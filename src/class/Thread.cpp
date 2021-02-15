/*
 * Context.cpp
 *
 * Created on: 10 de abr de 2019
 *   Author: lhlag
 */
#include "Thread.h"
#include <iostream>


Thread::Thread(){
	error_flags=0x00;
	cod_pointer=0;
	//vm=0;
	ct=0;
	cod=0;
	compare_flags=0;
#ifdef THREAD_CUSTOM_STACK
	stack_pointer=0;
	stack=new uint64[THREAD_STACK_SIZE];
	stack_max=THREAD_STACK_SIZE;
#else

#endif
	for(int x=0;x<256;x++)workspace[x]=0;
	vt=0;
}

Thread::~Thread(){
	delete[] stack;
}

void Thread::savePoint(){
	saveInStack(((uint64)ct->getCodContext()<<32)+cod_pointer);
}

void Thread::saveInStack(uint64 p){
#ifdef THREAD_CUSTOM_STACK
	if(stack_pointer>=stack_max){
		incrementStack();
		if(error_flags&MAX_LIMIT_STACK_){
			return;
		}
	}
	stack[stack_pointer++]=p;
#else
	stack.push(p);
#endif
}
uint64 Thread::recoverInStack(){
#ifdef THREAD_CUSTOM_STACK
	if(stack_pointer>100){
		if(stack_pointer&0x300!=0)if(stack_max>THREAD_STACK_SIZE)if(stack_pointer<(stack_max>>4)-64)decrementStack();
		return stack[--stack_pointer];
	}
	error_flags|=MIN_LIMIT_STACK_;
	return 0;
#else
	if(stack.empty()){
		error_flags|=MIN_LIMIT_STACK_;
		return 0;
	}
	uint64 ret=stack.top();
	stack.pop();
	return ret;
#endif
}

void Thread::recoverPoint(){
	register uint64 p=recoverInStack();
	if(isFinalized())return;
	register uint16 k=uint16(p>>32);
	if(ct->getCodContext()!=k){
		if(vt->checkContext(k)==0){
			error_flags|=INVALID_CHANGE_CONTEXT_;
			std::cout << "[ERROR] - Erro ao retornar para um Context que não existe mais. (ID= " << k << ")" << std::endl;
			return;
		}
		Context &c=vt->getContext(k);
		changeContext(c);
	}
	cod_pointer=uint32(p);
	return;
}

void Thread::setPontCodeCtx(uint48 val){
	uint64 p=val.toInt();
	register uint16 k=uint16(p>>32);
	if(ct->getCodContext()!=k){
		if(vt->checkContext(k)==0){
			error_flags|=INVALID_CHANGE_CONTEXT_;
			std::cout << "[ERROR] - Erro ao retornar para um Context que não existe mais. (ID= " << k << ")" << std::endl;
			return;
		}
		Context &c=vt->getContext(k);
		changeContext(c);
	}
	cod_pointer=uint32(p);
}

void Thread::prepare(VirtualMachine &v,Context &ct,uint16 cntx,uint32 pos){
	this->ct=&ct;
	vt=&v;
	cod=ct.cod;
	mem.prepare(&ct,&error_flags);
	error_flags&=~((uint16)1);
	cod_pointer=pos;
}
void Thread::changeContext(Context &c){
	mem.prepare(&c,&error_flags);
	cod=c.cod;
	cod_pointer=0;
	this->ct=&c;
}

VirtualMachine& Thread::getVirtualMachine(){
	return *vt;
}

uint16 Thread::runInstruction(void **funcs){
	uint16 opcode=getNext16();
	((Func)funcs[opcode])(*this);
	return opcode;
}

uint16 Thread::isFinalized(){
	return error_flags;
}
uint8* Thread::getPointerMemCode(){
	return ct->mem;
}

uint8 Thread::getNext8(){
	return cod[cod_pointer++];
}
uint16 Thread::getNextTwo8(){
	register uint16 x=*((uint16*)(&cod[cod_pointer]));
	cod_pointer+=2;
	return x;
}
void Thread::set16InCode(uint32 pont,uint16 val){
	register uint16* x=((uint16*)(&cod[pont]));
	*x=val;
}
void Thread::set32InCode(uint32 pont,uint32 val){
	register uint32* x=((uint32*)(&cod[pont]));
	*x=val;
}
uint16 Thread::getNext16(){
	register uint16 x=*((uint16*)(&cod[cod_pointer]));
	cod_pointer+=2;
	return x;
}
uint32 Thread::getNextTwo16(){
	register uint32 x=*((uint32*)(&cod[cod_pointer]));
	cod_pointer+=4;
	return x;
}
uint32 Thread::getNext32(){
	register uint32 x=*((uint32*)(&cod[cod_pointer]));
	cod_pointer+=4;
	return x;
}
uint64 Thread::getNextTwo32(){
	register uint64 x=*(uint64*)(&cod[cod_pointer]);
	cod_pointer+=8;
	return x;
}
uint48 Thread::getNext48(){
	register uint48 x=*((uint48*)(&cod[cod_pointer]));
	cod_pointer+=6;
	return x;
}
uint64 Thread::getNext64(){
	register uint64 x=*(uint64*)(&cod[cod_pointer]);
	cod_pointer+=8;
	return x;
}

uint8 Thread::checkUseCode(uint32 tam){
	if(cod_pointer+tam>ct->cod_len){
		//error_flags|=OVERLOAD_COD_ERROR_;
		throw CodeException(cod_pointer,"CHECK_CODE_THREAD",_OVERLOAD_CODE);
	}
	return error_flags;
}

void Thread::setPontCode(uint32 t){
	cod_pointer=t;
}
uint32 Thread::getPontCode(){
	return cod_pointer;
}

Context& Thread::getContext(){
	return *ct;
}


JitRuntime& Thread::getJitRuntime(){
	return vt->getManagerOpcodes().getJitRuntime();
}
