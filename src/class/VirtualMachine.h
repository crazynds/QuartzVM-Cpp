/*
 * VirtualMachine.h
 *
 *  Created on: 2 de mar de 2019
 *      Author: lhlag
 */

#ifndef VIRTUALMACHINE_H_
#define VIRTUALMACHINE_H_
	#include "../lib/Types.h"
	#include "../lib/Dupla.h"
	#include <vector>

	#define OPCODETAM 1<<16

	#define VM_FLAG_RUNNING 0
	#define VM_FLAG_DEBUG_LV 1


	class Contexto;
	class Thread;

	#define ASMJIT_STATIC
	#include "../asmjit/asmjit.h"

	using namespace asmjit;


	typedef uint64 (*Func)(Thread &t);


	class VirtualMachine{
		private:
			std::vector<Dupla<Contexto,uint16>> ct;
			std::vector<Dupla<Thread,uint16>> th;

			JitRuntime rt;

			uint16 tamContex;
			uint16 tamThreads;

			void *VET[OPCODETAM];

			uint16 vm_flags;
			uint16 *func_pos;
			uint16 funcs;

			void setStack();
			void setGerais();
			void setMov();
			void setArit();
			void setCmp();

			void finalize(uint16);
		public:

			VirtualMachine(uint8 = 0);
			~VirtualMachine();

			uint32 run();
			uint32 runCommand();

			void createThread(uint16,uint32);
			uint16 loadContexto(uint8*,uint32);
			uint8 getDebugLevel();


			uint16 checkContexto(uint16);
			void createFunction(uint16,CodeHolder&);
			Contexto& getContexto(uint16);
			JitRuntime& getJitRuntime();
	};


#endif /* VIRTUALMACHINE_H_ */
