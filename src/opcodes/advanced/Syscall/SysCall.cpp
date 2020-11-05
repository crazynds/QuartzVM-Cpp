/*
 * SysCall.cpp
 *
 *  Created on: 21 de abr de 2019
 *      Author: lhlag
 */

#include "../../../class/Thread.h"
#include "../../../class/CodeLoader.h"
#include <iostream>





void alloc_res(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint8 pos = t.getNext8();
	uint32 tam = t.getNext32();
	t.workspace[pos]=(uint64)t.getVirtualMachine().alloc_resorce(tam);
}
void free_res(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	t.getVirtualMachine().free_resorce((void*)t.workspace[t.getNext8()]);
}

void alloc_dinamic_res(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 pos = t.getNext8();
	uint32 tam = (uint32) t.workspace[t.getNext8()];
	t.workspace[pos]=(uint64)t.getVirtualMachine().alloc_resorce(tam);
}
void ralloc_dinamic_res(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 pos = t.getNext8();
	uint32 tam = (uint32) t.workspace[t.getNext8()];
	t.workspace[t.getNext8()]=(uint64)t.getVirtualMachine().realloc_resorce((void*)t.workspace[pos],tam);
}

void realloc_res(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint8 pos = t.getNext8();
	uint32 tam = t.getNext32();
	t.workspace[t.getNext8()]=(uint64)t.getVirtualMachine().realloc_resorce((void*)t.workspace[pos],tam);
}
