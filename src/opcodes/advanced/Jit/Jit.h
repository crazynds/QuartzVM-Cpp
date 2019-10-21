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

	#define ASMJIT_STATIC
	#define ASMJIT_NO_LOGGING
	#include "../../../asmjit/asmjit.h"
	using namespace asmjit;
	using namespace asmjit::x86;

	#include "../../../lib/Types.h"
	#include "../../../class/Thread.h"
	#include "../../../class/VirtualMachine.h"
	#include "../../Opcode.h"

	#define OK_JIT_STATE 0x00
	#define ERROR_JMP_ENTER_JIT_STATE 0x20
	#define LIXO_REG 0xAF001FA9E22500A1

	#include "AssemblerJIT.h"

	struct JitContentsAuxiliar{
		uint16 opcode;
		uint32 maxCode;
		uint32 minCode;
		uint8 type;
	};

	void init_jit(Thread &t);
	void end_jit(Thread &t);
	void execute_jit(Thread &t);
	void enter_jit(Thread &t);


	void definesPositionsThread();
	uint32 getWorkspace();


	void pushRegisters(AssemblerJIT &a);

	void popRegisters(AssemblerJIT &a);

	static Gp memory=rdi;
	static Gp workspace=rsi;

	static Gp qreg[8]= {r8,r9,r10,r11,r12,r13,r14,r15};
	static Gp dreg[8]= {r8d,r9d,r10d,r11d,r12d,r13d,r14d,r15d};
	static Gp wreg[8]= {r8w,r9w,r10w,r11w,r12w,r13w,r14w,r15w};
	static Gp breg[8]= {r8b,r9b,r10b,r11b,r12b,r13b,r14b,r15b};

#endif /* SRC_OPCODES_JIT_H_ */
