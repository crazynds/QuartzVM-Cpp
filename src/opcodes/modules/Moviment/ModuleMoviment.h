/*
 * WorkspaceMov.h
 *
 *  Created on: 19 de jun de 2020
 *      Author: lhlag
 */

#ifndef SRC_OPCODES_MODULES_WORKSPACEMOV_H_
#define SRC_OPCODES_MODULES_WORKSPACEMOV_H_

#include "../LibraryModuleOpcode.h"

class ModuleMoviment: public LibraryModuleOpcode {
private:
	uint16 sizeArray;
public:
	ModuleMoviment();
	virtual ~ModuleMoviment();

	std::string getNameModule(){
		return "WorkspaceMov";
	}
	void setInterpretedOpcodes(ManagerOpcodes&);
	bool check_jit(Thread &t,Assembler &a,std::vector<Dupla<Label,uint32>> &vector,uint16 comand);
	bool set_opcode_jit(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v);


	uint16* getListOpcodes();
	uint16 sizeListOpcodes(){
		return sizeArray;
	}
};

#endif /* SRC_OPCODES_MODULES_WORKSPACEMOV_H_ */
