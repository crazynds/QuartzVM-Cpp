/*
 * Context.cpp
 *
 * Created on: 10 de abr de 2019
 *   Author: lhlag
 */
#include "Thread.h"
#include <iostream>


Thread::Thread(VirtualMachine *v,Context *ct,uint32 pos,uint16 id):
mem(ct,&error_flags){
	this->id=id;
	this->ct=ct;
	this->vt=v;
	cod=ct->getCodeDataPointer();
	cod_pointer=pos;
	code_len = ct->getCodeDataSize();

	error_flags&=~((uint16)1);
	compare_flags=0;
#ifdef THREAD_CUSTOM_STACK
	stack_pointer=0;
	stack=new uint64[THREAD_STACK_SIZE];
	stack_max=THREAD_STACK_SIZE;
#else

#endif
	for(int x=0;x<256;x++)workspace[x]=0;
}

Thread::Thread(){
	this->id=0;
	this->ct=NULL;
	this->vt=NULL;
	cod=NULL;
	cod_pointer = 0;
	code_len = 0;

	error_flags&=~((uint16)1);
	compare_flags=0;

	#ifdef THREAD_CUSTOM_STACK
		stack_pointer=0;
		stack=new uint64[THREAD_STACK_SIZE];
		stack_max=THREAD_STACK_SIZE;
	#else

	#endif

	for(int x=0;x<256;x++)workspace[x]=0;
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
		Context& c=vt->getContext(k);
		changeContext(&c);
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
		Context& c=vt->getContext(k);
		changeContext(&c);
	}
	cod_pointer=uint32(p);
}

void Thread::changeContext(Context *c,uint32 pos){
	new (&mem) MemoryAcess(c,&error_flags);
	cod=c->getCodeDataPointer();
	cod_pointer=pos;
	this->ct=c;
}

VirtualMachine& Thread::getVirtualMachine(){
	return *vt;
}

uint16 Thread::isFinalized(){
	return error_flags;
}
uint8* Thread::getPointerMemCode(){
	return mem.getPointerMem();
}

inline uint8 Thread::getNext8(){
	return cod[cod_pointer++];
}
inline uint16 Thread::getNextTwo8(){
	register uint16 x=*((uint16*)(&cod[cod_pointer]));
	cod_pointer+=2;
	return x;
}
inline uint16 Thread::getNext16(){
	register uint16 x=*((uint16*)(&cod[cod_pointer]));
	cod_pointer+=2;
	return x;
}
inline uint32 Thread::getNextTwo16(){
	register uint32 x=*((uint32*)(&cod[cod_pointer]));
	cod_pointer+=4;
	return x;
}
inline uint32 Thread::getNext32(){
	register uint32 x=*((uint32*)(&cod[cod_pointer]));
	cod_pointer+=4;
	return x;
}
inline uint64 Thread::getNextTwo32(){
	register uint64 x=*(uint64*)(&cod[cod_pointer]);
	cod_pointer+=8;
	return x;
}
inline uint48 Thread::getNext48(){
	register uint48 x=*((uint48*)(&cod[cod_pointer]));
	cod_pointer+=6;
	return x;
}
inline uint64 Thread::getNext64(){
	register uint64 x=*(uint64*)(&cod[cod_pointer]);
	cod_pointer+=8;
	return x;
}

inline uint8 Thread::checkUseCode(uint32 tam){
	if(cod_pointer+tam > ct->getCodeDataSize()){
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
