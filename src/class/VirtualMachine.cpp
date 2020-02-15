/*
 * VirtualMachine.cpp
 *
 *  Created on: 10 de abr de 2019
 *      Author: lhlag
 */
#include "VirtualMachine.h"
#include "../lib/Types.h"
#include "../lib/Dupla.h"
#include "../opcodes/GeralComand.h"
#include <stdlib.h>


VirtualMachine::VirtualMachine(uint8 debug){
	tamContex=0;
	tamThreads=0;
	if(debug>3)debug=3;
	vm_flags=(debug<<VM_FLAG_DEBUG_LV);
	for(int x=0;x<OPCODETAM;x++){
		VET[x]=(void*)no_opcode;
	}

	qtd_res=0;


	definesPositionsThread();

	funcs=0;
	func_pos=(uint16*)calloc(1,2);
	if(getDebugLevel()>=2)std::cout << "[LOG] - Definidas as variaveis hambientes!"<< std::endl;


	VET[0]=(void*)end_running;
	VET[1]=(void*)test_func;
	VET[2]=(void*)sleep;
	VET[HLT_COMAND]=(void*)do_nothing;

	VET[JIT_FLAG_START]=(void*)init_jit;
	VET[JIT_FLAG_END]=(void*)end_jit;
	VET[JIT_FLAG_EXECUTE]=(void*)execute_jit;
	VET[JIT_FLAG_ENTER_CODE]=(void*)enter_jit;

	setGerais();
	setMov();
	setArit();
	setCmp();
	setStack();
	if(getDebugLevel()>=2)std::cout << "[LOG] - Carregado as intruções!"<< std::endl;

	if(getDebugLevel()>=1)std::cout << "[LOG] - Criado a virtual machine!"<< std::endl;
}

VirtualMachine::~VirtualMachine(){
	if(getDebugLevel()>=1)std::cout << "[LOG] -00%- Desligando virtual machine!" << std::endl;

	for(uint64 x=0;x<th.size();x++){
		if(getDebugLevel()>=3)std::cout << "[LOG] -" << 10*((x+1)/float(th.size()+1)) << "%- Liberando Thread N: " << th[x].getSecond() << std::endl;
		delete &th[x].getFirst();
	}
	th.clear();
	if(getDebugLevel()>=2)std::cout << "[LOG] -10%- Liberado todas as threads!" << std::endl;

	for(uint16 x=0;x<funcs;x++){
		if(func_pos[x]==0)continue;
		if(getDebugLevel()>=3)std::cout << "[LOG] -" << 10+35*((x+1)/float(funcs+1)) << "%- Liberando Instrução N: " << func_pos[x] << std::endl;
		rt.release(VET[func_pos[x]]);
	}
	free(func_pos);

	if(getDebugLevel()>=2)std::cout << "[LOG] -50%- Liberado todas as alocações dinamicas!" << std::endl;
	for(uint16 x=0;x<qtd_res;x++){
		if(getDebugLevel()>=3)std::cout << "[LOG] -" << 50+20*((x+1)/float(qtd_res+1)) << "%- Liberando alocação N: " << x << std::endl;
		free(recursos_alocados[x]);
	}
	free(recursos_alocados);
	if(getDebugLevel()>=2)std::cout << "[LOG] -77%- Liberado todas as instruções!" << std::endl;
	for(uint64 x=0;x<ct.size();x++){
		if(getDebugLevel()>=3)std::cout << "[LOG] -" << (77+21*((x+1)/float(ct.size()+1))) << "%- Liberando Contexto N: " << ct[x].getSecond() << std::endl;
		ct[x].getFirst().clearFunctions(rt);
		delete &ct[x].getFirst();
	}
	ct.clear();
	if(getDebugLevel()>=2)std::cout << "[LOG] -98%- Liberado os Contextos!" << std::endl;

	if(getDebugLevel()>=1)std::cout << "[LOG] -100%- Maquina virtual liberada completamente" << std::endl;
	if(getDebugLevel()>=1)std::cout << "[LOG] - Maquina virtual desligada!" << std::endl;
}

uint8 VirtualMachine::getDebugLevel(){
	return (vm_flags>>VM_FLAG_DEBUG_LV)&3;
}

uint32 VirtualMachine::run(){
	uint32 flags=0;
	if(getDebugLevel()>=1)std::cout << "[LOG] - Executando maquina virtual!"<< std::endl;
	std::cout << "$$ A partir daqui, todas as mensagem serão referente a execução da VM. $$"<< std::endl;
	do{
		for(uint16 x=0;x<th.size();x++){
			Thread &t=th[x].getFirst();
			uint16 p=t.runInstruction(VET);
			if(t.isFinalized()){
				flags=t.isFinalized();
				t.~Thread();
				th.erase(th.begin()+x);
				std::cout << std::endl;
				if(getDebugLevel()>=2)std::cout << "[LOG] - Finalizada thread de numero: " << th[x].getSecond() << std::endl;
				finalize(flags);
			}
		}
	}while(th.size()!=0);
	std::cout << "$$ Mensagens da execução da VM terminada. $$"<< std::endl;
	return flags;
}

uint32 VirtualMachine::runCommand(){
	uint32 flags=0;
	if(th.size()==0)return 1;
	for(uint16 x=0;x<th.size();x++){
		uint16 p=th[x].getFirst().runInstruction(VET);
		if(getDebugLevel()>=1)std::cout << "[DEBUG] - EXE {thr:" << x <<",instrucao:" << p << "}"<< std::endl;
		if(p)((void(*)(Thread&))(VET[1]))(th[x].getFirst());
		if(th[x].getFirst().isFinalized()){
			if(th.size()==1)flags=th[x].getFirst().isFinalized();
			if(getDebugLevel()>=3)std::cout << "[DEBUG] - THR {id:" << th[x].getSecond() << ",state:0}"<< std::endl;
			th[x].getFirst().~Thread();
			th.erase(th.begin()+x);
		}
	}
	finalize(flags);
	return flags;
}

void VirtualMachine::createFunction(uint16 pos, CodeHolder &code){
	Error err = rt.add(&VET[pos], &code);
	if (err){
		if(getDebugLevel()>=1)std::cout << "[ERROR] - Error ao compilar comando da Virtual Machine! Comando:  "+pos << err <<  std::endl;
		return;
	}else if(getDebugLevel()>=3) std::cout << "[SUCESS] - Criado comando jit optimizado N: " << pos << std::endl;
	funcs++;
	func_pos=(uint16*)realloc(func_pos,funcs*2);
	func_pos[funcs-1]=pos;
}

uint16 VirtualMachine::loadContexto(uint8 *bytecode,uint32 tam){
	ct.resize(ct.size()+1);
	ct[ct.size()-1].setFirst(new Contexto());
	ct[ct.size()-1].getFirst().prepare(++tamContex,bytecode,tam);
	ct[ct.size()-1].setSecond(tamContex);
	if(getDebugLevel()>=2)std::cout << "[LOG] -" << ct[ct.size()-1].getFirst().printVisibleName() << "- Contexto carregado completamente." << std::endl;
	return tamContex;
}

Contexto& VirtualMachine::getContexto(uint16 id) {
	for(uint16 x=0;x<ct.size();x++){
		if(ct[x].getSecond()==id)return ct[x].getFirst();
	}
	return ct[0].getFirst();
}

void* VirtualMachine::alloc_resorce(uint32 tam){
	void *res=alloca(tam);
	qtd_res++;
	recursos_alocados=(void**)realloc(recursos_alocados,sizeof(void*)*qtd_res);
	recursos_alocados[qtd_res-1]=res;
	return res;
}
void VirtualMachine::free_resorce(void* res){
	if(!qtd_res)return;
	uint8 bol=0;
	for(uint32 x=0;x<qtd_res;x++){
		if(bol){
			recursos_alocados[x-1]=recursos_alocados[x];
		}else
			if(recursos_alocados[x]!=res)continue;
			else{
				bol=1;
			}
	}
	if(bol){
		qtd_res--;
		recursos_alocados=(void**)realloc(recursos_alocados,sizeof(void*)*qtd_res);
		free(res);
	}
}

uint16 VirtualMachine::checkContexto(uint16 id){
	for(uint16 x=0;x<ct.size();x++){
		if(ct[x].getSecond()==id)return id;
	}
	return 0;
}

void VirtualMachine::createThread(uint16 context,uint32 pos){
	uint64 c=(uint64)~0;
	for(uint64 x=0;x<ct.size();x++){
		if(ct[x].getSecond()==context){
			c=x;
			break;
		}
	}
	if(c==(uint64)~0){
		std::cout << "[ERROR] - Não foi encontrado o contexto de ID= " << tamThreads << " para a criação da thread." << std::endl;
		return;
	}
	th.resize(th.size()+1);
	th[th.size()-1].setFirst(new Thread());
	th[th.size()-1].getFirst().prepare(*this,ct[c].getFirst(),context,pos);
	th[th.size()-1].setSecond(tamThreads);
	if(getDebugLevel()>=2)std::cout << "[LOG] - Criado thread ID= " << tamThreads << std::endl;
	tamThreads++;
}

void VirtualMachine::finalize(uint16 flag){
	if(flag&RUNNING_)std::cout << "[LOG] - Finalizado apos chamada de finalização!" << std::endl;
	if(flag&OVERLOAD_COD_ERROR_)std::cout << "[ERROR] - Erro overload na memoria do codigo!" << std::endl;
	if(flag&OVERLOAD_MEM_ERROR_)std::cout << "[ERROR] - Erro overload na memoria usavel!" << std::endl;
	if(flag&MAX_LIMIT_STACK_)std::cout << "[ERROR] - Erro memoria máxima de stack possivel atingido!" << std::endl;
	if(flag&NO_OPCODE_COMMAND_)std::cout << "[ERROR] - Erro nenhum opcode encontrado correspondente!" << std::endl;
	if(flag&INVALID_OPCODE_JIT_)std::cout << "[ERROR] - Erro, opcode para transformação JIT invalido!" << std::endl;
	if(flag&INTERNAL_ERROR_)std::cout << "[ERROR] - Erro interno do programa, contate o desenvolvedor para possiveis ajustes no software." << std::endl;
	if(flag&INVALID_JMP_JIT_)std::cout << "[ERROR] - Erro ao entrar dentro de código JIT sem flag de entrada." << std::endl;
	if(flag&INVALID_CHANGE_CONTEXT_)std::cout << "[ERROR] - Acesso a um contexto inesistente ou que não existe mais." << std::endl;
	vm_flags&=~(VM_FLAG_RUNNING);
}


JitRuntime& VirtualMachine::getJitRuntime(){
	return rt;
}

void VirtualMachine::setStack(){
	VET[CALL_C]=(void*)call_c;
	VET[CALL_M]=(void*)call_m;
	VET[CALL_W]=(void*)call_w;
	VET[RETURN]=(void*)ret;

	VET[PUSH_C]=(void*)push_c;
	VET[PUSH_W]=(void*)push_w;
	VET[POP_W]=(void*)pop_w;

	VET[CALL_CTX_C]=(void*)call_ctx_c;
	VET[CALL_CTX_W]=(void*)call_ctx_w;
}

void VirtualMachine::setGerais(){
	VET[JMP_C]=(void*)jmp_c;
	VET[JMP_M]=(void*)jmp_m;
	VET[JMP_W]=(void*)jmp_w;
	VET[JMP_C_MA]=(void*)jmp_c_ma;
	VET[JMP_C_ME]=(void*)jmp_c_me;
	VET[JMP_C_DI]=(void*)jmp_c_di;
	VET[JMP_C_IG]=(void*)jmp_c_ig;
	VET[JMP_C_MA_IG]=(void*)jmp_c_ma_ig;
	VET[JMP_C_ME_IG]=(void*)jmp_c_me_ig;
	VET[JMP_M_MA]=(void*)jmp_m_ma;
	VET[JMP_M_ME]=(void*)jmp_m_me;
	VET[JMP_M_DI]=(void*)jmp_m_di;
	VET[JMP_M_IG]=(void*)jmp_m_ig;
	VET[JMP_M_MA_IG]=(void*)jmp_m_ma_ig;
	VET[JMP_M_ME_IG]=(void*)jmp_m_me_ig;
	VET[JMP_W_MA]=(void*)jmp_w_ma;
	VET[JMP_W_ME]=(void*)jmp_w_me;
	VET[JMP_W_DI]=(void*)jmp_w_di;
	VET[JMP_W_IG]=(void*)jmp_w_ig;
	VET[JMP_W_MA_IG]=(void*)jmp_w_ma_ig;
	VET[JMP_W_ME_IG]=(void*)jmp_w_me_ig;
	VET[LOOP_C_W]=(void*)loop_c_w;
	VET[LOOP_W_W]=(void*)loop_w_w;

	VET[INC_W]=(void*)inc_w;
	VET[DEC_W]=(void*)dec_w;

	VET[PRINT_OUT_CHAR]=(void*)print_out_char_w;
	VET[PRINT_OUT_NUM]=(void*)print_out_num_w;
	VET[PRINT_OUT_STRING_MMW]=(void*)print_out_string_mmw;
	VET[PRINT_OUT_STRING_M]=(void*)print_out_string_m;
	VET[LOAD_CONTEXT]=(void*)load_context_w_mw;
	VET[GET_CONTEXT_ID]=(void*)get_context_id_w;
	VET[CHECK_CONTEXT_ID]=(void*)check_context_id_w;


	VET[ALLOC_RES]=alloc_res;
	VET[FREE_RES]=free_res;
}
void VirtualMachine::setMov(){

	VET[P_UINT8+MOV_RRW_C]=(void*)mov_rrw_c8;
	VET[P_UINT16+MOV_RRW_C]=(void*)mov_rrw_c16;
	VET[P_UINT32+MOV_RRW_C]=(void*)mov_rrw_c32;
	VET[P_UINT48+MOV_RRW_C]=(void*)mov_rrw_c48;
	VET[P_UINT64+MOV_RRW_C]=(void*)mov_rrw_c64;

	VET[P_UINT8+MOV_RRW_W]=(void*)mov_rrw_w8;
	VET[P_UINT16+MOV_RRW_W]=(void*)mov_rrw_w16;
	VET[P_UINT32+MOV_RRW_W]=(void*)mov_rrw_w32;
	VET[P_UINT48+MOV_RRW_W]=(void*)mov_rrw_w48;
	VET[P_UINT64+MOV_RRW_W]=(void*)mov_rrw_w64;

	VET[P_UINT8+MOV_W_RRW]=(void*)mov_w_rrw8;
	VET[P_UINT16+MOV_W_RRW]=(void*)mov_w_rrw16;
	VET[P_UINT32+MOV_W_RRW]=(void*)mov_w_rrw32;
	VET[P_UINT48+MOV_W_RRW]=(void*)mov_w_rrw48;
	VET[P_UINT64+MOV_W_RRW]=(void*)mov_w_rrw64;

	VET[P_UINT8+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww8;
	VET[P_INT8+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww8;
	VET[P_UINT16+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww16;
	VET[P_INT16+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww16;
	VET[P_UINT32+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww32;
	VET[P_INT32+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww32;
	VET[P_UINT48+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww48;
	VET[P_INT48+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww48;
	VET[P_UINT64+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww64;
	VET[P_INT64+MOV_MMWW_MMWW]=(void*)mov_mmww_mmww64;
	VET[P_UINT8+MOV_MMWW_W]=(void*)mov_mmww_w8;
	VET[P_INT8+MOV_MMWW_W]=(void*)mov_mmww_w8;
	VET[P_UINT16+MOV_MMWW_W]=(void*)mov_mmww_w16;
	VET[P_INT16+MOV_MMWW_W]=(void*)mov_mmww_w16;
	VET[P_UINT32+MOV_MMWW_W]=(void*)mov_mmww_w32;
	VET[P_INT32+MOV_MMWW_W]=(void*)mov_mmww_w32;
	VET[P_UINT48+MOV_MMWW_W]=(void*)mov_mmww_w48;
	VET[P_INT48+MOV_MMWW_W]=(void*)mov_mmww_w48;
	VET[P_UINT64+MOV_MMWW_W]=(void*)mov_mmww_w64;
	VET[P_INT64+MOV_MMWW_W]=(void*)mov_mmww_w64;
	VET[P_UINT8+MOV_W_MMWW]=(void*)mov_w_mmww8;
	VET[P_INT8+MOV_W_MMWW]=(void*)mov_w_mmww8;
	VET[P_UINT16+MOV_W_MMWW]=(void*)mov_w_mmww16;
	VET[P_INT16+MOV_W_MMWW]=(void*)mov_w_mmww16;
	VET[P_UINT32+MOV_W_MMWW]=(void*)mov_w_mmww32;
	VET[P_INT32+MOV_W_MMWW]=(void*)mov_w_mmww32;
	VET[P_UINT48+MOV_W_MMWW]=(void*)mov_w_mmww48;
	VET[P_INT48+MOV_W_MMWW]=(void*)mov_w_mmww48;
	VET[P_UINT64+MOV_W_MMWW]=(void*)mov_w_mmww64;
	VET[P_INT64+MOV_W_MMWW]=(void*)mov_w_mmww64;
	VET[P_UINT8+MOV_MMWW_C]=(void*)mov_mmww_c8;
	VET[P_INT8+MOV_MMWW_C]=(void*)mov_mmww_c8;
	VET[P_UINT16+MOV_MMWW_C]=(void*)mov_mmww_c16;
	VET[P_INT16+MOV_MMWW_C]=(void*)mov_mmww_c16;
	VET[P_UINT32+MOV_MMWW_C]=(void*)mov_mmww_c32;
	VET[P_INT32+MOV_MMWW_C]=(void*)mov_mmww_c32;
	VET[P_UINT48+MOV_MMWW_C]=(void*)mov_mmww_c48;
	VET[P_INT48+MOV_MMWW_C]=(void*)mov_mmww_c48;
	VET[P_UINT64+MOV_MMWW_C]=(void*)mov_mmww_c64;


	VET[P_INT8+COPY_M_M_C]=(void*)copy_m_m_c8;
	VET[P_INT8+COPY_M_M_W]=(void*)copy_m_m_w8;
	VET[P_UINT8+COPY_M_M_C]=(void*)copy_m_m_c8;
	VET[P_UINT8+COPY_M_M_W]=(void*)copy_m_m_w8;
	VET[P_INT16+COPY_M_M_C]=(void*)copy_m_m_c16;
	VET[P_INT16+COPY_M_M_W]=(void*)copy_m_m_w16;
	VET[P_UINT16+COPY_M_M_C]=(void*)copy_m_m_c16;
	VET[P_UINT16+COPY_M_M_W]=(void*)copy_m_m_w16;
	VET[P_INT32+COPY_M_M_C]=(void*)copy_m_m_c32;
	VET[P_INT32+COPY_M_M_W]=(void*)copy_m_m_w32;
	VET[P_UINT32+COPY_M_M_C]=(void*)copy_m_m_c32;
	VET[P_UINT32+COPY_M_M_W]=(void*)copy_m_m_w32;
	VET[P_INT48+COPY_M_M_C]=(void*)copy_m_m_c48;
	VET[P_INT48+COPY_M_M_W]=(void*)copy_m_m_w48;
	VET[P_UINT48+COPY_M_M_C]=(void*)copy_m_m_c48;
	VET[P_UINT48+COPY_M_M_W]=(void*)copy_m_m_w48;
	VET[P_INT64+COPY_M_M_C]=(void*)copy_m_m_c64;
	VET[P_INT64+COPY_M_M_W]=(void*)copy_m_m_w64;
	VET[P_UINT64+COPY_M_M_C]=(void*)copy_m_m_c64;
	VET[P_UINT64+COPY_M_M_W]=(void*)copy_m_m_w64;

	VET[P_INT8+COPY_MW_MW_C]=(void*)copy_mw_mw_c8;
	VET[P_INT8+COPY_MW_MW_W]=(void*)copy_mw_mw_w8;
	VET[P_UINT8+COPY_MW_MW_C]=(void*)copy_mw_mw_c8;
	VET[P_UINT8+COPY_MW_MW_W]=(void*)copy_mw_mw_w8;
	VET[P_INT16+COPY_MW_MW_C]=(void*)copy_mw_mw_c16;
	VET[P_INT16+COPY_MW_MW_W]=(void*)copy_mw_mw_w16;
	VET[P_UINT16+COPY_MW_MW_C]=(void*)copy_mw_mw_c16;
	VET[P_UINT16+COPY_MW_MW_W]=(void*)copy_mw_mw_w16;
	VET[P_INT32+COPY_MW_MW_C]=(void*)copy_mw_mw_c32;
	VET[P_INT32+COPY_MW_MW_W]=(void*)copy_mw_mw_w32;
	VET[P_UINT32+COPY_MW_MW_C]=(void*)copy_mw_mw_c32;
	VET[P_UINT32+COPY_MW_MW_W]=(void*)copy_mw_mw_w32;
	VET[P_INT48+COPY_MW_MW_C]=(void*)copy_mw_mw_c48;
	VET[P_INT48+COPY_MW_MW_W]=(void*)copy_mw_mw_w48;
	VET[P_UINT48+COPY_MW_MW_C]=(void*)copy_mw_mw_c48;
	VET[P_UINT48+COPY_MW_MW_W]=(void*)copy_mw_mw_w48;
	VET[P_INT64+COPY_MW_MW_C]=(void*)copy_mw_mw_c64;
	VET[P_INT64+COPY_MW_MW_W]=(void*)copy_mw_mw_w64;
	VET[P_UINT64+COPY_MW_MW_C]=(void*)copy_mw_mw_c64;
	VET[P_UINT64+COPY_MW_MW_W]=(void*)copy_mw_mw_w64;

	VET[P_INT8+MOV_MMW_MMW]=(void*)mov_mmw_mmw8;
	VET[P_INT16+MOV_MMW_MMW]=(void*)mov_mmw_mmw16;
	VET[P_INT32+MOV_MMW_MMW]=(void*)mov_mmw_mmw32;
	VET[P_INT48+MOV_MMW_MMW]=(void*)mov_mmw_mmw48;
	VET[P_INT64+MOV_MMW_MMW]=(void*)mov_mmw_mmw64;
	VET[P_INT8+MOV_W_MMW]=(void*)mov_w_mmw8;
	VET[P_INT16+MOV_W_MMW]=(void*)mov_w_mmw16;
	VET[P_INT32+MOV_W_MMW]=(void*)mov_w_mmw32;
	VET[P_INT48+MOV_W_MMW]=(void*)mov_w_mmw48;
	VET[P_INT64+MOV_W_MMW]=(void*)mov_w_mmw64;
	VET[P_INT8+MOV_MMW_W]=(void*)mov_mmw_w8;
	VET[P_INT16+MOV_MMW_W]=(void*)mov_mmw_w16;
	VET[P_INT32+MOV_MMW_W]=(void*)mov_mmw_w32;
	VET[P_INT48+MOV_MMW_W]=(void*)mov_mmw_w48;
	VET[P_INT64+MOV_MMW_W]=(void*)mov_mmw_w64;

	VET[P_UINT8+MOV_MMW_MMW]=(void*)mov_mmw_mmw8;
	VET[P_UINT16+MOV_MMW_MMW]=(void*)mov_mmw_mmw16;
	VET[P_UINT32+MOV_MMW_MMW]=(void*)mov_mmw_mmw32;
	VET[P_UINT48+MOV_MMW_MMW]=(void*)mov_mmw_mmw48;
	VET[P_UINT64+MOV_MMW_MMW]=(void*)mov_mmw_mmw64;
	VET[P_UINT8+MOV_W_MMW]=(void*)mov_w_mmw8;
	VET[P_UINT16+MOV_W_MMW]=(void*)mov_w_mmw16;
	VET[P_UINT32+MOV_W_MMW]=(void*)mov_w_mmw32;
	VET[P_UINT48+MOV_W_MMW]=(void*)mov_w_mmw48;
	VET[P_UINT64+MOV_W_MMW]=(void*)mov_w_mmw64;
	VET[P_UINT8+MOV_MMW_W]=(void*)mov_mmw_w8;
	VET[P_UINT16+MOV_MMW_W]=(void*)mov_mmw_w16;
	VET[P_UINT32+MOV_MMW_W]=(void*)mov_mmw_w32;
	VET[P_UINT48+MOV_MMW_W]=(void*)mov_mmw_w48;
	VET[P_UINT64+MOV_MMW_W]=(void*)mov_mmw_w64;


	VET[P_UINT8+MOV_MMW_C]=(void*)mov_mmw_c8;
	VET[P_UINT16+MOV_MMW_C]=(void*)mov_mmw_c16;
	VET[P_UINT32+MOV_MMW_C]=(void*)mov_mmw_c32;
	VET[P_UINT48+MOV_MMW_C]=(void*)mov_mmw_c48;
	VET[P_UINT64+MOV_MMW_C]=(void*)mov_mmw_c64;
	VET[P_UINT8+MOV_MMW_M]=(void*)mov_mmw_m8;
	VET[P_UINT16+MOV_MMW_M]=(void*)mov_mmw_m16;
	VET[P_UINT32+MOV_MMW_M]=(void*)mov_mmw_m32;
	VET[P_UINT48+MOV_MMW_M]=(void*)mov_mmw_m48;
	VET[P_UINT64+MOV_MMW_M]=(void*)mov_mmw_m64;
	VET[P_UINT8+MOV_M_MMW]=(void*)mov_m_mmw8;
	VET[P_UINT16+MOV_M_MMW]=(void*)mov_m_mmw16;
	VET[P_UINT32+MOV_M_MMW]=(void*)mov_m_mmw32;
	VET[P_UINT48+MOV_M_MMW]=(void*)mov_m_mmw48;
	VET[P_UINT64+MOV_M_MMW]=(void*)mov_m_mmw64;

	VET[P_INT8+MOV_MMW_C]=(void*)mov_mmw_c8;
	VET[P_INT16+MOV_MMW_C]=(void*)mov_mmw_c16;
	VET[P_INT32+MOV_MMW_C]=(void*)mov_mmw_c32;
	VET[P_INT48+MOV_MMW_C]=(void*)mov_mmw_c48;
	VET[P_INT64+MOV_MMW_C]=(void*)mov_mmw_c64;
	VET[P_INT8+MOV_MMW_M]=(void*)mov_mmw_m8;	//mov m[w[?]],m[?] (8 bits)
	VET[P_INT16+MOV_MMW_M]=(void*)mov_mmw_m16;
	VET[P_INT32+MOV_MMW_M]=(void*)mov_mmw_m32;
	VET[P_INT48+MOV_MMW_M]=(void*)mov_mmw_m48;
	VET[P_INT64+MOV_MMW_M]=(void*)mov_mmw_m64;
	VET[P_INT8+MOV_M_MMW]=(void*)mov_m_mmw8;
	VET[P_INT16+MOV_M_MMW]=(void*)mov_m_mmw16;
	VET[P_INT32+MOV_M_MMW]=(void*)mov_m_mmw32;
	VET[P_INT48+MOV_M_MMW]=(void*)mov_m_mmw48;
	VET[P_INT64+MOV_M_MMW]=(void*)mov_m_mmw64;

	VET[P_UINT8+MOV_M_C]=(void*)mov_m_c8;
	VET[P_UINT16+MOV_M_C]=(void*)mov_m_c16;
	VET[P_UINT32+MOV_M_C]=(void*)mov_m_c32;
	VET[P_UINT48+MOV_M_C]=(void*)mov_m_c48;
	VET[P_UINT64+MOV_M_C]=(void*)mov_m_c64;
	VET[P_UINT8+MOV_M_M]=(void*)mov_m_m8;
	VET[P_UINT16+MOV_M_M]=(void*)mov_m_m16;
	VET[P_UINT32+MOV_M_M]=(void*)mov_m_m32;
	VET[P_UINT48+MOV_M_M]=(void*)mov_m_m48;
	VET[P_UINT64+MOV_M_M]=(void*)mov_m_m64;
	VET[P_UINT8+MOV_M_W]=(void*)mov_m_w8;
	VET[P_UINT16+MOV_M_W]=(void*)mov_m_w16;
	VET[P_UINT32+MOV_M_W]=(void*)mov_m_w32;
	VET[P_UINT48+MOV_M_W]=(void*)mov_m_w48;
	VET[P_UINT64+MOV_M_W]=(void*)mov_m_w64;
	VET[P_UINT8+MOV_W_C]=(void*)mov_w_c8;
	VET[P_UINT16+MOV_W_C]=(void*)mov_w_c16;
	VET[P_UINT32+MOV_W_C]=(void*)mov_w_c32;
	VET[P_UINT48+MOV_W_C]=(void*)mov_w_c48;
	VET[P_UINT64+MOV_W_C]=(void*)mov_w_c64;


	//TASK Fazer comandos interpretados em JIT


	{
		CodeHolder ch;
		ch.init(rt.codeInfo());
		c_mov_w_w8(&ch);
		createFunction(P_UINT8+MOV_W_W,ch);
		createFunction(P_INT8+MOV_W_W,ch);
	}
	{
		CodeHolder ch;
		ch.init(rt.codeInfo());
		c_mov_w_w16(&ch);
		createFunction(P_UINT16+MOV_W_W,ch);
		createFunction(P_INT16+MOV_W_W,ch);
	}
	{
		CodeHolder ch;
		ch.init(rt.codeInfo());
		c_mov_w_w32(&ch);
		createFunction(P_UINT32+MOV_W_W,ch);
		createFunction(P_INT32+MOV_W_W,ch);
	}

	{
		CodeHolder ch;
		ch.init(rt.codeInfo());
		c_mov_w_w48(&ch);
		createFunction(P_UINT48+MOV_W_W,ch);
		createFunction(P_INT48+MOV_W_W,ch);
	}
	{
		CodeHolder ch;
		ch.init(rt.codeInfo());
		c_mov_w_w64(&ch);
		createFunction(P_UINT64+MOV_W_W,ch);
		createFunction(P_INT64+MOV_W_W,ch);
	}
	//VET[P_UINT8+MOV_W_W]=(void*)mov_w_w8;
	//VET[P_UINT16+MOV_W_W]=(void*)mov_w_w16;
	//VET[P_UINT32+MOV_W_W]=(void*)mov_w_w32;
	//VET[P_UINT48+MOV_W_W]=(void*)mov_w_w48;
	//VET[P_UINT64+MOV_W_W]=(void*)mov_w_w64;

	VET[P_UINT8+MOV_W_M]=(void*)mov_w_m8;
	VET[P_UINT16+MOV_W_M]=(void*)mov_w_m16;
	VET[P_UINT32+MOV_W_M]=(void*)mov_w_m32;
	VET[P_UINT48+MOV_W_M]=(void*)mov_w_m48;
	VET[P_UINT64+MOV_W_M]=(void*)mov_w_m64;


	VET[P_INT8+MOV_M_C]=(void*)mov_m_c8;
	VET[P_INT16+MOV_M_C]=(void*)mov_m_c16;
	VET[P_INT32+MOV_M_C]=(void*)mov_m_c32;
	VET[P_INT48+MOV_M_C]=(void*)mov_m_c48;
	VET[P_INT64+MOV_M_C]=(void*)mov_m_c64;
	VET[P_INT8+MOV_M_M]=(void*)mov_m_m8;
	VET[P_INT16+MOV_M_M]=(void*)mov_m_m16;
	VET[P_INT32+MOV_M_M]=(void*)mov_m_m32;
	VET[P_INT48+MOV_M_M]=(void*)mov_m_m48;
	VET[P_INT64+MOV_M_M]=(void*)mov_m_m64;
	VET[P_INT8+MOV_M_W]=(void*)mov_m_w8;
	VET[P_INT16+MOV_M_W]=(void*)mov_m_w16;
	VET[P_INT32+MOV_M_W]=(void*)mov_m_w32;
	VET[P_INT48+MOV_M_W]=(void*)mov_m_w48;
	VET[P_INT64+MOV_M_W]=(void*)mov_m_w64;
	VET[P_INT8+MOV_W_C]=(void*)mov_w_c8;
	VET[P_INT16+MOV_W_C]=(void*)mov_w_c16;
	VET[P_INT32+MOV_W_C]=(void*)mov_w_c32;
	VET[P_INT48+MOV_W_C]=(void*)mov_w_c48;
	VET[P_INT64+MOV_W_C]=(void*)mov_w_c64;
	VET[P_INT8+MOV_W_M]=(void*)mov_w_m8;
	VET[P_INT16+MOV_W_M]=(void*)mov_w_m16;
	VET[P_INT32+MOV_W_M]=(void*)mov_w_m32;
	VET[P_INT48+MOV_W_M]=(void*)mov_w_m48;
	VET[P_INT64+MOV_W_M]=(void*)mov_w_m64;
/*
	VET[P_INT8+MOV_W_W]=(void*)mov_w_w8;
	VET[P_INT16+MOV_W_W]=(void*)mov_w_w16;
	VET[P_INT32+MOV_W_W]=(void*)mov_w_w32;
	VET[P_INT48+MOV_W_W]=(void*)mov_w_w48;
	VET[P_INT64+MOV_W_W]=(void*)mov_w_w64;
	*/
}
void VirtualMachine::setArit(){

	VET[LEA_W__W_W_C]=(void*)lea_w__w_w_c;
	VET[LEA_W__W_W_W]=(void*)lea_w__w_w_w;
	VET[LEA_W__W_W_1]=(void*)lea_w__w_w_1;
	VET[LEA_W__W_W_2]=(void*)lea_w__w_w_2;
	VET[LEA_W__W_W_4]=(void*)lea_w__w_w_4;
	VET[LEA_W__W_W_8]=(void*)lea_w__w_w_8;
	VET[LEA_W__W_W_16]=(void*)lea_w__w_w_16;
	VET[LEA_W__W_W_32]=(void*)lea_w__w_w_32;
	VET[LEA_W__W_W_64]=(void*)lea_w__w_w_64;

	VET[P_UINT8+DD_W_C]=(void*)dd_w_c_8;
	VET[P_UINT16+DD_W_C]=(void*)dd_w_c_16;
	VET[P_UINT32+DD_W_C]=(void*)dd_w_c_32;
	VET[P_UINT48+DD_W_C]=(void*)dd_w_c_48;
	VET[P_UINT64+DD_W_C]=(void*)dd_w_c_64;

	VET[P_INT8+DD_W_C]=(void*)dd_w_c_8;
	VET[P_INT16+DD_W_C]=(void*)dd_w_c_16;
	VET[P_INT32+DD_W_C]=(void*)dd_w_c_32;
	VET[P_INT48+DD_W_C]=(void*)dd_w_c_48;
	VET[P_INT64+DD_W_C]=(void*)dd_w_c_64;

	VET[P_UINT8+DD_W_W]=(void*)dd_w_w_8;
	VET[P_UINT16+DD_W_W]=(void*)dd_w_w_16;
	VET[P_UINT32+DD_W_W]=(void*)dd_w_w_32;
	VET[P_UINT48+DD_W_W]=(void*)dd_w_w_48;
	VET[P_UINT64+DD_W_W]=(void*)dd_w_w_64;

	VET[P_INT8+DD_W_W]=(void*)dd_w_w_8;
	VET[P_INT16+DD_W_W]=(void*)dd_w_w_16;
	VET[P_INT32+DD_W_W]=(void*)dd_w_w_32;
	VET[P_INT48+DD_W_W]=(void*)dd_w_w_48;
	VET[P_INT64+DD_W_W]=(void*)dd_w_w_64;

	VET[P_UINT8+DE_W_C]=(void*)de_w_c_8;
	VET[P_UINT16+DE_W_C]=(void*)de_w_c_16;
	VET[P_UINT32+DE_W_C]=(void*)de_w_c_32;
	VET[P_UINT48+DE_W_C]=(void*)de_w_c_48;
	VET[P_UINT64+DE_W_C]=(void*)de_w_c_64;

	VET[P_INT8+DE_W_C]=(void*)de_w_c_8;
	VET[P_INT16+DE_W_C]=(void*)de_w_c_16;
	VET[P_INT32+DE_W_C]=(void*)de_w_c_32;
	VET[P_INT48+DE_W_C]=(void*)de_w_c_48;
	VET[P_INT64+DE_W_C]=(void*)de_w_c_64;

	VET[P_UINT8+DE_W_W]=(void*)de_w_w_8;
	VET[P_UINT16+DE_W_W]=(void*)de_w_w_16;
	VET[P_UINT32+DE_W_W]=(void*)de_w_w_32;
	VET[P_UINT48+DE_W_W]=(void*)de_w_w_48;
	VET[P_UINT64+DE_W_W]=(void*)de_w_w_64;

	VET[P_INT8+DE_W_W]=(void*)de_w_w_8;
	VET[P_INT16+DE_W_W]=(void*)de_w_w_16;
	VET[P_INT32+DE_W_W]=(void*)de_w_w_32;
	VET[P_INT48+DE_W_W]=(void*)de_w_w_48;
	VET[P_INT64+DE_W_W]=(void*)de_w_w_64;

	//Aritimetic
	VET[P_INT8+SOMA_M_C]=(void*)soma_m_c_i8;
	VET[P_INT16+SOMA_M_C]=(void*)soma_m_c_i16;
	VET[P_INT32+SOMA_M_C]=(void*)soma_m_c_i32;
	VET[P_INT48+SOMA_M_C]=(void*)soma_m_c_i48;
	VET[P_INT64+SOMA_M_C]=(void*)soma_m_c_i64;
	VET[P_INT8+SOMA_W_C]=(void*)soma_w_c_i8;
	VET[P_INT16+SOMA_W_C]=(void*)soma_w_c_i16;
	VET[P_INT32+SOMA_W_C]=(void*)soma_w_c_i32;
	VET[P_INT48+SOMA_W_C]=(void*)soma_w_c_i48;
	VET[P_INT64+SOMA_W_C]=(void*)soma_w_c_i64;
	VET[P_INT8+SOMA_W_M]=(void*)soma_w_m_i8;
	VET[P_INT16+SOMA_W_M]=(void*)soma_w_m_i16;
	VET[P_INT32+SOMA_W_M]=(void*)soma_w_m_i32;
	VET[P_INT48+SOMA_W_M]=(void*)soma_w_m_i48;
	VET[P_INT64+SOMA_W_M]=(void*)soma_w_m_i64;
	VET[P_INT8+SOMA_W_W]=(void*)soma_w_w_i8;
	VET[P_INT16+SOMA_W_W]=(void*)soma_w_w_i16;
	VET[P_INT32+SOMA_W_W]=(void*)soma_w_w_i32;
	VET[P_INT48+SOMA_W_W]=(void*)soma_w_w_i48;
	VET[P_INT64+SOMA_W_W]=(void*)soma_w_w_i64;

	VET[P_UINT8+SOMA_M_C]=(void*)soma_m_c_ui8;
	VET[P_UINT16+SOMA_M_C]=(void*)soma_m_c_ui16;
	VET[P_UINT32+SOMA_M_C]=(void*)soma_m_c_ui32;
	VET[P_UINT48+SOMA_M_C]=(void*)soma_m_c_ui48;
	VET[P_UINT64+SOMA_M_C]=(void*)soma_m_c_ui64;
	VET[P_UINT8+SOMA_W_C]=(void*)soma_w_c_ui8;
	VET[P_UINT16+SOMA_W_C]=(void*)soma_w_c_ui16;
	VET[P_UINT32+SOMA_W_C]=(void*)soma_w_c_ui32;
	VET[P_UINT48+SOMA_W_C]=(void*)soma_w_c_ui48;
	VET[P_UINT64+SOMA_W_C]=(void*)soma_w_c_ui64;
	VET[P_UINT8+SOMA_W_M]=(void*)soma_w_m_ui8;
	VET[P_UINT16+SOMA_W_M]=(void*)soma_w_m_ui16;
	VET[P_UINT32+SOMA_W_M]=(void*)soma_w_m_ui32;
	VET[P_UINT48+SOMA_W_M]=(void*)soma_w_m_ui48;
	VET[P_UINT64+SOMA_W_M]=(void*)soma_w_m_ui64;
	VET[P_UINT8+SOMA_W_W]=(void*)soma_w_w_ui8;
	VET[P_UINT16+SOMA_W_W]=(void*)soma_w_w_ui16;
	VET[P_UINT32+SOMA_W_W]=(void*)soma_w_w_ui32;
	VET[P_UINT48+SOMA_W_W]=(void*)soma_w_w_ui48;
	VET[P_UINT64+SOMA_W_W]=(void*)soma_w_w_ui64;


	//Aritimetic
	VET[P_INT8+SUB_M_C]=(void*)sub_m_c_i8;
	VET[P_INT16+SUB_M_C]=(void*)sub_m_c_i16;
	VET[P_INT32+SUB_M_C]=(void*)sub_m_c_i32;
	VET[P_INT48+SUB_M_C]=(void*)sub_m_c_i48;
	VET[P_INT64+SUB_M_C]=(void*)sub_m_c_i64;
	VET[P_INT8+SUB_W_C]=(void*)sub_w_c_i8;
	VET[P_INT16+SUB_W_C]=(void*)sub_w_c_i16;
	VET[P_INT32+SUB_W_C]=(void*)sub_w_c_i32;
	VET[P_INT48+SUB_W_C]=(void*)sub_w_c_i48;
	VET[P_INT64+SUB_W_C]=(void*)sub_w_c_i64;
	VET[P_INT8+SUB_W_M]=(void*)sub_w_m_i8;
	VET[P_INT16+SUB_W_M]=(void*)sub_w_m_i16;
	VET[P_INT32+SUB_W_M]=(void*)sub_w_m_i32;
	VET[P_INT48+SUB_W_M]=(void*)sub_w_m_i48;
	VET[P_INT64+SUB_W_M]=(void*)sub_w_m_i64;
	VET[P_INT8+SUB_W_W]=(void*)sub_w_w_i8;
	VET[P_INT16+SUB_W_W]=(void*)sub_w_w_i16;
	VET[P_INT32+SUB_W_W]=(void*)sub_w_w_i32;
	VET[P_INT48+SUB_W_W]=(void*)sub_w_w_i48;
	VET[P_INT64+SUB_W_W]=(void*)sub_w_w_i64;

	VET[P_UINT8+SUB_M_C]=(void*)sub_m_c_ui8;
	VET[P_UINT16+SUB_M_C]=(void*)sub_m_c_ui16;
	VET[P_UINT32+SUB_M_C]=(void*)sub_m_c_ui32;
	VET[P_UINT48+SUB_M_C]=(void*)sub_m_c_ui48;
	VET[P_UINT64+SUB_M_C]=(void*)sub_m_c_ui64;
	VET[P_UINT8+SUB_W_C]=(void*)sub_w_c_ui8;
	VET[P_UINT16+SUB_W_C]=(void*)sub_w_c_ui16;
	VET[P_UINT32+SUB_W_C]=(void*)sub_w_c_ui32;
	VET[P_UINT48+SUB_W_C]=(void*)sub_w_c_ui48;
	VET[P_UINT64+SUB_W_C]=(void*)sub_w_c_ui64;
	VET[P_UINT8+SUB_W_M]=(void*)sub_w_m_ui8;
	VET[P_UINT16+SUB_W_M]=(void*)sub_w_m_ui16;
	VET[P_UINT32+SUB_W_M]=(void*)sub_w_m_ui32;
	VET[P_UINT48+SUB_W_M]=(void*)sub_w_m_ui48;
	VET[P_UINT64+SUB_W_M]=(void*)sub_w_m_ui64;
	VET[P_UINT8+SUB_W_W]=(void*)sub_w_w_ui8;
	VET[P_UINT16+SUB_W_W]=(void*)sub_w_w_ui16;
	VET[P_UINT32+SUB_W_W]=(void*)sub_w_w_ui32;
	VET[P_UINT48+SUB_W_W]=(void*)sub_w_w_ui48;
	VET[P_UINT64+SUB_W_W]=(void*)sub_w_w_ui64;


	//Aritimetic
	VET[P_INT8+MUL_M_C]=(void*)mul_m_c_i8;
	VET[P_INT16+MUL_M_C]=(void*)mul_m_c_i16;
	VET[P_INT32+MUL_M_C]=(void*)mul_m_c_i32;
	VET[P_INT48+MUL_M_C]=(void*)mul_m_c_i48;
	VET[P_INT64+MUL_M_C]=(void*)mul_m_c_i64;
	VET[P_INT8+MUL_W_C]=(void*)mul_w_c_i8;
	VET[P_INT16+MUL_W_C]=(void*)mul_w_c_i16;
	VET[P_INT32+MUL_W_C]=(void*)mul_w_c_i32;
	VET[P_INT48+MUL_W_C]=(void*)mul_w_c_i48;
	VET[P_INT64+MUL_W_C]=(void*)mul_w_c_i64;
	VET[P_INT8+MUL_W_M]=(void*)mul_w_m_i8;
	VET[P_INT16+MUL_W_M]=(void*)mul_w_m_i16;
	VET[P_INT32+MUL_W_M]=(void*)mul_w_m_i32;
	VET[P_INT48+MUL_W_M]=(void*)mul_w_m_i48;
	VET[P_INT64+MUL_W_M]=(void*)mul_w_m_i64;
	VET[P_INT8+MUL_W_W]=(void*)mul_w_w_i8;
	VET[P_INT16+MUL_W_W]=(void*)mul_w_w_i16;
	VET[P_INT32+MUL_W_W]=(void*)mul_w_w_i32;
	VET[P_INT48+MUL_W_W]=(void*)mul_w_w_i48;
	VET[P_INT64+MUL_W_W]=(void*)mul_w_w_i64;

	VET[P_UINT8+MUL_M_C]=(void*)mul_m_c_ui8;
	VET[P_UINT16+MUL_M_C]=(void*)mul_m_c_ui16;
	VET[P_UINT32+MUL_M_C]=(void*)mul_m_c_ui32;
	VET[P_UINT48+MUL_M_C]=(void*)mul_m_c_ui48;
	VET[P_UINT64+MUL_M_C]=(void*)mul_m_c_ui64;
	VET[P_UINT8+MUL_W_C]=(void*)mul_w_c_ui8;
	VET[P_UINT16+MUL_W_C]=(void*)mul_w_c_ui16;
	VET[P_UINT32+MUL_W_C]=(void*)mul_w_c_ui32;
	VET[P_UINT48+MUL_W_C]=(void*)mul_w_c_ui48;
	VET[P_UINT64+MUL_W_C]=(void*)mul_w_c_ui64;
	VET[P_UINT8+MUL_W_M]=(void*)mul_w_m_ui8;
	VET[P_UINT16+MUL_W_M]=(void*)mul_w_m_ui16;
	VET[P_UINT32+MUL_W_M]=(void*)mul_w_m_ui32;
	VET[P_UINT48+MUL_W_M]=(void*)mul_w_m_ui48;
	VET[P_UINT64+MUL_W_M]=(void*)mul_w_m_ui64;
	VET[P_UINT8+MUL_W_W]=(void*)mul_w_w_ui8;
	VET[P_UINT16+MUL_W_W]=(void*)mul_w_w_ui16;
	VET[P_UINT32+MUL_W_W]=(void*)mul_w_w_ui32;
	VET[P_UINT48+MUL_W_W]=(void*)mul_w_w_ui48;
	VET[P_UINT64+MUL_W_W]=(void*)mul_w_w_ui64;


	//Aritimetic
	VET[P_INT8+DIV_M_C]=(void*)div_m_c_i8;
	VET[P_INT16+DIV_M_C]=(void*)div_m_c_i16;
	VET[P_INT32+DIV_M_C]=(void*)div_m_c_i32;
	VET[P_INT48+DIV_M_C]=(void*)div_m_c_i48;
	VET[P_INT64+DIV_M_C]=(void*)div_m_c_i64;
	VET[P_INT8+DIV_W_C]=(void*)div_w_c_i8;
	VET[P_INT16+DIV_W_C]=(void*)div_w_c_i16;
	VET[P_INT32+DIV_W_C]=(void*)div_w_c_i32;
	VET[P_INT48+DIV_W_C]=(void*)div_w_c_i48;
	VET[P_INT64+DIV_W_C]=(void*)div_w_c_i64;
	VET[P_INT8+DIV_W_M]=(void*)div_w_m_i8;
	VET[P_INT16+DIV_W_M]=(void*)div_w_m_i16;
	VET[P_INT32+DIV_W_M]=(void*)div_w_m_i32;
	VET[P_INT48+DIV_W_M]=(void*)div_w_m_i48;
	VET[P_INT64+DIV_W_M]=(void*)div_w_m_i64;
	VET[P_INT8+DIV_W_W]=(void*)div_w_w_i8;
	VET[P_INT16+DIV_W_W]=(void*)div_w_w_i16;
	VET[P_INT32+DIV_W_W]=(void*)div_w_w_i32;
	VET[P_INT48+DIV_W_W]=(void*)div_w_w_i48;
	VET[P_INT64+DIV_W_W]=(void*)div_w_w_i64;

	VET[P_UINT8+DIV_M_C]=(void*)div_m_c_ui8;
	VET[P_UINT16+DIV_M_C]=(void*)div_m_c_ui16;
	VET[P_UINT32+DIV_M_C]=(void*)div_m_c_ui32;
	VET[P_UINT48+DIV_M_C]=(void*)div_m_c_ui48;
	VET[P_UINT64+DIV_M_C]=(void*)div_m_c_ui64;
	VET[P_UINT8+DIV_W_C]=(void*)div_w_c_ui8;
	VET[P_UINT16+DIV_W_C]=(void*)div_w_c_ui16;
	VET[P_UINT32+DIV_W_C]=(void*)div_w_c_ui32;
	VET[P_UINT48+DIV_W_C]=(void*)div_w_c_ui48;
	VET[P_UINT64+DIV_W_C]=(void*)div_w_c_ui64;
	VET[P_UINT8+DIV_W_M]=(void*)div_w_m_ui8;
	VET[P_UINT16+DIV_W_M]=(void*)div_w_m_ui16;
	VET[P_UINT32+DIV_W_M]=(void*)div_w_m_ui32;
	VET[P_UINT48+DIV_W_M]=(void*)div_w_m_ui48;
	VET[P_UINT64+DIV_W_M]=(void*)div_w_m_ui64;
	VET[P_UINT8+DIV_W_W]=(void*)div_w_w_ui8;
	VET[P_UINT16+DIV_W_W]=(void*)div_w_w_ui16;
	VET[P_UINT32+DIV_W_W]=(void*)div_w_w_ui32;
	VET[P_UINT48+DIV_W_W]=(void*)div_w_w_ui48;
	VET[P_UINT64+DIV_W_W]=(void*)div_w_w_ui64;


	//Aritimetic
	VET[P_INT8+MOD_M_C]=(void*)mod_m_c_i8;
	VET[P_INT16+MOD_M_C]=(void*)mod_m_c_i16;
	VET[P_INT32+MOD_M_C]=(void*)mod_m_c_i32;
	VET[P_INT48+MOD_M_C]=(void*)mod_m_c_i48;
	VET[P_INT64+MOD_M_C]=(void*)mod_m_c_i64;
	VET[P_INT8+MOD_W_C]=(void*)mod_w_c_i8;
	VET[P_INT16+MOD_W_C]=(void*)mod_w_c_i16;
	VET[P_INT32+MOD_W_C]=(void*)mod_w_c_i32;
	VET[P_INT48+MOD_W_C]=(void*)mod_w_c_i48;
	VET[P_INT64+MOD_W_C]=(void*)mod_w_c_i64;
	VET[P_INT8+MOD_W_M]=(void*)mod_w_m_i8;
	VET[P_INT16+MOD_W_M]=(void*)mod_w_m_i16;
	VET[P_INT32+MOD_W_M]=(void*)mod_w_m_i32;
	VET[P_INT48+MOD_W_M]=(void*)mod_w_m_i48;
	VET[P_INT64+MOD_W_M]=(void*)mod_w_m_i64;
	VET[P_INT8+MOD_W_W]=(void*)mod_w_w_i8;
	VET[P_INT16+MOD_W_W]=(void*)mod_w_w_i16;
	VET[P_INT32+MOD_W_W]=(void*)mod_w_w_i32;
	VET[P_INT48+MOD_W_W]=(void*)mod_w_w_i48;
	VET[P_INT64+MOD_W_W]=(void*)mod_w_w_i64;

	VET[P_UINT8+MOD_M_C]=(void*)mod_m_c_ui8;
	VET[P_UINT16+MOD_M_C]=(void*)mod_m_c_ui16;
	VET[P_UINT32+MOD_M_C]=(void*)mod_m_c_ui32;
	VET[P_UINT48+MOD_M_C]=(void*)mod_m_c_ui48;
	VET[P_UINT64+MOD_M_C]=(void*)mod_m_c_ui64;
	VET[P_UINT8+MOD_W_C]=(void*)mod_w_c_ui8;
	VET[P_UINT16+MOD_W_C]=(void*)mod_w_c_ui16;
	VET[P_UINT32+MOD_W_C]=(void*)mod_w_c_ui32;
	VET[P_UINT48+MOD_W_C]=(void*)mod_w_c_ui48;
	VET[P_UINT64+MOD_W_C]=(void*)mod_w_c_ui64;
	VET[P_UINT8+MOD_W_M]=(void*)mod_w_m_ui8;
	VET[P_UINT16+MOD_W_M]=(void*)mod_w_m_ui16;
	VET[P_UINT32+MOD_W_M]=(void*)mod_w_m_ui32;
	VET[P_UINT48+MOD_W_M]=(void*)mod_w_m_ui48;
	VET[P_UINT64+MOD_W_M]=(void*)mod_w_m_ui64;
	VET[P_UINT8+MOD_W_W]=(void*)mod_w_w_ui8;
	VET[P_UINT16+MOD_W_W]=(void*)mod_w_w_ui16;
	VET[P_UINT32+MOD_W_W]=(void*)mod_w_w_ui32;
	VET[P_UINT48+MOD_W_W]=(void*)mod_w_w_ui48;
	VET[P_UINT64+MOD_W_W]=(void*)mod_w_w_ui64;
}
void VirtualMachine::setCmp(){

	VET[P_UINT8+CMP_M_C]=(void*)cmp_m_c_ui8;
	VET[P_UINT16+CMP_M_C]=(void*)cmp_m_c_ui16;
	VET[P_UINT32+CMP_M_C]=(void*)cmp_m_c_ui32;
	VET[P_UINT48+CMP_M_C]=(void*)cmp_m_c_ui48;
	VET[P_UINT64+CMP_M_C]=(void*)cmp_m_c_ui64;
	VET[P_UINT8+CMP_M_M]=(void*)cmp_m_m_ui8;
	VET[P_UINT16+CMP_M_M]=(void*)cmp_m_m_ui16;
	VET[P_UINT32+CMP_M_M]=(void*)cmp_m_m_ui32;
	VET[P_UINT48+CMP_M_M]=(void*)cmp_m_m_ui48;
	VET[P_UINT64+CMP_M_M]=(void*)cmp_m_m_ui64;
	VET[P_UINT8+CMP_M_W]=(void*)cmp_m_w_ui8;
	VET[P_UINT16+CMP_M_W]=(void*)cmp_m_w_ui16;
	VET[P_UINT32+CMP_M_W]=(void*)cmp_m_w_ui32;
	VET[P_UINT48+CMP_M_W]=(void*)cmp_m_w_ui48;
	VET[P_UINT64+CMP_M_W]=(void*)cmp_m_w_ui64;
	VET[P_UINT8+CMP_W_C]=(void*)cmp_w_c_ui8;
	VET[P_UINT16+CMP_W_C]=(void*)cmp_w_c_ui16;
	VET[P_UINT32+CMP_W_C]=(void*)cmp_w_c_ui32;
	VET[P_UINT48+CMP_W_C]=(void*)cmp_w_c_ui48;
	VET[P_UINT64+CMP_W_C]=(void*)cmp_w_c_ui64;
	VET[P_UINT8+CMP_W_M]=(void*)cmp_w_m_ui8;
	VET[P_UINT16+CMP_W_M]=(void*)cmp_w_m_ui16;
	VET[P_UINT32+CMP_W_M]=(void*)cmp_w_m_ui32;
	VET[P_UINT48+CMP_W_M]=(void*)cmp_w_m_ui48;
	VET[P_UINT64+CMP_W_M]=(void*)cmp_w_m_ui64;
	VET[P_UINT8+CMP_W_W]=(void*)cmp_w_w_ui8;
	VET[P_UINT16+CMP_W_W]=(void*)cmp_w_w_ui16;
	VET[P_UINT32+CMP_W_W]=(void*)cmp_w_w_ui32;
	VET[P_UINT48+CMP_W_W]=(void*)cmp_w_w_ui48;
	VET[P_UINT64+CMP_W_W]=(void*)cmp_w_w_ui64;


	VET[P_INT8+CMP_M_C]=(void*)cmp_m_c_i8;
	VET[P_INT16+CMP_M_C]=(void*)cmp_m_c_i16;
	VET[P_INT32+CMP_M_C]=(void*)cmp_m_c_i32;
	VET[P_INT48+CMP_M_C]=(void*)cmp_m_c_i48;
	VET[P_INT64+CMP_M_C]=(void*)cmp_m_c_i64;
	VET[P_INT8+CMP_M_M]=(void*)cmp_m_m_i8;
	VET[P_INT16+CMP_M_M]=(void*)cmp_m_m_i16;
	VET[P_INT32+CMP_M_M]=(void*)cmp_m_m_i32;
	VET[P_INT48+CMP_M_M]=(void*)cmp_m_m_i48;
	VET[P_INT64+CMP_M_M]=(void*)cmp_m_m_i64;
	VET[P_INT8+CMP_M_W]=(void*)cmp_m_w_i8;
	VET[P_INT16+CMP_M_W]=(void*)cmp_m_w_i16;
	VET[P_INT32+CMP_M_W]=(void*)cmp_m_w_i32;
	VET[P_INT48+CMP_M_W]=(void*)cmp_m_w_i48;
	VET[P_INT64+CMP_M_W]=(void*)cmp_m_w_i64;
	VET[P_INT8+CMP_W_C]=(void*)cmp_w_c_i8;
	VET[P_INT16+CMP_W_C]=(void*)cmp_w_c_i16;
	VET[P_INT32+CMP_W_C]=(void*)cmp_w_c_i32;
	VET[P_INT48+CMP_W_C]=(void*)cmp_w_c_i48;
	VET[P_INT64+CMP_W_C]=(void*)cmp_w_c_i64;
	VET[P_INT8+CMP_W_M]=(void*)cmp_w_m_i8;
	VET[P_INT16+CMP_W_M]=(void*)cmp_w_m_i16;
	VET[P_INT32+CMP_W_M]=(void*)cmp_w_m_i32;
	VET[P_INT48+CMP_W_M]=(void*)cmp_w_m_i48;
	VET[P_INT64+CMP_W_M]=(void*)cmp_w_m_i64;
	VET[P_INT8+CMP_W_W]=(void*)cmp_w_w_i8;
	VET[P_INT16+CMP_W_W]=(void*)cmp_w_w_i16;
	VET[P_INT32+CMP_W_W]=(void*)cmp_w_w_i32;
	VET[P_INT48+CMP_W_W]=(void*)cmp_w_w_i48;
	VET[P_INT64+CMP_W_W]=(void*)cmp_w_w_i64;
}
