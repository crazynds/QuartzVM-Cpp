/*
 * MemoryType.h
 *
 *  Created on: 15 de jun de 2019
 *      Author: lhlag
 */

#ifndef SRC_OPCODES_WORDCODER_MEMORYTYPE_H_
#define SRC_OPCODES_WORDCODER_MEMORYTYPE_H_

	#include "../../lib/Types.h"
	#define RAX W

	class GeralMemory{
	protected:
		char type;
	public:
		char getType(){
			return type;
		}

	};

	class Memoria: GeralMemory{
	private:
		uint48 pos;
	public:
		Memoria(uint48 p){
			type='m';
			pos=p;
		}
		uint48 getPos(){
			return pos;
		}
	};
	class Workspace: GeralMemory{
	private:
		uint8 pos;
	public:
		Workspace(uint8 p){
			type='W';
			pos=p;
		}

		uint8 getPos(){
			return pos;
		}
	};

	class MemoriaPtr: GeralMemory{
	private:
		uint8 regBase,regIndex;
		uint8 shift;
		uint32 inc;
	public:
		MemoriaPtr(Workspace *reg1,Workspace *reg2,uint8 s=0,uint32 i=0){
			inc=i;
			shift=s;
			regBase=reg1->getPos();
			regIndex=reg2->getPos();
			type='M';
			delete reg1;
			delete reg2;
		}
		MemoriaPtr(Workspace *reg1,uint32 i=0){
			inc=i;
			shift=0;
			regBase=reg1->getPos();
			regIndex=0;
			type='P';
			delete reg1;
		}

		uint8 getPosBase(){
			return regBase;
		}
		uint8 getPosIndex(){
			return regIndex;
		}
		uint8 getShift(){
			return shift;
		}
		uint32 getIncrement(){
			return inc;
		}
	};

	class ImediateData: GeralMemory{
	private:
		uint64 value;
	public:
		ImediateData(uint64 v){
			value=v;
			type='I';
		}
		uint64 getValue(){
			return value;
		}
	};

	GeralMemory* w_(uint8 pos);
	GeralMemory* m_(uint48 pos);
	GeralMemory* c_(uint64 dado);
	GeralMemory* ptr_(GeralMemory *r,uint32 inc);
	GeralMemory* ptr_(GeralMemory *reg,GeralMemory *regIndex,uint8 shift,uint32 inc);
	/*
	 * Tipos diferentes de gerais:
	 * m - memoria estática
	 * P - Memoria baseada em 1 workspace e 1 incremento
	 * M - Memoria baseade em 2 workspaces, onde um é a base e outro é o index. Com shift e incremento.
	 * W - Workspace estatica
	 * I - Valor imediato
	 */

#endif /* SRC_OPCODES_WORDCODER_MEMORYTYPE_H_ */
