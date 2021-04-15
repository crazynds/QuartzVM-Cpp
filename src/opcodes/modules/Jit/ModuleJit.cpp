/*
 * ModuleJit.cpp
 *
 *  Created on: 20 de jun de 2020
 *      Author: lhlag
 */

#include "ModuleJit.h"

#include "Jit.h"

ModuleJit::ModuleJit() {
	uint16 *arr=getListOpcodes();
	uint16 x=0;
	while(arr[x]!=0)x++;
	sizeArray=x;
}

ModuleJit::~ModuleJit() {
}

uint16* ModuleJit::getListOpcodes(){
	static uint16 arr[]={
		JIT_FLAG_START,
		JIT_FLAG_EXECUTE,
		JIT_FLAG_ENTER_CODE,
		JIT_FLAG_END,
		0};
	return arr;
}
bool ModuleJit::check_jit(Thread &t,Assembler &a,std::map<uint32,Label> &v,uint16 opcode){
	switch(opcode){
		case JIT_FLAG_ENTER_CODE:{
			if(t.checkUseCode(4))return false;
			t.getNext32();
			int b=0;
			uint32 idLabel=t.getPontCode();

			auto it = v.find(idLabel);
			if(it!=v.end()){
				b=1;
				a.cmp(rax,idLabel);
				a.je(it->first);
			}else{
				Label l = a.newLabel();
				v[idLabel]= l;
				a.cmp(rax,idLabel);
				a.je(l);
			}
		}break;
		default:
			return false;
	}
	return true;
}

bool ModuleJit::set_opcode_jit(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::map<uint32,Label> &v){
	if(jcontent.opcode==JIT_FLAG_ENTER_CODE){
		t.getNext32();
		return true;
	}
	return false;
}

void ModuleJit::setInterpretedOpcodes(ManagerOpcodes& man){
	man.createOpcode(JIT_FLAG_START,(void*)init_jit);
	man.createOpcode(JIT_FLAG_EXECUTE,execute_jit);
	man.createOpcode(JIT_FLAG_ENTER_CODE,enter_jit);
	man.createOpcode(JIT_FLAG_END,end_jit);
}


