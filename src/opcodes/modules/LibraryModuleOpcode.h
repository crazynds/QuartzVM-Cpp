/*
 * LibraryModuleOpcode.h
 *
 *  Created on: 19 de jun de 2020
 *      Author: lhlag
 */

#ifndef SRC_OPCODES_LIBRARYMODULEOPCODE_H_
#define SRC_OPCODES_LIBRARYMODULEOPCODE_H_

#include "Jit/Jit.h"


class LibraryModuleOpcode {
public:
	LibraryModuleOpcode(){
	}
	virtual ~LibraryModuleOpcode(){
	}

	virtual std::string getNameModule()=0;
	virtual uint16* getListOpcodes()=0;
	virtual uint16 sizeListOpcodes()=0;
	virtual void setInterpretedOpcodes(ManagerOpcodes&)=0;
	virtual bool check_jit(Thread &t,Assembler &a,std::vector<Dupla<Label,uint32>> &vector,uint16 comand)=0;
	virtual bool set_opcode_jit(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v)=0;
};



#endif /* SRC_OPCODES_LIBRARYMODULEOPCODE_H_ */
