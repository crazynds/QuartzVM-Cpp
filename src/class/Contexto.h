/*
 * Contexto.h
 *
 *  Created on: 2 de mar de 2019
 *      Author: lhlag
 */

#ifndef CONTEXTO_H_
#define CONTEXTO_H_
	#include "../lib/Types.h"
	#include "../lib/Dupla.h"
	#include "VirtualMachine.h"
	#include <vector>



	#define MEMORY_BASE_CONTEXT 16384
	//#define _FAST_MODE


	class VirtualMachine;


	#define ASMJIT_STATIC
	#include "../asmjit/asmjit.h"

	using namespace asmjit;


	typedef uint64 (*FuncJit)(uint8 **pontMem,uint64 *pontWork,uint32 goTo);


	class Contexto{
		private:
			std::vector<Dupla<FuncJit,uint32>> funcs;
			uint16 cod_ctx;

			uint16 versao;
			uint8 correcao;


			uint64 devVersion;
			char *nome_geral;
			char *nome_visivel;


		public:
			// memory data
			uint8 *mem;
			uint64 max_mem;

			// code data
			uint8 *cod;
			uint32 cod_len;

			Contexto();
			~Contexto();

			void prepare(uint16,uint8*,uint32);

			FuncJit& createFunction(uint32);
			void clearFunctions(JitRuntime&);

			void incrementMemory();
			void freeMemory(uint48);
			char printVisibleName();

			uint16 getCodContext();
			FuncJit getFunction(uint32);


	};


#endif /* CONTEXTO_H_ */
