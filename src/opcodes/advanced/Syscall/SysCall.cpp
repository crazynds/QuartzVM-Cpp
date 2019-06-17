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
	if(t.checkUseCode(3))return;
	uint8 aux=t.getNext8();
	cout << "[OUTPUT] - {char:" << (char)t.workspace[aux] << "}" << endl;
}
void print_out_num_w(Thread &t){
	if(t.checkUseCode(3))return;
	uint8 aux=t.getNext8();
	cout << "[OUTPUT] - {number:" << t.workspace[aux] << "}" << endl;
}
void print_out_string_mw(Thread &t){
	if(t.checkUseCode(3))return;
	uint8 aux=t.getNext8();
	uint64 b=t.workspace[aux]&0x0000FFFFFFFFFFFF;
	uint8 *str=&t.mem[b];
	cout << "[OUTPUT] - {string:" << str << "}" << endl;
}
void load_context_w_mw(Thread &t){
	if(t.checkUseCode(4))return;
	uint8 pos=t.getNext8();
	char *n;
	{
		uint64 x=t.workspace[t.getNext8()]&0x0000FFFFFFFFFFFF;
		n=(char*)&(t.mem[x]);
	}
	FileLoader cl(n);
	if(cl.getTam()==0)t.workspace[pos]=0;
	else{
		VirtualMachine &vm=t.getVirtualMachine();
		t.workspace[pos]=vm.loadContexto(cl.getCode(),cl.getTam());
	}
}
void get_context_id_w(Thread &t){
	if(t.checkUseCode(3))return;
	t.workspace[t.getNext8()]=t.getContexto().getCodContext();
}
void check_context_id_w(Thread &t){
	if(t.checkUseCode(3))return;
	uint8 pos=t.getNext8();
	t.workspace[pos]=t.getVirtualMachine().checkContexto(uint16(t.workspace[pos]));
}
