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

bool ModuleJit::check_jit(Thread &t,Assembler &a,std::vector<Dupla<Label,uint32>> &v,uint16 opcode){
	switch(opcode){
		case JIT_FLAG_ENTER_CODE:{
			if(t.checkUseCode(4))return false;
			t.getNext32();
			int b=0;
			uint32 idLabel=t.getPontCode();
			for(int x=0;x<v.size();x++){
				if(v[x].getSecond()==idLabel){
					b=1;
					a.cmp(rax,idLabel);
					a.je(v[x].getFirst());
					break;
				}
			}
			if(b)break;
			Label *jmp=new Label();
			*jmp=a.newLabel();
			uint32 aux=v.size();
			v.resize(aux+1);
			v[aux].setFirst(jmp);
			v[aux].setSecond(idLabel);
			a.cmp(rax,idLabel);
			a.je(*jmp);
		}break;
		default:
			return false;
	}
	return true;
}

bool ModuleJit::set_opcode_jit(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v){
	if(jcontent.opcode==JIT_FLAG_ENTER_CODE){
		t.getNext32();
		return true;
	}
	return false;
}

void ModuleJit::setInterpretedOpcodes(ManagerOpcodes& man){
	man.createOpcode(JIT_FLAG_START,init_jit);
	man.createOpcode(JIT_FLAG_EXECUTE,execute_jit);
	man.createOpcode(JIT_FLAG_ENTER_CODE,enter_jit);
	man.createOpcode(JIT_FLAG_END,end_jit);
}


