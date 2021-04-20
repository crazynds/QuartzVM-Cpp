/*
 * ModuleJit.h
 *
 *  Created on: 20 de jun de 2020
 *      Author: lhlag
 */

#ifndef OPCODES_MODULES_JIT_MODULEJIT_H_
#define OPCODES_MODULES_JIT_MODULEJIT_H_

#include "../LibraryModuleOpcode.h"

class ModuleJit: public LibraryModuleOpcode {
private:
	uint16 sizeArray;
public:
	ModuleJit();
	virtual ~ModuleJit();


	std::string getNameModule(){
		return "Jit";
	}
	void setInterpretedOpcodes(ManagerOpcodes&);

	bool check_jit(Thread &t,Assembler &a,std::map<uint32,Label> &vector,uint16 comand);
	bool set_opcode_jit(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::map<uint32,Label> &v);


	uint16* getListOpcodes();
	uint16 sizeListOpcodes(){
		return sizeArray;
	}
};

#endif /* OPCODES_MODULES_JIT_MODULEJIT_H_ */
