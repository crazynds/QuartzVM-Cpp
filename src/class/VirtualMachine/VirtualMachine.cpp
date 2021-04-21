/*
 * VirtualMachine.cpp
 *
 *  Created on: 10 de abr de 2019
 *      Author: lhlag
 */
#include "../../lib/IOMessages.h"
#include "VirtualMachine.h"

#include "../Thread.h"
#include "../Context.h"

#include <vector>
#include <future>
#include <chrono>


#define PRINT_MESSAGE(type,str) {std::stringstream os;os << str;printMessage(getDebugLevel(),type,os);}
#define PRINT_MESSAGE2(type,str) {std::stringstream os;os << str;printMessage(debugLevel,type,os);}



VirtualMachine::VirtualMachine(uint8 debug):
	manJit(VET,debug){
	start();

	if(getDebugLevel()>=2)std::cout << "[LOG] - Carregado as intruções!"<< std::endl;
	nextIdContext = 1;
	nextIdThread = 1;


	if(debug>3)debug=3;
	vm_flags=(debug<<VM_FLAG_DEBUG_LV)|(1<<VM_FLAG_RUNNING);
	recursos_alocados = (void**)mmalloc(0);
	qtd_res=0;

	if(getDebugLevel()>=2)std::cout << "[LOG] - Definidas as variaveis hambientes!"<< std::endl;



	if(getDebugLevel()>=1)std::cout << "[LOG] - Criado a virtual machine!"<< std::endl;
}

VirtualMachine::~VirtualMachine(){

	double percentage=0;

	PRINT_MESSAGE(OUT_LOG," |"<<  percentage << "%| Desligando virtual machine!");

	double unclear = (threads.size()+1)+contexts.size()+4+qtd_res+1;
	double passo = 95/unclear;
	percentage+=4;
	PRINT_MESSAGE(OUT_LOG," |"<<  percentage << "%| Calculado todas as porcentagem!");

	percentage+=passo*(threads.size()+1);
	threads.clear();
	PRINT_MESSAGE(OUT_LOG," |"<<  percentage << "%| Liberado todas as threads!");

	percentage+=passo*4;
	manJit.releaseOpcodesJit();
	PRINT_MESSAGE(OUT_LOG," |"<<  percentage << "%| Liberado todas as instruções!");

	for(uint16 x=0;x<qtd_res;x++){
		free(recursos_alocados[x]);
		percentage+=passo;
		PRINT_MESSAGE(OUT_LOG_EXTRA," |"<<  percentage << "%| Liberando alocação N: " << x);
	}
	free(recursos_alocados);
	percentage+=passo;
	PRINT_MESSAGE(OUT_LOG," |"<<  percentage << "%| Liberado todas as alocações dinamicas!");

	percentage+=passo*contexts.size();
	contexts.clear();
	PRINT_MESSAGE(OUT_LOG, " |"<<  percentage << "%| Liberado os Contexts!");

	PRINT_MESSAGE(OUT_LOG," |100%| Maquina virtual liberada completamente");
	PRINT_MESSAGE(OUT_LOG,"Maquina virtual desligada!");
}

uint8 VirtualMachine::getDebugLevel(){
	return (vm_flags>>VM_FLAG_DEBUG_LV)&3;
}


void finalizeThread(uint16 flags,uint8 debugLevel){
	if(flags&RUNNING_)PRINT_MESSAGE2(OUT_LOG,"Finalizado apos chamada de finalização!");
	//if(flag&OVERLOAD_COD_ERROR_)PRINT_MESSAGE2(OUT_ERROR,"Erro overload na memoria do codigo!");
	if(flags&OVERLOAD_MEM_ERROR_)PRINT_MESSAGE2(OUT_ERROR,"Erro overload na memoria usavel!");
	if(flags&MAX_LIMIT_STACK_)PRINT_MESSAGE2(OUT_ERROR,"Erro memoria máxima de stack possivel atingido!");
	//if(flag&NO_OPCODE_COMMAND_)PRINT_MESSAGE2(OUT_ERROR,"Erro nenhum opcode encontrado correspondente!");
	//if(flag&INVALID_OPCODE_JIT_)PRINT_MESSAGE2(OUT_ERROR,"Erro, opcode para transformação JIT invalido!");
	if(flags&INTERNAL_ERROR_)PRINT_MESSAGE2(OUT_ERROR,"Erro interno do programa, mantenha as bibliotecas atualizadas para evitar esse erro novamente.");
	if(flags&INVALID_JMP_JIT_)PRINT_MESSAGE2(OUT_ERROR,"Erro ao tentar entrar dentro de código JIT sem flag de entrada.");
	if(flags&INVALID_CHANGE_CONTEXT_)PRINT_MESSAGE2(OUT_ERROR,"Acesso a um Context inesistente ou que não existe mais.");
	if(flags&MIN_LIMIT_STACK_)PRINT_MESSAGE2(OUT_ERROR,"Erro na tentativa de leitura de valor na stack vazia!");
}

uint16 runThread(Thread *t,void** COMANDS){
	try{
		while(!t->isFinalized()){
			uint16 opcode = t->getNext16();
			((Func)COMANDS[opcode])(*t);
		}
	}catch(VMException &e){
		e.addToPath("VM_RUN");
		t->setErrorFlags(INTERNAL_ERROR_);
		e.printError();
	}
	finalizeThread(t->isFinalized(),t->getVirtualMachine().getDebugLevel());
	return t->isFinalized();
}


uint16 VirtualMachine::run(){
	uint16 flags=0;
	PRINT_MESSAGE(OUT_INFO_EXTRA,"Executando maquina virtual!");
	PRINT_MESSAGE(OUT_LOG, "$$ A partir daqui, todas as mensagem serão referente a execução da VM. $$");

	std::map<uint16,std::future<uint16>> futures;
	const std::chrono::milliseconds span (25);

	for(auto it=threads.begin(); it!=threads.end(); ++it){
		Thread &t=it->second;
		t.setErrorFlags(RUNNING_);
		futures[it->first]=std::async(runThread,&t,VET);
	}
	while(threads.size()>0){
		for(auto it = futures.begin(); it!=futures.end(); ++it){
			auto &future = it->second;
			uint16 id = it->first;
			if(future.wait_for(span)!=std::future_status::timeout){
				auto it = threads.find(id);
				if(it==threads.end())
					continue;
				if(it->second.isFinalized()&INTERNAL_ERROR_){
					vm_flags|=1<<VM_FLAG_EXCEPTION;
				}
				threads.erase(it);
			}
		}
	}

	finalize();
	return flags;
}

uint16 VirtualMachine::runCommand(){
	uint16 flags=0;
	if(threads.size()==0)return 1;
	try{
		for (std::map<uint16,Thread>::iterator it=threads.begin(); it!=threads.end(); ++it){
			Thread &t=it->second;
			uint16 p = t.getNext16();
			((Func)VET[p])(t);
			PRINT_MESSAGE(OUT_LOG_EXTRA,"EXE {thr:" << it->first <<",instrucao:" << "0x" << std::hex << p << "}");

			if(t.isFinalized()){
				flags|=t.isFinalized();
				threads.erase(it);
				PRINT_MESSAGE(OUT_DEBUG,"CLOSED THREAD {id: " << it->first << ", flags: "<< t.isFinalized() << "}");
				finalizeThread(flags,getDebugLevel());
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
		contexts.emplace(std::piecewise_construct,
				std::forward_as_tuple(id),
				std::forward_as_tuple(this,id,bytecode,tam));
		if(nextIdContext==0){
			do{
				nextIdContext++;
			}while(contexts.find(nextIdContext)!=contexts.end());
		}

	}catch(VMException &e){
		e.printError();
		vm_flags|=1<<VM_FLAG_EXCEPTION;
	}
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
uint16 VirtualMachine::createThread(uint16 context,uint32 pos){
	if(!checkContext(context)){
		PRINT_MESSAGE(OUT_ERROR,"Não foi encontrado o Context de ID= " << context << " para a criação da thread.");
		return 0;
	}
	uint16 id = nextIdThread++;
	threads.emplace(std::piecewise_construct,
			std::forward_as_tuple(id),
			std::forward_as_tuple(this,&(contexts[context]),pos,id));
	if(nextIdThread==0){
		do{
			nextIdThread++;
		}while(threads.find(nextIdThread)!=threads.end());
	}

	PRINT_MESSAGE(OUT_INFO,"Criado thread ID= " << id)
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
		PRINT_MESSAGE(OUT_WARNING, (char*)"!A VM apresentou exceções durante sua execução!");
	PRINT_MESSAGE(OUT_INFO, (char*)"$$ Mensagens da execução da VM terminada. $$");
}



