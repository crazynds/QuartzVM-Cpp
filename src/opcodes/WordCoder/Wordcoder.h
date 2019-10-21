/*
 * Wordcoder.h
 *
 *  Created on: 13 de mar de 2019
 *      Author: Luiz Henrique
 */

#ifndef OPCODES_WORDCODER_WORDCODER_H_
#define OPCODES_WORDCODER_WORDCODER_H_

	#include "../../lib/Types.h"
	#include "../Opcode.h"
	#include "VERSION.h"
	#include "MemoryType.h"

	#define WAX w_(0)
	#define WBX w_(1)
	#define WCX w_(2)
	#define WDX w_(3)
	#define WEX w_(4)
	#define WFX w_(5)
	#define WGX w_(6)
	#define WHX w_(7)
	#define WIX w_(8)
	#define WJX w_(9)
	#define WKX w_(10)
	#define WLX w_(11)
	#define WMX w_(12)
	#define WNX w_(13)
	#define WOX w_(14)
	#define WPX w_(15)

	class Wordcoder{
		private:
			uint8 *bytecode;
			uint32 maxTam;
			uint32 tam;
			uint16 atual;
			uint32 jit_pos=1;
			uint32 localLastCab;

			void expand(){
				uint8 *aux=new uint8[maxTam+256];
				for(uint32 x=0;x<maxTam;x++){
					aux[x]=bytecode[x];
				}
				maxTam+=256;
				delete[] bytecode;
				bytecode=aux;
			}
			void addCabecalho8(uint8 a){
				if(tam+1>=maxTam)expand();
				(*((uint16*)&bytecode[5]))++;
				for(uint32 x=tam-1;x>=localLastCab;x--){
					bytecode[x+1]=bytecode[x];
				}
				bytecode[localLastCab]=a;
				localLastCab++;
				tam++;
			}
			void addCabecalho16(uint16 a){
				if(tam+2>=maxTam)expand();
				(*((uint16*)&bytecode[5]))+=2;
				for(uint32 x=tam-1;x>=localLastCab;x--){
					bytecode[x+2]=bytecode[x];
				}
				setIn16(localLastCab,a);
				localLastCab+=2;
				tam+=2;
			}
			void addCabecalho32(uint32 a){
				if(tam+4>=maxTam)expand();
				(*((uint16*)&bytecode[5]))+=4;
				for(uint32 x=tam-1;x>=localLastCab;x--){
					bytecode[x+4]=bytecode[x];
				}
				setIn32(localLastCab,a);
				localLastCab+=4;
				tam+=4;
			}
			void addCabecalho64(uint64 a){
				if(tam+8>=maxTam)expand();
				(*((uint16*)&bytecode[5]))+=8;
				for(uint32 x=tam-1;x>=localLastCab;x--){
					bytecode[x+8]=bytecode[x];
				}
				setIn64(localLastCab,a);
				localLastCab+=8;
				tam+=8;
			}
			void set8(uint8 x){
				if(tam+1>=maxTam)expand();
				bytecode[tam]=x;
				tam++;
			}

			void set32(uint32 x){
				if(tam+4>=maxTam)expand();
				uint32 *p=(uint32*)&bytecode[tam];
				*p=x;
				tam+=4;
			}

			void set48(uint48 x){
				if(tam+6>=maxTam)expand();
				uint48 *p=(uint48*)&bytecode[tam];
				*p=x;
				tam+=6;
			}

			void set64(uint64 x){
				if(tam+8>=maxTam)expand();
				uint64 *p=(uint64*)&bytecode[tam];
				*p=x;
				tam+=8;
			}
			void incrementTamCabecalho(){
				(*((uint16*)&bytecode[9]))++;
			}

			void setIn16(uint32 ponto, uint16 valor){
				*((uint16*)&bytecode[ponto])=valor;
			}
			void setIn64(uint32 ponto, uint64 valor){
				*((uint64*)&bytecode[ponto])=valor;
			}

			void inc_w(uint8 m1){
				set16(INC_W);
				set8(m1);
			}
			void dec_w(uint8 m1){
				set16(DEC_W);
				set8(m1);
			}
			void inc_m(uint48 m1){
				set16(INC_M);
				set48(m1);
			}
			void dec_m(uint48 m1){
				set16(DEC_M);
				set48(m1);
			}

			void call_c(uint32 m1){
				set16(CALL_C);
				set32(m1);
			}
			void call_m(uint48 m1){
				set16(CALL_M);
				set48(m1);
			}
			void call_w(uint8 m1){
				set16(CALL_W);
				set8(m1);
			}

			void push_w(uint8 m1){
				set16(PUSH_W);
				set8(m1);
			}
			void push_c(uint64 m1){
				set16(PUSH_C);
				set64(m1);
			}
			void pop_w(uint8 m1){
				set16(POP_W);
				set8(m1);
			}
			void soma_m_c(uint48 m1,uint64 m2){
				set16(atual+SOMA_M_C);
				set48(m1);
				setAtual(m2);
			}
			void soma_w_c(uint8 m1,uint64 m2){
				set16(atual+SOMA_W_C);
				set8(m1);
				setAtual(m2);
			}
			void soma_w_m(uint8 m1,uint48 m2){
				set16(atual+SOMA_W_M);
				set8(m1);
				set48(m2);
			}
			void soma_w_w(uint8 m1,uint8 m2){
				set16(atual+SOMA_W_W);
				set8(m1);
				set8(m2);
			}
			void sub_m_c(uint48 m1,uint64 m2){
				set16(atual+SUB_M_C);
				set48(m1);
				setAtual(m2);
			}
			void sub_w_c(uint8 m1,uint64 m2){
				set16(atual+SUB_W_C);
				set8(m1);
				setAtual(m2);
			}
			void sub_w_m(uint8 m1,uint48 m2){
				set16(atual+SUB_W_M);
				set8(m1);
				set48(m2);
			}
			void sub_w_w(uint8 m1,uint8 m2){
				set16(atual+SUB_W_W);
				set8(m1);
				set8(m2);
			}
			void mov_mmww_c(uint8 base,uint8 index,uint8 shift,uint32 inc,uint64 value){
				set16(atual+MOV_MMWW_C);
				set32(inc);
				set8(base);
				set8(index);
				set8(shift);
				set64(value);
			}
			void mov_mmww_w(uint8 base,uint8 index,uint8 shift,uint32 inc,uint8 val){
				set16(atual+MOV_MMWW_W);
				set32(inc);
				set8(base);
				set8(index);
				set8(shift);
				set8(val);
			}
			void mov_w_mmww(uint8 dst,uint8 base,uint8 index,uint8 shift,uint32 inc){
				set16(atual+MOV_W_MMWW);
				set8(dst);
				set32(inc);
				set8(base);
				set8(index);
				set8(shift);
			}
			void mov_mmww_mmww(uint8 base,uint8 index,uint8 shift,uint32 inc,uint8 base2,uint8 index2,uint8 shift2,uint32 inc2){
				set16(atual+MOV_MMWW_MMWW);
				set32(inc);
				set8(base);
				set8(index);
				set8(shift);
				set32(inc2);
				set8(base2);
				set8(index2);
				set8(shift2);
			}
			void mov_mmw_mmw(uint8 m1,uint32 inc1, uint8 m2, uint32 inc2){
				set16(atual+MOV_MMW_MMW);
				set32(inc1);
				set8((uint8)m1);
				set32(inc2);
				set8((uint8)m2);
			}
			void mov_w_mmw(uint8 m1, uint8 m2, uint32 inc2){
				set16(atual+MOV_W_MMW);
				set8((uint8)m1);
				set32(inc2);
				set8((uint8)m2);
			}
			void mov_mmw_w(uint8 m1,uint32 inc1, uint8 m2){
				set16(atual+MOV_MMW_W);
				set32(inc1);
				set8((uint8)m1);
				set8((uint8)m2);
			}
			void mov_mmw_c(uint8 m1,uint32 inc,uint64 m2){
				set16(atual+MOV_MMW_C);
				set32(inc);
				set8(m1);
				setAtual(m2);
			}

			void mov_mmw_m(uint8 m1,uint32 inc,uint48 m2){
				set16(atual+MOV_MMW_M);
				set32(inc);
				set8(m1);
				set48(m2);
			}
			void mov_m_mmw(uint48 m1,uint8 m2,uint32 inc){
				set16(atual+MOV_M_MMW);
				set48(m1);
				set32(inc);
				set8(m2);
			}

			void mov_m_c(uint48 m1,uint64 m2){
				set16(atual+MOV_M_C);
				set48(m1);
				setAtual(m2);
			}
			void mov_m_m(uint48 m1,uint48 m2){
				set16(atual+MOV_M_M);
				set48(m1);
				set48(m2);
			}
			void mov_m_w(uint48 m1,uint8 m2){
				set16(atual+MOV_M_W);
				set48(m1);
				set8(m2);
			}
			void mov_w_c(uint8 m1,uint64 m2){
				set16(atual+MOV_W_C);
				set8(m1);
				setAtual(m2);
			}
			void mov_w_m(uint8 m1,uint48 m2){
				set16(atual+MOV_W_M);
				set8(m1);
				set48(m2);
			}
			void mov_w_w(uint8 m1,uint8 m2){
				set16(atual+MOV_W_W);
				set8(m1);
				set8(m2);
			}
		public:

			Wordcoder(int x=0){
				bytecode=new uint8[256];
				tam=0;
				maxTam=256;

				atual=P_UINT8;
				if(x==0){
					set16(0);
					set16(VERSION_VM);
					set8(CORRECION_VM);
					set32(2);
					set16(0);
				}
				localLastCab=getTam();
			}
			~Wordcoder(){
				delete[] bytecode;
			}

			void mov(GeralMemory*,GeralMemory*);
			void add(GeralMemory*,GeralMemory*);
			void sub(GeralMemory*,GeralMemory*);
			void inc(GeralMemory*);
			void dec(GeralMemory*);
			void call(GeralMemory*);
			void pop(GeralMemory*);
			void push(GeralMemory*);
			void setString(GeralMemory*,char*);
			void printNum(GeralMemory*);
			void printChar(GeralMemory*);
			void printString(GeralMemory*);

			void setDevVersion(uint64 x);
			void setGeralName(const char*);

			void setIn32(uint32 ponto, uint32 valor){
				*((uint32*)&bytecode[ponto])=valor;
			}
			void set16(uint16 x){
				if(tam+2>=maxTam)expand();
				uint16 *p=(uint16*)&bytecode[tam];
				*p=x;
				tam+=2;
			}
			void finalize(){
				set16(0);
			}

			void copy_m_m_c(uint48 m1,uint48 m2,uint32 m3){
				set16(atual+COPY_M_M_C);
				set48(m1);
				set48(m2);
				set32(m3);
			}


			void copy_m_m_w(uint48 m1,uint48 m2,uint8 m3){
				set16(atual+COPY_M_M_W);
				set48(m1);
				set48(m2);
				set8(m3);
			}
			void copy_mw_mw_c(uint8 m1,uint8 m2,uint32 m3){
				set16(atual+COPY_MW_MW_C);
				set8(m1);
				set8(m2);
				set32(m3);
			}
			void copy_mw_mw_w(uint8 m1,uint8 m2,uint8 m3){
				set16(atual+COPY_MW_MW_W);
				set8(m1);
				set8(m2);
				set8(m3);
			}

			void defineUI8(){
				atual=P_UINT8;
			}
			void defineUI16(){
				atual=P_UINT16;
			}
			void defineUI32(){
				atual=P_UINT32;
			}
			void defineUI48(){
				atual=P_UINT48;
			}
			void defineUI64(){
				atual=P_UINT64;
			}

			void defineI8(){
				atual=P_INT8;
			}
			void defineI16(){
				atual=P_INT16;
			}
			void defineI32(){
				atual=P_INT32;
			}
			void defineI48(){
				atual=P_INT48;
			}
			void defineI64(){
				atual=P_INT64;
			}

			uint32 getTam(){
				return tam;
			}


			void ret(){
				set16(RETURN);
			}

			uint8* getBytecode(){
				return bytecode;
			}

			void call_ctx_c(uint8 m1,uint32 m2){
				set16(CALL_CTX_C);
				set8(m1);
				set32(m2);
			}
			void call_ctx_w(uint8 m1,uint8 m2){
				set16(CALL_CTX_W);
				set8(m1);
				set8(m2);
			}

			void load_context_w_mw(uint8 m1,uint8 m2){
				set16(LOAD_CONTEXT);
				set8(m1);
				set8(m2);
			}

			void set_string_m(char *str,uint64 m1){
				int x=0;
				uint16 aux=atual;
				defineI8();
				do{
					mov_m_c(m1+x,str[x]);
				}while(str[x++]!='\0');
				atual=aux;
			}
			void setAtual(uint64 val){
				switch(atual){
				case P_UINT8:
				case P_INT8:
					set8((uint8)val);
					break;
				case P_UINT16:
				case P_INT16:
					set16((uint16)val);
					break;
				case P_UINT32:
				case P_INT32:
					set32((uint32)val);
					break;
				case P_UINT48:
				case P_INT48:
					set48((uint48)val);
					break;
				case P_UINT64:
				case P_INT64:
					set64((uint64)val);
					break;
				}
			}

			void get_context_id(uint8 m1){
				set16(GET_CONTEXT_ID);
				set8(m1);
			}

			void print_out_char_w(uint8 m1){
				set16(PRINT_OUT_CHAR);
				set8(m1);
			}
			void print_out_num_w(uint8 m1){
				set16(PRINT_OUT_NUM);
				set8(m1);
			}
			void print_out_string_mmw(uint8 m1,uint32 inc){
				set16(PRINT_OUT_STRING_MMW);
				set8(m1);
				set32(inc);
			}
			void print_out_string_m(uint48 m1){
				set16(PRINT_OUT_STRING_M);
				set48(m1);
			}
			void set_flag_enter_optimization(){
				if(jit_pos==1)return;
				set16(JIT_FLAG_ENTER_CODE);
				set32(jit_pos);
			}
			void dd_w_c(uint8 m1,uint8 m2){
				if(atual<=P_INT128){
					set16(atual+DD_W_C);
				}else{
					set16(P_UINT64+DD_W_C);
				}
				set8(m1);
				set8(m2);
			}
			void dd_w_w(uint8 m1,uint8 m2){
				if(atual<=P_INT128){
					set16(atual+DD_W_W);
				}else{
					set16(P_UINT64+DD_W_W);
				}
				set8(m1);
				set8(m2);
			}
			void de_w_c(uint8 m1,uint8 m2){
				if(atual<=P_INT128){
					set16(atual+DE_W_C);
				}else{
					set16(P_UINT64+DE_W_C);
				}
				set8(m1);
				set8(m2);
			}
			void de_w_w(uint8 m1,uint8 m2){
				if(atual<=P_INT128){
					set16(atual+DE_W_W);
				}else{
					set16(P_UINT64+DE_W_W);
				}
				set8(m1);
				set8(m2);
			}

			void lea_w__w_w_c(uint8 m1,uint8 m2,uint8 m3,uint64 m4){
				set16(LEA_W__W_W_C);
				set8(m1);
				set8(m2);
				set8(m3);
				set64(m4);
			}
			void lea_w__w_w_w(uint8 m1,uint8 m2,uint8 m3,uint8 m4){
				set16(LEA_W__W_W_W);
				set8(m1);
				set8(m2);
				set8(m3);
				set8(m4);
			}
			void lea_w__w_w_1(uint8 m1,uint8 m2,uint8 m3){
				set16(LEA_W__W_W_1);
				set8(m1);
				set8(m2);
				set8(m3);
			}
			void lea_w__w_w_2(uint8 m1,uint8 m2,uint8 m3){
				set16(LEA_W__W_W_2);
				set8(m1);
				set8(m2);
				set8(m3);
			}
			void lea_w__w_w_4(uint8 m1,uint8 m2,uint8 m3){
				set16(LEA_W__W_W_4);
				set8(m1);
				set8(m2);
				set8(m3);
			}
			void lea_w__w_w_8(uint8 m1,uint8 m2,uint8 m3){
				set16(LEA_W__W_W_8);
				set8(m1);
				set8(m2);
				set8(m3);
			}
			void lea_w__w_w_16(uint8 m1,uint8 m2,uint8 m3){
				set16(LEA_W__W_W_16);
				set8(m1);
				set8(m2);
				set8(m3);
			}
			void lea_w__w_w_32(uint8 m1,uint8 m2,uint8 m3){
				set16(LEA_W__W_W_32);
				set8(m1);
				set8(m2);
				set8(m3);
			}
			void lea_w__w_w_64(uint8 m1,uint8 m2,uint8 m3){
				set16(LEA_W__W_W_64);
				set8(m1);
				set8(m2);
				set8(m3);
			}


			void loop_c_w(uint32 m1, uint8 m2){
				set16(LOOP_C_W);
				set32(m1);
				set8(m2);
			}
			void loop_w_w(uint8 m1, uint8 m2){
				set16(LOOP_C_W);
				set8(m1);
				set8(m2);
			}

			void jmp_c(uint32 m1){
				set16(JMP_C);
				set32(m1);
			}
			void jmp_m(uint48 m1){
				set16(JMP_M);
				set48(m1);
			}
			void jmp_w(uint8 m1){
				set16(JMP_W);
				set8(m1);
			}
			uint32 getPos(){
				return tam-localLastCab;
			}

			void jmp_c_ma(uint32 m1){
				set16(JMP_C_MA);
				set32(m1);
			}
			void jmp_c_me(uint32 m1){
				set16(JMP_C_ME);
				set32(m1);
			}
			void jmp_c_ma_ig(uint32 m1){
				set16(JMP_C_MA_IG);
				set32(m1);
			}
			void jmp_c_me_ig(uint32 m1){
				set16(JMP_C_ME_IG);
				set32(m1);
			}
			void jmp_c_ig(uint32 m1){
				set16(JMP_C_IG);
				set32(m1);
			}
			void jmp_c_di(uint32 m1){
				set16(JMP_C_DI);
				set32(m1);
			}
			void jmp_w_ma(uint8 m1){
				set16(JMP_W_MA);
				set8(m1);
			}
			void jmp_w_me(uint8 m1){
				set16(JMP_W_ME);
				set8(m1);
			}
			void jmp_w_ma_ig(uint8 m1){
				set16(JMP_W_MA_IG);
				set8(m1);
			}
			void jmp_w_me_ig(uint8 m1){
				set16(JMP_W_ME_IG);
				set8(m1);
			}
			void jmp_w_ig(uint8 m1){
				set16(JMP_W_IG);
				set8(m1);
			}
			void jmp_w_di(uint8 m1){
				set16(JMP_W_DI);
				set8(m1);
			}
			void jmp_m_ma(uint48 m1){
				set16(JMP_M_MA);
				set48(m1);
			}
			void jmp_m_me(uint48 m1){
				set16(JMP_M_ME);
				set48(m1);
			}
			void jmp_m_ma_ig(uint48 m1){
				set16(JMP_M_MA_IG);
				set48(m1);
			}
			void jmp_m_me_ig(uint48 m1){
				set16(JMP_M_ME_IG);
				set48(m1);
			}
			void jmp_m_ig(uint48 m1){
				set16(JMP_M_IG);
				set48(m1);
			}
			void jmp_m_di(uint48 m1){
				set16(JMP_M_DI);
				set48(m1);
			}

			void cmp_m_c(uint48 m1,uint64 m2){
				set16(atual+CMP_M_C);
				set48(m1);
				setAtual(m2);
			}

			void cmov_ig_w_c(uint8 m1,uint64 m2){
				set16(atual+CMOV_IG_W_C);
				set8(m1);
				setAtual(m2);
			}
			void cmov_di_w_c(uint8 m1,uint64 m2){
				set16(atual+CMOV_DI_W_C);
				set8(m1);
				setAtual(m2);
			}
			void cmov_ma_w_c(uint8 m1,uint64 m2){
				set16(atual+CMOV_MA_W_C);
				set8(m1);
				setAtual(m2);
			}
			void cmov_me_w_c(uint8 m1,uint64 m2){
				set16(atual+CMOV_ME_W_C);
				set8(m1);
				setAtual(m2);
			}
			void cmov_ma_ig_w_c(uint8 m1,uint64 m2){
				set16(atual+CMOV_MA_IG_W_C);
				set8(m1);
				setAtual(m2);
			}
			void cmov_me_ig_w_c(uint8 m1,uint64 m2){
				set16(atual+CMOV_ME_IG_W_C);
				set8(m1);
				setAtual(m2);
			}
			void cmov_ig_w_w(uint8 m1,uint8 m2){
				set16(atual+CMOV_IG_W_W);
				set8(m1);
				set8(m2);
			}
			void cmov_di_w_w(uint8 m1,uint8 m2){
				set16(atual+CMOV_DI_W_W);
				set8(m1);
				set8(m2);
			}
			void cmov_ma_w_w(uint8 m1,uint8 m2){
				set16(atual+CMOV_MA_W_W);
				set8(m1);
				set8(m2);
			}
			void cmov_me_w_w(uint8 m1,uint8 m2){
				set16(atual+CMOV_ME_W_W);
				set8(m1);
				set8(m2);
			}
			void cmov_ma_ig_w_w(uint8 m1,uint8 m2){
				set16(atual+CMOV_MA_IG_W_W);
				set8(m1);
				set8(m2);
			}
			void cmov_me_ig_w_w(uint8 m1,uint8 m2){
				set16(atual+CMOV_ME_IG_W_W);
				set8(m1);
				set8(m2);
			}

			void cmp_m_m(uint48 m1,uint48 m2){
				set16(atual+CMP_M_M);
				set48(m1);
				set48(m2);
			}
			void cmp_m_w(uint48 m1,uint8 m2){
				set16(atual+CMP_M_W);
				set48(m1);
				set8(m2);
			}
			void cmp_w_c(uint8 m1,uint64 m2){
				set16(atual+CMP_W_C);
				set8(m1);
				setAtual(m2);
			}
			void cmp_w_m(uint8 m1,uint48 m2){
				set16(atual+CMP_W_M);
				set8(m1);
				set48(m2);
			}
			void cmp_w_w(uint8 m1,uint8 m2){
				set16(atual+CMP_W_W);
				set8(m1);
				set8(m2);
			}

			void mul_m_c(uint48 m1,uint64 m2){
				set16(atual+MUL_M_C);
				set48(m1);
				setAtual(m2);
			}
			void mul_w_c(uint8 m1,uint64 m2){
				set16(atual+MUL_W_C);
				set8(m1);
				setAtual(m2);
			}
			void mul_w_m(uint8 m1,uint48 m2){
				set16(atual+MUL_W_M);
				set8(m1);
				set48(m2);
			}
			void mul_w_w(uint8 m1,uint8 m2){
				set16(atual+MUL_W_W);
				set8(m1);
				set8(m2);
			}

			void div_m_c(uint48 m1,uint64 m2){
				set16(atual+DIV_M_C);
				set48(m1);
				setAtual(m2);
			}
			void div_w_c(uint8 m1,uint64 m2){
				set16(atual+DIV_W_C);
				set8(m1);
				setAtual(m2);
			}
			void div_w_m(uint8 m1,uint48 m2){
				set16(atual+DIV_W_M);
				set8(m1);
				set48(m2);
			}
			void div_w_w(uint8 m1,uint8 m2){
				set16(atual+DIV_W_W);
				set8(m1);
				set8(m2);
			}

			void mod_m_c(uint48 m1,uint64 m2){
				set16(atual+MOD_M_C);
				set48(m1);
				setAtual(m2);
			}
			void mod_w_c(uint8 m1,uint64 m2){
				set16(atual+MOD_W_C);
				set8(m1);
				setAtual(m2);
			}
			void mod_w_m(uint8 m1,uint48 m2){
				set16(atual+MOD_W_M);
				set8(m1);
				set48(m2);
			}
			void mod_w_w(uint8 m1,uint8 m2){
				set16(atual+MOD_W_W);
				set8(m1);
				set8(m2);
			}
			void set_flag_optimization(){
				set16(JIT_FLAG_START);
				jit_pos=getPos();
			}
			void set_end_flag_optimization(){
				if(jit_pos==1)return;
				jit_pos=1;
				set16(JIT_FLAG_END);
			}
	};



#endif /* OPCODES_BYTECODER_H_ */
