/*
 * ManagerOpcodes.h
 *
 *  Created on: 20 de jun de 2020
 *      Author: lhlag
 */

#ifndef SRC_CLASS_VIRTUALMACHINE_MANAGEROPCODES_H_
#define SRC_CLASS_VIRTUALMACHINE_MANAGEROPCODES_H_


	#include "../../lib/Types.h"
	#include "../../lib/asmjit.h"

	using namespace asmjit;

	class LibraryModuleOpcode;


	class ManagerOpcodes {
	private:
		JitRuntime rt;

		//Instruçõs iniciadas em JIT
		uint16 *func_pos;
		uint16 funcs;
		void **VET;


		//Modulos de opcodes
		LibraryModuleOpcode **modulesArray;
		uint16 lenModules;

		uint8 debugLevel;


		void loadOpcodesModules();

	public:
		ManagerOpcodes(void **VET,uint8 debugLevel);
		virtual ~ManagerOpcodes();

		void createOpcodeJit(uint16,CodeHolder&);
		void createOpcode(uint16,void*);
		void loadLibraryModuleOpcode(LibraryModuleOpcode *);

		void releaseOpcodesJit();



		void setDebugLevel(uint8);

		uint16 sizeFuncsJit();
		uint16 sizeModules();

		JitRuntime& getJitRuntime();
		void **getVetorOpcode();
		LibraryModuleOpcode** getModules();
	};

#endif /* SRC_CLASS_VIRTUALMACHINE_MANAGEROPCODES_H_ */
