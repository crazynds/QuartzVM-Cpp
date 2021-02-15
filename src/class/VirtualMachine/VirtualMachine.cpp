/*
 * VirtualMachine.cpp
 *
 *  Created on: 10 de abr de 2019
 *      Author: lhlag
 */
#include "VirtualMachine.h"

#include "../Thread.h"
#include "../Context.h"
#include <stdlib.h>


VirtualMachine::VirtualMachine(uint8 debug):
	manJit(VET,debug){
	start();
	tamContex=0;
	tamThreads=0;

	if(debug>3)debug=3;
	vm_flags=(debug<<VM_FLAG_DEBUG_LV)|(1<<VM_FLAG_RUNNING);
	recursos_alocados = (void**)mmalloc(0);
	qtd_res=0;

	if(getDebugLevel()>=2)std::cout << "[LOG] - Definidas as variaveis hambientes!"<< std::endl;


	if(getDebugLevel()>=2)std::cout << "[LOG] - Carregado as intruções!"<< std::endl;

	if(getDebugLevel()>=1)std::cout << "[LOG] - Criado a virtual machine!"<< std::endl;
}

VirtualMachine::~VirtualMachine(){
	double percentage=0;
	if(getDebugLevel()>=1)std::cout << "[LOG] -" << percentage << "%- Desligando virtual machine!" << std::endl;

	double unclear = th.size()+1+4+qtd_res+1+ct.size()*2+1;
	double passo = 94/unclear;
	percentage+=5;
	if(getDebugLevel()>=1)std::cout << "[LOG] -" << percentage << "%- Calculado todas as porcentagem!" << std::endl;

	for(uint64 x=0;x<th.size();x++){
		delete &th[x].getFirst();
		percentage+=passo;
		if(getDebugLevel()>=3)std::cout << "[LOG] -" << percentage << "%- Liberando Thread N: " << th[x].getSecond() << std::endl;
	}
	th.clear();
	percentage+=passo;
	if(getDebugLevel()>=2)std::cout << "[LOG] -" << percentage << "%- Liberado todas as threads!" << std::endl;

	percentage+=passo*4;
	manJit.releaseOpcodesJit();
	if(getDebugLevel()>=2)std::cout << "[LOG] -" << percentage << "%- Liberado todas as instruções!" << std::endl;

	for(uint16 x=0;x<qtd_res;x++){
		free(recursos_alocados[x]);
		percentage+=passo;
		if(getDebugLevel()>=3)std::cout << "[LOG] -" << percentage << "%- Liberando alocação N: " << x << std::endl;
	}
	free(recursos_alocados);
	percentage+=passo;
	if(getDebugLevel()>=2)std::cout << "[LOG] -" << percentage << "%- Liberado todas as alocações dinamicas!" << std::endl;

	for(uint64 x=0;x<ct.size();x++){
		ct[x].getFirst().clearFunctions(manJit.getJitRuntime());
		delete &ct[x].getFirst();
		percentage+=passo*2;
		if(getDebugLevel()>=3)std::cout << "[LOG] -" << percentage << "%- Liberando Context N: " << ct[x].getSecond() << std::endl;
	}
	ct.clear();
	percentage+=passo;
	if(getDebugLevel()>=2)std::cout << "[LOG] -" << percentage << "%- Liberado os Contexts!" << std::endl;

	if(getDebugLevel()>=1)std::cout << "[LOG] -100%- Maquina virtual liberada completamente" << std::endl;
	if(getDebugLevel()>=1)std::cout << "[LOG] - Maquina virtual desligada!" << std::endl;
}

void finalizeThread(uint16 flag){
	if(flag&RUNNING_)std::cout << "[LOG] - Finalizado apos chamada de finalização!" << std::endl;
	//if(flag&OVERLOAD_COD_ERROR_)std::cout << "[ERROR] - Erro overload na memoria do codigo!" << std::endl;
	if(flag&OVERLOAD_MEM_ERROR_)std::cout << "[ERROR] - Erro overload na memoria usavel!" << std::endl;
	if(flag&MAX_LIMIT_STACK_)std::cout << "[ERROR] - Erro memoria máxima de stack possivel atingido!" << std::endl;
	//if(flag&NO_OPCODE_COMMAND_)std::cout << "[ERROR] - Erro nenhum opcode encontrado correspondente!" << std::endl;
	//if(flag&INVALID_OPCODE_JIT_)std::cout << "[ERROR] - Erro, opcode para transformação JIT invalido!" << std::endl;
	if(flag&INTERNAL_ERROR_)std::cout << "[ERROR] - Erro interno do programa, mantenha as bibliotecas atualizadas para evitar esse erro novamente." << std::endl;
	if(flag&INVALID_JMP_JIT_)std::cout << "[ERROR] - Erro ao tentar entrar dentro de código JIT sem flag de entrada." << std::endl;
	if(flag&INVALID_CHANGE_CONTEXT_)std::cout << "[ERROR] - Acesso a um Context inesistente ou que não existe mais." << std::endl;
	if(flag&MIN_LIMIT_STACK_)std::cout << "[ERROR] - Erro na tentativa de leitura de valor na stack vazia!" << std::endl;
}

uint8 VirtualMachine::getDebugLevel(){
	return (vm_flags>>VM_FLAG_DEBUG_LV)&3;
}


inline uint32 VirtualMachine::runAllThread1Time(uint32 flags){
	for(uint16 x=0;x<th.size();x++){
		Thread &t=th[x].getFirst();
		uint16 p=t.runInstruction(VET);
		if(t.isFinalized()){
			flags|=t.isFinalized();
			delete &th[x].getFirst();
			th.erase(th.begin()+x);
			if(getDebugLevel()>=2)std::cout << "[LOG] - Finalizada thread de numero: " << th[x].getSecond() << std::endl;
			finalizeThread(flags);
		}
	}
	return flags;
}



uint32 VirtualMachine::run(){
	uint32 flags=0;
	if(getDebugLevel()>=1)std::cout << "[LOG] - Executando maquina virtual!"<< std::endl;
	std::cout << "$$ A partir daqui, todas as mensagem serão referente a execução da VM. $$"<< std::endl;
	try{
		do{
			flags=runAllThread1Time(flags);
		}while(th.size()!=0);
	}catch(VMException &e){
		e.addToPath("VM_RUN");
		vm_flags|=1<<VM_FLAG_EXCEPTION;
		flags|=INTERNAL_ERROR_;
		e.printError();
	}
	finalize();
	return flags;
}

uint32 VirtualMachine::runCommand(){
	uint32 flags=0;
	if(th.size()==0)return 1;
	try{
		for(uint16 x=0;x<th.size();x++){
			uint16 p=th[x].getFirst().runInstruction(VET);
			if(getDebugLevel()>=1)std::cout << "[DEBUG] - EXE {thr:" << x <<",instrucao:" << "0x" << std::hex << p << "}"<< std::endl;
			if(th[x].getFirst().isFinalized()){
				if(th.size()==1)flags=th[x].getFirst().isFinalized();
				if(getDebugLevel()>=3)std::cout << "[DEBUG] - CLOSED THREAD {id: " << th[x].getSecond() << ", flags: "<< th[x].getFirst().isFinalized() << "}" << std::endl;
				delete &th[x].getFirst();
				th.erase(th.begin()+x);
				finalizeThread(flags);
			}
		}
	}catch(VMException &e){
		e.addToPath("VM_RUN_DEBUG");
		vm_flags|=1<<VM_FLAG_EXCEPTION;
		flags|=INTERNAL_ERROR_;
		e.printError();
	}
	if(flags || isExceptionCatched())finalize();

	return flags;
}


ManagerOpcodes& VirtualMachine::getManagerOpcodes(){
	return manJit;
}

uint16 VirtualMachine::loadContext(uint8 *bytecode,uint32 tam){
	try{
		ct.resize(ct.size()+1);
		ct[ct.size()-1].setFirst(new Context());
		ct[ct.size()-1].getFirst().prepare(++tamContex,bytecode,tam);
		ct[ct.size()-1].setSecond(tamContex);
	}catch(VMException &e){
		e.printError();
		vm_flags|=1<<VM_FLAG_EXCEPTION;
	}
	if(getDebugLevel()>=2)std::cout << "[LOG] -" << ct[ct.size()-1].getFirst().printVisibleName() << "- Context carregado completamente." << std::endl;
	return tamContex;
}

Context& VirtualMachine::getContext(uint16 id) {
	for(uint16 x=0;x<ct.size();x++){
		if(ct[x].getSecond()==id)return ct[x].getFirst();
	}
	return ct[0].getFirst();
}

void* VirtualMachine::alloc_resorce(uint32 tam){
	void *res=(void*)mmalloc(tam);
	qtd_res++;
	recursos_alocados=(void**)mrealloc(recursos_alocados,sizeof(void*)*qtd_res);
	recursos_alocados[qtd_res-1]=res;
	return res;
}
void* VirtualMachine::realloc_resorce(void *res,uint32 tam){
	for(uint32 x=0;x<qtd_res;x++){
		if(recursos_alocados[x]==res){
			void *aux=(void*)mrealloc(res,tam);
			recursos_alocados[x]=aux;
			return res;
		}
	}
	return alloc_resorce(tam);
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
		recursos_alocados=(void**)mrealloc(recursos_alocados,sizeof(void*)*qtd_res);
		free(res);
	}
}

uint16 VirtualMachine::checkContext(uint16 id){
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
		std::cout << "[ERROR] - Não foi encontrado o Context de ID= " << tamThreads << " para a criação da thread." << std::endl;
		return;
	}
	th.resize(th.size()+1);
	th[th.size()-1].setFirst(new Thread());
	th[th.size()-1].getFirst().prepare(*this,ct[c].getFirst(),context,pos);
	th[th.size()-1].setSecond(tamThreads);
	if(getDebugLevel()>=2)std::cout << "[LOG] - Criado thread ID= " << tamThreads << std::endl;
	tamThreads++;
}
bool VirtualMachine::isRunning(){
	return (vm_flags&(VM_FLAG_RUNNING));
}
bool VirtualMachine::isExceptionCatched(){
	return (vm_flags&(1<<VM_FLAG_EXCEPTION));
}

void VirtualMachine::finalize(){
	vm_flags&=~(VM_FLAG_RUNNING);
	if(vm_flags&(1<<VM_FLAG_EXCEPTION))std::cout << "[WARNING] ! A VM apresentou exceções durante sua execução !" << std::endl;
	std::cout << "$$ Mensagens da execução da VM terminada. $$"<< std::endl;
}


