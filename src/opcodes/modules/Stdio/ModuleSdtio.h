/*
 * Sdtio.h
 *
 *  Created on: 20 de jun de 2020
 *      Author: lhlag
 */

#ifndef OPCODES_MODULES_STDIO_MODULESDTIO_H_
#define OPCODES_MODULES_STDIO_MODULESDTIO_H_


#include "../LibraryModuleOpcode.h"

class ModuleSdtio: public LibraryModuleOpcode {
private:
	uint16 sizeArray;
public:
	ModuleSdtio();
	virtual ~ModuleSdtio();


	std::string getNameModule(){
		return "Stdio";
	}
	void setInterpretedOpcodes(ManagerOpcodes&);
	bool check_jit(Thread &t,Assembler &a,std::map<uint32,Label> &vector,uint16 comand);
	bool set_opcode_jit(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::map<uint32,Label> &v);


	uint16* getListOpcodes();
	uint16 sizeListOpcodes(){
		return sizeArray;
	}
};

#endif /* OPCODES_MODULES_STDIO_MODULESDTIO_H_ */
