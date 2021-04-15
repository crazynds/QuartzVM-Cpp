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
#include <sstream>



VirtualMachine::VirtualMachine(uint8 debug):
	manJit(VET,debug){
	start();
	nextIdContext = 1;
	nextIdThread = 1;


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

	double unclear = threads.size()+1+4+qtd_res+1+contexts.size();
	double passo = 94/unclear;
	percentage+=5;
	if(getDebugLevel()>=1)std::cout << "[LOG] -" << percentage << "%- Calculado todas as porcentagem!" << std::endl;

	percentage+=passo*threads.size();
	threads.clear();
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

	percentage+=passo*contexts.size();
	contexts.clear();
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
	for (std::map<uint16,Thread>::iterator it=threads.begin(); it!=threads.end(); ++it){
		Thread &t=it->second;
		uint16 opcode = t.getNext16();
		((Func)VET[opcode])(t);
		if(t.isFinalized()){
			flags|=t.isFinalized();
			threads.erase(it);
			if(getDebugLevel()>=2)std::cout << "[LOG] - Finalizada thread de numero: " << it->first << std::endl;
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
		}while(threads.size()>0);
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
	if(threads.size()==0)return 1;
	try{
		for (std::map<uint16,Thread>::iterator it=threads.begin(); it!=threads.end(); ++it){
			Thread &t=it->second;
			uint16 p = t.getNext16();
			((Func)VET[p])(t);
			if(getDebugLevel()>=1)std::cout << "[DEBUG] - EXE {thr:" << it->first <<",instrucao:" << "0x" << std::hex << p << "}"<< std::endl;
			if(t.isFinalized()){
				flags|=t.isFinalized();
				threads.erase(it);
				if(getDebugLevel()>=3)std::cout << "[DEBUG] - CLOSED THREAD {id: " << it->first << ", flags: "<< t.isFinalized() << "}" << std::endl;
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
	uint16 id;
	try{
		id = nextIdContext++;
		contexts[id] = Context();
		if(nextIdContext==0){
			do{
				nextIdContext++;
			}while(contexts.find(nextIdContext)!=contexts.end());
		}
	}catch(VMException &e){
		e.printError();
		vm_flags|=1<<VM_FLAG_EXCEPTION;
	}
	if(getDebugLevel()>=2)std::cout << "[LOG] -" << contexts[id].printVisibleName() << "- Context carregado completamente." << std::endl;
	return id;
}

Context& VirtualMachine::getContext(uint16 id) {
	return contexts[id];
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
	auto it = contexts.find(id);
	if(it!=contexts.end())
		return it->first;
	else return 0;
}

#define PRINT_MESSAGE(type,str) {std::stringstream os;os << str;printMessage(type,os);}

uint16 VirtualMachine::createThread(uint16 context,uint32 pos){
	if(!checkContext(context)){
		std::stringstream os;
		os << "Não foi encontrado o Context de ID= " << context << " para a criação da thread.";
		printMessage(OUT_ERROR,os);
		return 0;
	}
	uint16 id = nextIdThread++;
	threads[id] = Thread(this,&(contexts[context]),pos,id);
	if(nextIdThread==0){
		do{
			nextIdThread++;
		}while(threads.find(nextIdThread)!=threads.end());
	}
	{
		std::stringstream os;
		os << "[LOG] - Criado thread ID= " << id;
		printMessage(OUT_INFO,os);
	}

	PRINT_MESSAGE(OUT_INFO,"[LOG] - Criado thread ID= " << id)
	return id;
}




bool VirtualMachine::isRunning(){
	return (vm_flags&(VM_FLAG_RUNNING));
}
bool VirtualMachine::isExceptionCatched(){
	return (vm_flags&(1<<VM_FLAG_EXCEPTION));
}

void VirtualMachine::finalize(){
	vm_flags&=~(VM_FLAG_RUNNING);

	if(vm_flags&(1<<VM_FLAG_EXCEPTION))
		printMessage(OUT_WARNING, (char*)"!A VM apresentou exceções durante sua execução!");
	printMessage(OUT_INFO, (char*)"$$ Mensagens da execução da VM terminada. $$");
}


void VirtualMachine::printMessage(uint8 type,char *str){
	std::string s(str);
	switch(type){
	case OUT_INFO:
		std::cout << "[INFO] - "<<s  << std::endl;
		break;
	case OUT_LOG:
		std::cout << "[LOG] - "<<s  << std::endl;
		break;
	case OUT_ERROR:
		std::cout << "[ERROR] - "<<s  << std::endl;
		break;
	case OUT_WARNING:
		if(getDebugLevel()<1)return;
		std::cout << "[WARNING] - "<<s << std::endl;
		break;
	case OUT_SUCESS:
		if(getDebugLevel()<1)return;
		std::cout << "[SUCESS] - "<<s << std::endl;
		break;
	case OUT_INFO_EXTRA:
		if(getDebugLevel()<2)return;
		std::cout << "[INFO] - "<<s << std::endl;
		break;
	case OUT_LOG_EXTRA:
		if(getDebugLevel()<2)return;
		std::cout << "[LOG] - "<<s << std::endl;
		break;
	case OUT_DEBUG:
		if(getDebugLevel()<3)return;
		std::cout << "[DEBUG] - "<<s << std::endl;
		break;
	}
}

void VirtualMachine::printMessage(uint8 type,std::stringstream& os){
	std::string s = os.str();
	switch(type){
	case OUT_INFO:
		std::cout << "[INFO] - "<<s  << std::endl;
		break; // Awails show
	case OUT_LOG:
		std::cout << "[LOG] - "<<s  << std::endl;
		break;
	case OUT_ERROR:
		std::cout << "[ERROR] - "<<s  << std::endl;
		break;
	case OUT_WARNING:
		if(getDebugLevel()<1)return;
		std::cout << "[WARNING] - "<<s << std::endl;
		break;
	case OUT_SUCESS:
		if(getDebugLevel()<1)return;
		std::cout << "[SUCESS] - "<<s << std::endl;
		break;
	case OUT_INFO_EXTRA:
		if(getDebugLevel()<2)return;
		std::cout << "[INFO] - "<<s << std::endl;
		break;
	case OUT_LOG_EXTRA:
		if(getDebugLevel()<2)return;
		std::cout << "[LOG] - "<<s << std::endl;
		break;
	case OUT_DEBUG:
		if(getDebugLevel()<3)return;
		std::cout << "[DEBUG] - "<<s << std::endl;
		break;
	}
}




