/*
 * Jit.h
 *
 *  Created on: 26 de abr de 2019
 *      Author: lhlag
 */

#ifndef JIT_H_
#define JIT_H_

	#include <vector>
	#include <stdio.h>

	#include "../../../lib/asmjit.h"
	#include "../../../lib/Types.h"
	#include "../../../class/Thread.h"
	#include "../../../class/VirtualMachine/VirtualMachine.h"
	#include "../../Opcode.h"

	using namespace asmjit;
	using namespace asmjit::x86;

	#define OK_JIT_STATE 0x00
	#define ERROR_JMP_ENTER_JIT_STATE 0x20

	#include "AssemblerJIT.h"

	struct JitContentsAuxiliar{
		uint16 opcode;
		uint32 maxCode;
		uint32 minCode;
		uint8 sign_operation; // 'u' = sem sinal = unsigned / 's' = com sinal = signed
	};

	void init_jit(Thread &t);
	void end_jit(Thread &t);
	void execute_jit(Thread &t);
	void enter_jit(Thread &t);


	void definesPositionsThread();
	uint32 getWorkspace();


	void pushRegisters(AssemblerJIT &a);

	void popRegisters(AssemblerJIT &a);


#endif /* SRC_OPCODES_JIT_H_ */
