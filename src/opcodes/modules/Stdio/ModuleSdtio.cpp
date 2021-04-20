/*
 * Sdtio.cpp
 *
 *  Created on: 20 de jun de 2020
 *      Author: lhlag
 */


#include <iostream>
#include <time.h>

#include "ModuleSdtio.h"

#include "../Jit/Jit.h"
#include "../../../class/CodeLoader.h"

void print_out_char_w(Thread&);
void print_out_num_w(Thread&);
void print_out_string_mmw(Thread&);
void print_out_string_m(Thread&);
void load_context_w_mw(Thread&);
void get_context_id_w(Thread&);
void check_context_id_w(Thread&);


void test_func(Thread &t);
void sleep(Thread &t);
void do_nothing(Thread &t);
void print_alloc(Thread &t);


ModuleSdtio::ModuleSdtio() {
	uint16 *arr=getListOpcodes();
	uint16 x=0;
	while(arr[x]!=0)x++;
	sizeArray=x;
}

ModuleSdtio::~ModuleSdtio() {
	// TODO Auto-generated destructor stub
}


uint16* ModuleSdtio::getListOpcodes(){
	static uint16 arr[]={
			DEBUG_PRINT_OUT_MEM,
			DEBUG_PRINT_OUT_RESORCE,
			SLEEP_COMAND,
			HLT_COMAND,
			PRINT_OUT_CHAR,
			PRINT_OUT_NUM,
			PRINT_OUT_STRING_MMW,
			PRINT_OUT_STRING_M,
			LOAD_CONTEXT,
			GET_CONTEXT_ID,
			CHECK_CONTEXT_ID,
		0};
	return arr;
}

void ModuleSdtio::setInterpretedOpcodes(ManagerOpcodes& man){
	man.createOpcode(DEBUG_PRINT_OUT_MEM,(void*)test_func);
	man.createOpcode(DEBUG_PRINT_OUT_RESORCE,(void*)print_alloc);
	man.createOpcode(SLEEP_COMAND,(void*)sleep);
	man.createOpcode(HLT_COMAND,(void*)do_nothing);

	man.createOpcode(PRINT_OUT_CHAR,(void*)print_out_char_w);
	man.createOpcode(PRINT_OUT_NUM,(void*)print_out_num_w);
	man.createOpcode(PRINT_OUT_STRING_MMW,(void*)print_out_string_mmw);
	man.createOpcode(PRINT_OUT_STRING_M,(void*)print_out_string_m);
	man.createOpcode(LOAD_CONTEXT,(void*)load_context_w_mw);
	man.createOpcode(GET_CONTEXT_ID,(void*)get_context_id_w);
	man.createOpcode(CHECK_CONTEXT_ID,(void*)check_context_id_w);

}

bool ModuleSdtio::check_jit(Thread &t,Assembler &a,std::map<uint32,Label> &vector,uint16 comand){
	return false;
}
bool ModuleSdtio::set_opcode_jit(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::map<uint32,Label> &v){
	return false;
}


void do_nothing(Thread &t){
	__asm("hlt");
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif
}

void sleep(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint64 p=t.recoverInStack();
	if(p&((uint64)1<<63)){
		p^=(uint64)1<<63;
		if(( clock() - p )/(double)(CLOCKS_PER_SEC/1000)>t.getNext32())return;
		t.saveInStack(p|(uint64)1<<63);
		t.setPontCode(t.getPontCode()-6);
	}else{
		t.setPontCode(t.getPontCode()-2);
		t.saveInStack(p|(uint64)1<<63);
	}
}

void test_func(Thread &t){
	std::cout << std::dec << "[DEBUG] - MEMORY {" << (int16)t.mem[0];
	for(int p=1;p<35;p++)std::cout << "," << (int16)t.mem[p] ;
	std::cout << "}" << std::endl;
	//for(int p=0;p<20;p++)std::cout << std::bitset<8>(t.workspace[p]) << " \n";

	std::cout << "[DEBUG] - WORKSP {"<< (uint64)t.workspace[0];
	for(int p=1;p<20;p++)std::cout<< "," << (uint64)t.workspace[p];
	std::cout << "}" << std::endl;

#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif
}
void print_alloc(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(7);
#endif
	uint8 *array=(uint8*)t.workspace[t.getNext8()];
	uint32 tam=t.getNext32();
	std::cout << "[DEBUG] - RESORC {" << (int16)array[0];
	for(int p=1;p<tam;p++)std::cout << "," << (int16)array[p] ;
	std::cout << "}" << std::endl;
}

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
		t.workspace[pos]=vm.loadContext(cl.getCode(),cl.getTam());
	}
}
void get_context_id_w(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	t.workspace[t.getNext8()]=t.getContext().getCodContext();
}
void check_context_id_w(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(3))return;
#endif
	uint8 pos=t.getNext8();
	t.workspace[pos]=t.getVirtualMachine().checkContext(uint16(t.workspace[pos]));
}


