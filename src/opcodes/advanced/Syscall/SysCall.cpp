/*
 * SysCall.cpp
 *
 *  Created on: 21 de abr de 2019
 *      Author: lhlag
 */

#include "../../../class/Thread.h"
#include "../../../class/CodeLoader.h"
#include <iostream>


using namespace std;

void print_out_char_w(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	uint8 aux=t.getNext8();
	uint8 debg=t.getVirtualMachine().getDebugLevel();
	if(debg==0) cout << (char)t.workspace[aux];
	else cout << "[OUTPUT] - {char:" << (char)t.workspace[aux] << "}" << endl;
}
void print_out_num_w(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	uint8 aux=t.getNext8();
	uint8 debg=t.getVirtualMachine().getDebugLevel();
	if(debg==0) cout << t.workspace[aux];
	else cout << "[OUTPUT] - {number:" << t.workspace[aux] << "}" << endl;
}
void print_out_string_mmw(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	uint8 aux=t.getNext8();
	uint64 b=t.workspace[aux]&0x0000FFFFFFFFFFFF;
	b+=t.getNext32();
	uint8 *str=&t.mem[b];
	uint8 debg=t.getVirtualMachine().getDebugLevel();
	if(debg==0) cout << str;
	else cout << "[OUTPUT] - {string:" << str << "}" << endl;
}
void print_out_string_m(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	uint64 b=t.getNext48().toInt();
	uint8 *str=&t.mem[b];
	uint8 debg=t.getVirtualMachine().getDebugLevel();
	if(debg==0) cout << str;
	else cout << "[OUTPUT] - {string:" << str << "}" << endl;
}
void load_context_w_mw(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 pos=t.getNext8();
	char *n;
	{
		uint64 x=t.workspace[t.getNext8()]&0x0000FFFFFFFFFFFF;
		n=(char*)&(t.mem[x]);
	}
	FileLoader cl(n,t.getVirtualMachine().getDebugLevel());
	if(cl.getTam()==0)t.workspace[pos]=0;
	else{
		VirtualMachine &vm=t.getVirtualMachine();
		t.workspace[pos]=vm.loadContexto(cl.getCode(),cl.getTam());
	}
}
void get_context_id_w(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	t.workspace[t.getNext8()]=t.getContexto().getCodContext();
}
void check_context_id_w(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	uint8 pos=t.getNext8();
	t.workspace[pos]=t.getVirtualMachine().checkContexto(uint16(t.workspace[pos]));
}


void alloc_res(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint8 pos = t.getNext8();
	uint32 tam = t.getNext32();
	t.workspace[pos]=t.getVirtualMachine().alloc_resorce(tam);
}
void free_res(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	t.getVirtualMachine().free_resorce((void*)t.workspace[t.getNext8()]);
}
