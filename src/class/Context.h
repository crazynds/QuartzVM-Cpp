/*
 * Context.h
 *
 *  Created on: 2 de mar de 2019
 *      Author: lhlag
 */

#ifndef Context_H_
#define Context_H_
	#include "../lib/Types.h"
	#include <vector>
	#include <map>
	#include "VirtualMachine/VirtualMachine.h"



	#define MEMORY_BASE_CONTEXT 16*KB
	//#define _FAST_MODE


	class VirtualMachine;

	#include "../lib/asmjit.h"

	using namespace asmjit;


	typedef uint64 (*FuncJit)(uint8 *pontMem,uint64 *pontWork,Thread &t,uint32 goTo);


	class Context{
		private:
			std::map<uint32,FuncJit> functions;
			//std::vector<Dupla<FuncJit,uint32>> funcs;
			uint16 id;

			uint16 versao;
			uint8 correcao;


			uint64 devVersion;
			char *nome_geral;
			char *nome_visivel;


			// memory data
			uint8 *mem;
			uint64 max_mem;

			// code data
			uint8 *cod;
			uint32 cod_len;



			void prepare(uint16,uint8*,uint32);

		public:


			Context(VirtualMachine*,uint16,uint8*,uint32);
			~Context();

			FuncJit& createFunction(uint32);
			void clearFunctions(JitRuntime&);

			char printVisibleName();

			uint16 getCodContext();
			FuncJit getFunction(uint32);

			void set16InCode(uint32,uint16);
			void set32InCode(uint32,uint32);

			uint8* getMemoryDataDataPointer();
			uint48 getMemoryDataSize();

			const uint8* getCodeDataPointer();
			uint32 getCodeDataSize();


	};


#endif /* Context_H_ */
