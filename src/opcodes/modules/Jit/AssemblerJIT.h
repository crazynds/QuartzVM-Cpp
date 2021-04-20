/*
 * AssemblerJIT.h
 *
 *  Created on: 21 de jun de 2019
 *Author: lhlag
 */

#ifndef SRC_LIB_ASSEMBLERJIT_H_
#define SRC_LIB_ASSEMBLERJIT_H_

	#include "../../../lib/asmjit.h"
	#include "../../../lib/exception/VMException.h"
	const Gp memory=rdi;
	const Gp workspace=rsi;

	const Gp qreg[8]= {r8,r9,r10,r11,r12,r13,r14,r15};
	const Gp dreg[8]= {r8d,r9d,r10d,r11d,r12d,r13d,r14d,r15d};
	const Gp wreg[8]= {r8w,r9w,r10w,r11w,r12w,r13w,r14w,r15w};
	const Gp breg[8]= {r8b,r9b,r10b,r11b,r12b,r13b,r14b,r15b};


	const static uint64 SUPORT_48_BITS = 0x0000FFFFFFFFFFFF;
	const static uint64 INVERTED_SUPORT_48_BITS = ~(0x0000FFFFFFFFFFFF);


	class AssemblerJIT:public Assembler{
	private:
		uint8 vez=0;


		//free registers RAX,RBX,RCX,RDX
		uint64 val_reg[4]={0,0,0,0};
		//oq contem dentro do registrador
		//se 0 contem nada, está livre
		//se 1 contem valor estático
		//se 2 contem valor de workspace
		//se 3 contem valor de workspace usado atualmente
		//se 4 contem valor estático usado atualmente
		//se 5 contem valor aleatorio usado atualmente
		int8 t_reg[4]={0,0,0,0};

		uint8 use_reg[256]={0};


		Gp getRegister(uint16 x,uint8 tam){
			switch(tam){
			case 8:
				switch(x){
				case 2:
					return al;
				case 1:
					return bl;
				case 3:
					return cl;
				case 0:
					return dl;
				}
				break;
			case 16:
				switch(x){
				case 2:
					return ax;
				case 1:
					return bx;
				case 3:
					return cx;
				case 0:
					return dx;
				}
				break;
			case 32:
				switch(x){
				case 2:
					return eax;
				case 1:
					return ebx;
				case 3:
					return ecx;
				case 0:
					return edx;
				}
				break;
			case 64:
				switch(x){
				case 2:
					return rax;
				case 1:
					return rbx;
				case 3:
					return rcx;
				case 0:
					return rdx;
				}
				break;
			}
			throw VMException(_ERROR_JIT_CREATE_NOT_FOUND_REGISTER_TYPE);
		}

		uint8 getNextRegister(){
			uint8 selected=255;
			uint8 type=255;
			if(t_reg[vez]==0){
				selected=vez;
				type=0;
			}else{
				for(int x=0;x<4;x++)
					if(t_reg[x]==0){
						selected=vez=x;
						type=0;
						break;
					}else if(type>t_reg[x]){
						selected=vez=x;
						type=t_reg[x];
					}else if(type==2 && t_reg[x]==2){
						uint8 life1 = uint8(val_reg[x]>>8);
						uint8 life2 = uint8(val_reg[selected]>>8);
						if(life1<life2){
							selected=vez=x;
							type=t_reg[x];
						}
					}
			}
			if(vez<3)vez++;
			else vez=0;
			if(selected>=4 || type>2){
				throw VMException(_ERROR_JIT_CREATE_ANY_REGISTER_FREE);
			}else{
				clearRegister(selected);
				t_reg[selected]=5;
				return selected;
			}
		}

		Gp getNextRegisterValue(uint8 size,uint64 val){
			uint8 selected = getNextRegister();
			Gp reg=getRegister(selected,size);
			switch(size){
			case 8:
				mov(reg,uint8(val));
				break;
			case 16:
				mov(reg,uint16(val));
				break;
			case 32:
				mov(reg,uint32(val));
				break;
			case 64:
			default:
				mov(reg,val);
				break;
			}
			t_reg[selected]=4;
			val_reg[selected]=val;
			return reg;
		}

		Gp getNextRegisterWorkspace(uint8 size,uint8 pos){
			uint8 selected = getNextRegister();
			Gp reg=getRegister(selected,64);
			mov(reg,ptr(workspace,8*pos));
			t_reg[selected]=3;
			val_reg[selected]=pos;
			return getRegister(selected,size);
		}

	public:

		AssemblerJIT(CodeHolder* code):Assembler(code){
			//qreg free for use r8-r15(8) para workspace
			//rax - rbx - rcx - rdx  para calculos normais
			//rdi - rsi para uso de ponteiros para mem e workspace
			push(rbx);
			push(rdi);
			push(rsi);
			push(r12);
			push(r13);
			push(r14);
			push(r15);
			for(uint16 x=0;x<16;x++)prefetcht0(ptr(workspace,8*x));	//Move a workspace para perto do processador nos caches.
			mov(workspace,rdx); 									// RSI - WORKSPACE THREAD
			mov(memory,rcx); 										// RDI - MEMORIA Context
			push(r8);												// THREAD - ARMAZENADA
			mov(rax,r9); 											// PRAMETRO goTo
			for(uint16 x=0;x<8;x++)mov(qreg[x],qword_ptr(workspace,x*8));
			cld();
		}
		~AssemblerJIT(){
			clearRegisters();

			for(uint16 x=0;x<8;x++)mov(qword_ptr(workspace,x*8),qreg[x]);
			add(rsp,0x8);
			pop(r15);
			pop(r14);
			pop(r13);
			pop(r12);
			pop(rsi);
			pop(rdi);
			pop(rbx);
			ret();
		}

		Mem getMemory48bitsSuport(){
			return ptr(uint64(&SUPORT_48_BITS));
		}
		Mem getMemory48bitsInvertedSuport(){
			return ptr(uint64(&INVERTED_SUPORT_48_BITS));
		}

		void ignoreWorkspace(uint8 pos){
			if(pos<8)return;
			for(int x=0;x<4;x++){
				if((t_reg[x]==2 || t_reg[x]==3)&&(uint8(val_reg[x])==pos)){
					t_reg[x]=0;
					return;
				}
			}
		}
		bool hasWorkspace(uint8 pos){
			if(pos<8)return true;
			for(int x=0;x<4;x++){
				if((t_reg[x]==2 || t_reg[x]==3)&&(uint8(val_reg[x])==pos)){
					return true;
				}
			}
			return false;
		}


		void clearRegister(uint8 pos){
			if(pos>=4)return;
			switch(t_reg[pos]){
			case 0:
			case 5:
				//nada está livre
				break;
			case 1:
			case 4:
				//contém valor estático, pode passar
				break;
			case 2:
			case 3:
				uint8 reg = uint8(val_reg[pos]);
				mov(ptr(workspace,reg*8),getRegister(pos,64));
				break;
			}
			t_reg[pos]=0;
		}

		void clearRegisters(){
			nextState();
			for(int x=0;x<4;x++)
				clearRegister(x);
			for(int x=0;x<255;x++){
				use_reg[x]=0;
			}
		}
		void nextState(){
			for(int x=0;x<255;x++){
				if(use_reg[x]>0)use_reg[x]--;
			}
			for(int x=0;x<4;x++){
				switch(t_reg[x]){
				case 3:{
					uint8 newLife=6;
					t_reg[x]=2;
					val_reg[x]|=(newLife)<<8;
				}break;
				case 4:{
					t_reg[x]=1;
				}break;
				case 5:{
					t_reg[x]=0;
				}break;
				case 2:{
					uint8 life = uint8(val_reg[x]>>8);
					if(life==0)clearRegister(x);
					else {
						val_reg[x]=((life-1)<<8)|uint8(val_reg[x]);
					}
				}break;
				}
			}
		}

		Gp getRegisterWorkspace(uint8 size,uint8 pos){
			use_reg[pos]+=5;
			if(pos<8){
				switch(size){
				case 8:
					return breg[pos];
				case 16:
					return wreg[pos];
				case 32:
					return dreg[pos];
				case 64:
				default:
					return qreg[pos];
				}
			}else{
				for(int x=0;x<4;x++){
					if((t_reg[x]==2 || t_reg[x]==3)&&(uint8(val_reg[x])==pos)){
						t_reg[x]=3;
						return getRegister(x,size);
					}
				}
				return getNextRegisterWorkspace(size,pos);
			}
		}
		Gp getRegisterImediateValue(uint8 size,uint64 val){
			for(int x=0;x<4;x++){
				if(t_reg[x]==1 && val_reg[x]==val){
					t_reg[x]=4;
					return getRegister(x,size);
				}
			}
			return getNextRegisterValue(size,val);
		}
		Gp getRegister(uint8 size){
			return getRegister(getNextRegister(),size);
		}
		Gp getRegisterWorkspace8(uint8 pos){
			return getRegisterWorkspace(8,pos);
		}
		Gp getRegisterWorkspace16(uint8 pos){
			return getRegisterWorkspace(16,pos);
		}
		Gp getRegisterWorkspace32(uint8 pos){
			return getRegisterWorkspace(32,pos);
		}
		Gp getRegisterWorkspace64(uint8 pos){
			return getRegisterWorkspace(64,pos);
		}
		Gp getRegisterImediateValue8(uint8 val){
			return getRegisterImediateValue(8,val);
		}
		Gp getRegisterImediateValue16(uint16 val){
			return getRegisterImediateValue(16,val);
		}
		Gp getRegisterImediateValue32(uint32 val){
			return getRegisterImediateValue(32,val);
		}
		Gp getRegisterImediateValue64(uint64 val){
			return getRegisterImediateValue(64,val);
		}
		Gp getRegister8(){
			return getRegister(8);
		}
		Gp getRegister16(){
			return getRegister(16);
		}
		Gp getRegister32(){
			return getRegister(32);
		}
		Gp getRegister64(){
			return getRegister(64);
		}
	};


#endif /* SRC_LIB_ASSEMBLERJIT_H_ */
