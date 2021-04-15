/*
 * Thread.h
 *
 *  Created on: 13 de jun de 2019
 *      Author: seicom
 */

#ifndef SRC_CLASS_THREAD_H_
#define SRC_CLASS_THREAD_H_

	#include "../lib/Types.h"
	#include "Context.h"

	#define RUNNING_ 1<<0
	//#define OVERLOAD_COD_ERROR_ 1<<1
	#define OVERLOAD_MEM_ERROR_ 1<<2
	#define MAX_LIMIT_STACK_ 1<<3
	//#define NO_OPCODE_COMMAND_ 1<<4
	//#define INVALID_OPCODE_JIT_ 1<<5
	#define INVALID_JMP_JIT_ 1<<6
	#define INTERNAL_ERROR_ 1<<7
	#define INVALID_CHANGE_CONTEXT_ 1<<8
	#define MIN_LIMIT_STACK_ 1<<9

	#define THREAD_STACK_SIZE 2048

	class MemoryAcess{
		private:
			uint8 *mem;
			uint64 maxMem;
			uint32 *erro_flags;
		public:
			MemoryAcess(){
				mem= NULL;
				maxMem = 0;
				erro_flags = NULL;
			}
			MemoryAcess(Context *c,uint32 *err){
				mem=c->getMemoryDataDataPointer();
				maxMem=c->getMemoryDataSize().toInt();
				erro_flags=err;
			}
			uint8& operator[](uint64 p){
			#ifdef _FAST_MODE
				return (*mem)[p];
			#else
				if(p<maxMem)return mem[p];
				*erro_flags|=OVERLOAD_MEM_ERROR_;
				return mem[0];
			#endif
			}
			uint8* getPointerMem(){
				return mem;
			}
	};

	#define THREAD_CUSTOM_STACK


	#ifndef THREAD_CUSTOM_STACK
		#include <stack>
	#endif

	class Thread{
		private:
			uint16 id;

			VirtualMachine *vt;
			Context *ct;
			//Memorias de acesso;
			const uint8 *cod;
			uint32 code_len;

			// stack
		#ifdef THREAD_CUSTOM_STACK
			uint64 *stack;
			uint32 stack_max;
			uint32 stack_pointer;
		#else
			std::stack<uint64> stack;
		#endif

			uint32 cod_pointer;



		#ifdef THREAD_CUSTOM_STACK
			void incrementStack(){
				uint32 pos_stack=(uint32)stack_max<<2;
				if(pos_stack>1<<28){
					pos_stack=stack_max+THREAD_STACK_SIZE;
					if(pos_stack>1<<28){
						error_flags|=MAX_LIMIT_STACK_;
						return;
					}
				}
				uint64 *aux=new uint64[pos_stack];
				memcpy(aux,stack,stack_max*sizeof(64));
				stack_max=pos_stack;
				delete[] stack;
				stack=aux;
			}

			void decrementStack(){
				uint32 pos_stack=(uint32)stack_max>>1;
				uint64 *aux=new uint64[pos_stack];
				memcpy(aux,stack,pos_stack*sizeof(64));
				stack_max=pos_stack;
				delete[] stack;
				stack=aux;
			}
		#endif

		public:

			MemoryAcess mem;				//Gerencia o acesso a memoria;
			uint64 workspace[257];  		//para não haver invasão de memoria;

			uint32 error_flags;
			uint8 compare_flags;


			Thread(VirtualMachine*,Context*,uint32,uint16);
			Thread();
			~Thread();


			void savePoint();
			void saveInStack(uint64);
			uint64 recoverInStack();
			void recoverPoint();
			void changeContext(Context*,uint32 pos = 0);

			uint8 getNext8();
			uint16 getNext16();
			uint32 getNext32();
			uint48 getNext48();
			uint64 getNext64();
			uint16 getNextTwo8();
			uint32 getNextTwo16();
			uint64 getNextTwo32();

			uint8 checkUseCode(uint32);
			uint8* getPointerMemCode();
			uint16 isFinalized();
			uint32 getPontCode();
			VirtualMachine& getVirtualMachine();
			Context& getContext();


			void setPontCode(uint32);
			void setPontCodeCtx(uint48);

			uint8 operator==(const Thread &t){
				return (vt==t.vt && ct==t.ct && stack==t.stack);
			}

			JitRuntime& getJitRuntime();
	};


#endif /* SRC_CLASS_THREAD_H_ */
