/*
 * ManagerOpcodes.cpp
 *
 *  Created on: 20 de jun de 2020
 *      Author: lhlag
 */

#include "ManagerOpcodes.h"
#include <iostream>
#include "../../opcodes/GeralComand.h"
#include "../../opcodes/modules/GeneralModules.h"
#include "../../opcodes/modules/LibraryModuleOpcode.h"

class Thread;

void setStack(void **);
void setGerais(void **);
void setMov(void **);
void setArit(void **);
void setCmp(void **);


void end_running(Thread &t){
	//Define a flag running como off;
	t.error_flags|=RUNNING_;
}


void no_opcode(Thread &t){
	throw CodeException(t.getPontCode()-2,"No Opcode Found","Nenhum opcode equivalente encontrado");

#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif
}

ManagerOpcodes::ManagerOpcodes(void **VET,uint8 debugLevel) {
	this->debugLevel=debugLevel;
	this->VET=VET;
	funcs=0;
	func_pos=(uint16*)mcalloc(1,sizeof(uint16));

	modulesArray = (LibraryModuleOpcode**)mmalloc(sizeof(LibraryModuleOpcode*));
	lenModules=0;

	for(int x=0;x<OPCODETAM;x++){
		VET[x]=(void*)no_opcode;
	}

	definesPositionsThread();


	loadLibraryModuleOpcode(new ModuleJit());
	loadLibraryModuleOpcode(new ModuleSdtio());
	loadLibraryModuleOpcode(new ModuleMoviment());

	loadOpcodesModules();

	setStack(VET);
	setGerais(VET);
	setMov(VET);
	setArit(VET);
	setCmp(VET);
}

ManagerOpcodes::~ManagerOpcodes() {
	if(func_pos!=0){
		free(func_pos);
	}

	for(uint16 x=0;x<lenModules;x++){
		delete modulesArray[x];
	}
	free(modulesArray);
}

void ** ManagerOpcodes::getVetorOpcode(){
	return VET;
}

void ManagerOpcodes::releaseOpcodesJit(){
	for(uint16 x=0;x<funcs;x++){
		if(func_pos[x]==0)return;
		rt.release(VET[func_pos[x]]);
	}
	free(func_pos);
	func_pos=0;
}

uint16 ManagerOpcodes::sizeFuncsJit(){
	return funcs;
}

uint16 ManagerOpcodes::sizeModules(){
	return lenModules;
}

void ManagerOpcodes::createOpcodeJit(uint16 pos, CodeHolder &code){
	void *aux= VET[pos];

	Error err = rt.add(&VET[pos], &code);
	if (err){
		VET[pos]=aux;
		if(debugLevel>=1)std::cout << "[ERROR] - Error ao compilar comando da Virtual Machine! Comando:  "+pos << err <<  std::endl;
		return;
	}else if(debugLevel>=3) std::cout << "[SUCESS] - Criado comando jit optimizado N: " << pos << std::endl;
	funcs++;
	func_pos=(uint16*)mrealloc(func_pos,funcs*sizeof(uint16));
	func_pos[funcs-1]=pos;
}
void ManagerOpcodes::createOpcode(uint16 pos,void * func){
	VET[pos]=func;
}

LibraryModuleOpcode** ManagerOpcodes::getModules(){
	return modulesArray;
}

void ManagerOpcodes::loadLibraryModuleOpcode(LibraryModuleOpcode *pont){
	lenModules++;
	modulesArray = (LibraryModuleOpcode**)mrealloc(modulesArray,sizeof(LibraryModuleOpcode*)*lenModules);
	modulesArray[lenModules-1]=pont;
}
void ManagerOpcodes::loadOpcodesModules(){
	for(uint16 x=0;x<lenModules;x++){
		modulesArray[x]->setInterpretedOpcodes(*this);
	}
}
JitRuntime& ManagerOpcodes::getJitRuntime(){
	return rt;
}

void ManagerOpcodes::setDebugLevel(uint8 debugLevel){
	this->debugLevel=debugLevel;
}


void setStack(void **VET){
	VET[CALL_C]=(void*)call_c;
	VET[CALL_M]=(void*)call_m;
	VET[CALL_W]=(void*)call_w;
	VET[RETURN]=(void*)ret;

	VET[PUSH_C]=(void*)push_c;
	VET[PUSH_W]=(void*)push_w;
	VET[POP_W]=(void*)pop_w;

	VET[CALL_CTX_C]=(void*)call_ctx_c;
	VET[CALL_CTX_W]=(void*)call_ctx_w;
	VET[JMP_C]=(void*)jmp_c;
	VET[JMP_M]=(void*)jmp_m;
	VET[JMP_W]=(void*)jmp_w;
	VET[JMP_C_MA]=(void*)jmp_c_ma;
	VET[JMP_C_ME]=(void*)jmp_c_me;
	VET[JMP_C_DI]=(void*)jmp_c_di;
	VET[JMP_C_IG]=(void*)jmp_c_ig;
	VET[JMP_C_MA_IG]=(void*)jmp_c_ma_ig;
	VET[JMP_C_ME_IG]=(void*)jmp_c_me_ig;
	VET[JMP_M_MA]=(void*)jmp_m_ma;
	VET[JMP_M_ME]=(void*)jmp_m_me;
	VET[JMP_M_DI]=(void*)jmp_m_di;
	VET[JMP_M_IG]=(void*)jmp_m_ig;
	VET[JMP_M_MA_IG]=(void*)jmp_m_ma_ig;
	VET[JMP_M_ME_IG]=(void*)jmp_m_me_ig;
	VET[JMP_W_MA]=(void*)jmp_w_ma;
	VET[JMP_W_ME]=(void*)jmp_w_me;
	VET[JMP_W_DI]=(void*)jmp_w_di;
	VET[JMP_W_IG]=(void*)jmp_w_ig;
	VET[JMP_W_MA_IG]=(void*)jmp_w_ma_ig;
	VET[JMP_W_ME_IG]=(void*)jmp_w_me_ig;
	VET[LOOP_C_W]=(void*)loop_c_w;
	VET[LOOP_W_W]=(void*)loop_w_w;
}

void setGerais(void **VET){

	VET[0]=(void*)end_running;

	VET[ALLOC_DIN_RES]=(void*)alloc_dinamic_res;
	VET[REALLOC_DIN_RES]=(void*)ralloc_dinamic_res;
	VET[ALLOC_RES]=(void*)alloc_res;
	VET[FREE_RES]=(void*)free_res;
	VET[REALLOC_RES]=(void*)realloc_res;
}
void setMov(void **VET){

	VET[P_INT8+COPY_M_M_C]=(void*)copy_m_m_c8;
	VET[P_INT8+COPY_M_M_W]=(void*)copy_m_m_w8;
	VET[P_UINT8+COPY_M_M_C]=(void*)copy_m_m_c8;
	VET[P_UINT8+COPY_M_M_W]=(void*)copy_m_m_w8;
	VET[P_INT16+COPY_M_M_C]=(void*)copy_m_m_c16;
	VET[P_INT16+COPY_M_M_W]=(void*)copy_m_m_w16;
	VET[P_UINT16+COPY_M_M_C]=(void*)copy_m_m_c16;
	VET[P_UINT16+COPY_M_M_W]=(void*)copy_m_m_w16;
	VET[P_INT32+COPY_M_M_C]=(void*)copy_m_m_c32;
	VET[P_INT32+COPY_M_M_W]=(void*)copy_m_m_w32;
	VET[P_UINT32+COPY_M_M_C]=(void*)copy_m_m_c32;
	VET[P_UINT32+COPY_M_M_W]=(void*)copy_m_m_w32;
	VET[P_INT48+COPY_M_M_C]=(void*)copy_m_m_c48;
	VET[P_INT48+COPY_M_M_W]=(void*)copy_m_m_w48;
	VET[P_UINT48+COPY_M_M_C]=(void*)copy_m_m_c48;
	VET[P_UINT48+COPY_M_M_W]=(void*)copy_m_m_w48;
	VET[P_INT64+COPY_M_M_C]=(void*)copy_m_m_c64;
	VET[P_INT64+COPY_M_M_W]=(void*)copy_m_m_w64;
	VET[P_UINT64+COPY_M_M_C]=(void*)copy_m_m_c64;
	VET[P_UINT64+COPY_M_M_W]=(void*)copy_m_m_w64;

	VET[P_INT8+COPY_MW_MW_C]=(void*)copy_mw_mw_c8;
	VET[P_INT8+COPY_MW_MW_W]=(void*)copy_mw_mw_w8;
	VET[P_UINT8+COPY_MW_MW_C]=(void*)copy_mw_mw_c8;
	VET[P_UINT8+COPY_MW_MW_W]=(void*)copy_mw_mw_w8;
	VET[P_INT16+COPY_MW_MW_C]=(void*)copy_mw_mw_c16;
	VET[P_INT16+COPY_MW_MW_W]=(void*)copy_mw_mw_w16;
	VET[P_UINT16+COPY_MW_MW_C]=(void*)copy_mw_mw_c16;
	VET[P_UINT16+COPY_MW_MW_W]=(void*)copy_mw_mw_w16;
	VET[P_INT32+COPY_MW_MW_C]=(void*)copy_mw_mw_c32;
	VET[P_INT32+COPY_MW_MW_W]=(void*)copy_mw_mw_w32;
	VET[P_UINT32+COPY_MW_MW_C]=(void*)copy_mw_mw_c32;
	VET[P_UINT32+COPY_MW_MW_W]=(void*)copy_mw_mw_w32;
	VET[P_INT48+COPY_MW_MW_C]=(void*)copy_mw_mw_c48;
	VET[P_INT48+COPY_MW_MW_W]=(void*)copy_mw_mw_w48;
	VET[P_UINT48+COPY_MW_MW_C]=(void*)copy_mw_mw_c48;
	VET[P_UINT48+COPY_MW_MW_W]=(void*)copy_mw_mw_w48;
	VET[P_INT64+COPY_MW_MW_C]=(void*)copy_mw_mw_c64;
	VET[P_INT64+COPY_MW_MW_W]=(void*)copy_mw_mw_w64;
	VET[P_UINT64+COPY_MW_MW_C]=(void*)copy_mw_mw_c64;
	VET[P_UINT64+COPY_MW_MW_W]=(void*)copy_mw_mw_w64;

}
void setArit(void **VET){

	VET[INC_W]=(void*)inc_w;
	VET[DEC_W]=(void*)dec_w;

	VET[LEA_W__W_W_C]=(void*)lea_w__w_w_c;
	VET[LEA_W__W_W_W]=(void*)lea_w__w_w_w;
	VET[LEA_W__W_W_1]=(void*)lea_w__w_w_1;
	VET[LEA_W__W_W_2]=(void*)lea_w__w_w_2;
	VET[LEA_W__W_W_4]=(void*)lea_w__w_w_4;
	VET[LEA_W__W_W_8]=(void*)lea_w__w_w_8;
	VET[LEA_W__W_W_16]=(void*)lea_w__w_w_16;
	VET[LEA_W__W_W_32]=(void*)lea_w__w_w_32;
	VET[LEA_W__W_W_64]=(void*)lea_w__w_w_64;

	VET[P_UINT8+DD_W_C]=(void*)dd_w_c_8;
	VET[P_UINT16+DD_W_C]=(void*)dd_w_c_16;
	VET[P_UINT32+DD_W_C]=(void*)dd_w_c_32;
	VET[P_UINT48+DD_W_C]=(void*)dd_w_c_48;
	VET[P_UINT64+DD_W_C]=(void*)dd_w_c_64;

	VET[P_INT8+DD_W_C]=(void*)dd_w_c_8;
	VET[P_INT16+DD_W_C]=(void*)dd_w_c_16;
	VET[P_INT32+DD_W_C]=(void*)dd_w_c_32;
	VET[P_INT48+DD_W_C]=(void*)dd_w_c_48;
	VET[P_INT64+DD_W_C]=(void*)dd_w_c_64;

	VET[P_UINT8+DD_W_W]=(void*)dd_w_w_8;
	VET[P_UINT16+DD_W_W]=(void*)dd_w_w_16;
	VET[P_UINT32+DD_W_W]=(void*)dd_w_w_32;
	VET[P_UINT48+DD_W_W]=(void*)dd_w_w_48;
	VET[P_UINT64+DD_W_W]=(void*)dd_w_w_64;

	VET[P_INT8+DD_W_W]=(void*)dd_w_w_8;
	VET[P_INT16+DD_W_W]=(void*)dd_w_w_16;
	VET[P_INT32+DD_W_W]=(void*)dd_w_w_32;
	VET[P_INT48+DD_W_W]=(void*)dd_w_w_48;
	VET[P_INT64+DD_W_W]=(void*)dd_w_w_64;

	VET[P_UINT8+DE_W_C]=(void*)de_w_c_8;
	VET[P_UINT16+DE_W_C]=(void*)de_w_c_16;
	VET[P_UINT32+DE_W_C]=(void*)de_w_c_32;
	VET[P_UINT48+DE_W_C]=(void*)de_w_c_48;
	VET[P_UINT64+DE_W_C]=(void*)de_w_c_64;

	VET[P_INT8+DE_W_C]=(void*)de_w_c_8;
	VET[P_INT16+DE_W_C]=(void*)de_w_c_16;
	VET[P_INT32+DE_W_C]=(void*)de_w_c_32;
	VET[P_INT48+DE_W_C]=(void*)de_w_c_48;
	VET[P_INT64+DE_W_C]=(void*)de_w_c_64;

	VET[P_UINT8+DE_W_W]=(void*)de_w_w_8;
	VET[P_UINT16+DE_W_W]=(void*)de_w_w_16;
	VET[P_UINT32+DE_W_W]=(void*)de_w_w_32;
	VET[P_UINT48+DE_W_W]=(void*)de_w_w_48;
	VET[P_UINT64+DE_W_W]=(void*)de_w_w_64;

	VET[P_INT8+DE_W_W]=(void*)de_w_w_8;
	VET[P_INT16+DE_W_W]=(void*)de_w_w_16;
	VET[P_INT32+DE_W_W]=(void*)de_w_w_32;
	VET[P_INT48+DE_W_W]=(void*)de_w_w_48;
	VET[P_INT64+DE_W_W]=(void*)de_w_w_64;

	//Aritimetic
	VET[P_INT8+SOMA_M_C]=(void*)soma_m_c_i8;
	VET[P_INT16+SOMA_M_C]=(void*)soma_m_c_i16;
	VET[P_INT32+SOMA_M_C]=(void*)soma_m_c_i32;
	VET[P_INT48+SOMA_M_C]=(void*)soma_m_c_i48;
	VET[P_INT64+SOMA_M_C]=(void*)soma_m_c_i64;
	VET[P_INT8+SOMA_W_C]=(void*)soma_w_c_i8;
	VET[P_INT16+SOMA_W_C]=(void*)soma_w_c_i16;
	VET[P_INT32+SOMA_W_C]=(void*)soma_w_c_i32;
	VET[P_INT48+SOMA_W_C]=(void*)soma_w_c_i48;
	VET[P_INT64+SOMA_W_C]=(void*)soma_w_c_i64;
	VET[P_INT8+SOMA_W_M]=(void*)soma_w_m_i8;
	VET[P_INT16+SOMA_W_M]=(void*)soma_w_m_i16;
	VET[P_INT32+SOMA_W_M]=(void*)soma_w_m_i32;
	VET[P_INT48+SOMA_W_M]=(void*)soma_w_m_i48;
	VET[P_INT64+SOMA_W_M]=(void*)soma_w_m_i64;
	VET[P_INT8+SOMA_W_W]=(void*)soma_w_w_i8;
	VET[P_INT16+SOMA_W_W]=(void*)soma_w_w_i16;
	VET[P_INT32+SOMA_W_W]=(void*)soma_w_w_i32;
	VET[P_INT48+SOMA_W_W]=(void*)soma_w_w_i48;
	VET[P_INT64+SOMA_W_W]=(void*)soma_w_w_i64;

	VET[P_UINT8+SOMA_M_C]=(void*)soma_m_c_ui8;
	VET[P_UINT16+SOMA_M_C]=(void*)soma_m_c_ui16;
	VET[P_UINT32+SOMA_M_C]=(void*)soma_m_c_ui32;
	VET[P_UINT48+SOMA_M_C]=(void*)soma_m_c_ui48;
	VET[P_UINT64+SOMA_M_C]=(void*)soma_m_c_ui64;
	VET[P_UINT8+SOMA_W_C]=(void*)soma_w_c_ui8;
	VET[P_UINT16+SOMA_W_C]=(void*)soma_w_c_ui16;
	VET[P_UINT32+SOMA_W_C]=(void*)soma_w_c_ui32;
	VET[P_UINT48+SOMA_W_C]=(void*)soma_w_c_ui48;
	VET[P_UINT64+SOMA_W_C]=(void*)soma_w_c_ui64;
	VET[P_UINT8+SOMA_W_M]=(void*)soma_w_m_ui8;
	VET[P_UINT16+SOMA_W_M]=(void*)soma_w_m_ui16;
	VET[P_UINT32+SOMA_W_M]=(void*)soma_w_m_ui32;
	VET[P_UINT48+SOMA_W_M]=(void*)soma_w_m_ui48;
	VET[P_UINT64+SOMA_W_M]=(void*)soma_w_m_ui64;
	VET[P_UINT8+SOMA_W_W]=(void*)soma_w_w_ui8;
	VET[P_UINT16+SOMA_W_W]=(void*)soma_w_w_ui16;
	VET[P_UINT32+SOMA_W_W]=(void*)soma_w_w_ui32;
	VET[P_UINT48+SOMA_W_W]=(void*)soma_w_w_ui48;
	VET[P_UINT64+SOMA_W_W]=(void*)soma_w_w_ui64;


	//Aritimetic
	VET[P_INT8+SUB_M_C]=(void*)sub_m_c_i8;
	VET[P_INT16+SUB_M_C]=(void*)sub_m_c_i16;
	VET[P_INT32+SUB_M_C]=(void*)sub_m_c_i32;
	VET[P_INT48+SUB_M_C]=(void*)sub_m_c_i48;
	VET[P_INT64+SUB_M_C]=(void*)sub_m_c_i64;
	VET[P_INT8+SUB_W_C]=(void*)sub_w_c_i8;
	VET[P_INT16+SUB_W_C]=(void*)sub_w_c_i16;
	VET[P_INT32+SUB_W_C]=(void*)sub_w_c_i32;
	VET[P_INT48+SUB_W_C]=(void*)sub_w_c_i48;
	VET[P_INT64+SUB_W_C]=(void*)sub_w_c_i64;
	VET[P_INT8+SUB_W_M]=(void*)sub_w_m_i8;
	VET[P_INT16+SUB_W_M]=(void*)sub_w_m_i16;
	VET[P_INT32+SUB_W_M]=(void*)sub_w_m_i32;
	VET[P_INT48+SUB_W_M]=(void*)sub_w_m_i48;
	VET[P_INT64+SUB_W_M]=(void*)sub_w_m_i64;
	VET[P_INT8+SUB_W_W]=(void*)sub_w_w_i8;
	VET[P_INT16+SUB_W_W]=(void*)sub_w_w_i16;
	VET[P_INT32+SUB_W_W]=(void*)sub_w_w_i32;
	VET[P_INT48+SUB_W_W]=(void*)sub_w_w_i48;
	VET[P_INT64+SUB_W_W]=(void*)sub_w_w_i64;

	VET[P_UINT8+SUB_M_C]=(void*)sub_m_c_ui8;
	VET[P_UINT16+SUB_M_C]=(void*)sub_m_c_ui16;
	VET[P_UINT32+SUB_M_C]=(void*)sub_m_c_ui32;
	VET[P_UINT48+SUB_M_C]=(void*)sub_m_c_ui48;
	VET[P_UINT64+SUB_M_C]=(void*)sub_m_c_ui64;
	VET[P_UINT8+SUB_W_C]=(void*)sub_w_c_ui8;
	VET[P_UINT16+SUB_W_C]=(void*)sub_w_c_ui16;
	VET[P_UINT32+SUB_W_C]=(void*)sub_w_c_ui32;
	VET[P_UINT48+SUB_W_C]=(void*)sub_w_c_ui48;
	VET[P_UINT64+SUB_W_C]=(void*)sub_w_c_ui64;
	VET[P_UINT8+SUB_W_M]=(void*)sub_w_m_ui8;
	VET[P_UINT16+SUB_W_M]=(void*)sub_w_m_ui16;
	VET[P_UINT32+SUB_W_M]=(void*)sub_w_m_ui32;
	VET[P_UINT48+SUB_W_M]=(void*)sub_w_m_ui48;
	VET[P_UINT64+SUB_W_M]=(void*)sub_w_m_ui64;
	VET[P_UINT8+SUB_W_W]=(void*)sub_w_w_ui8;
	VET[P_UINT16+SUB_W_W]=(void*)sub_w_w_ui16;
	VET[P_UINT32+SUB_W_W]=(void*)sub_w_w_ui32;
	VET[P_UINT48+SUB_W_W]=(void*)sub_w_w_ui48;
	VET[P_UINT64+SUB_W_W]=(void*)sub_w_w_ui64;


	//Aritimetic
	VET[P_INT8+MUL_M_C]=(void*)mul_m_c_i8;
	VET[P_INT16+MUL_M_C]=(void*)mul_m_c_i16;
	VET[P_INT32+MUL_M_C]=(void*)mul_m_c_i32;
	VET[P_INT48+MUL_M_C]=(void*)mul_m_c_i48;
	VET[P_INT64+MUL_M_C]=(void*)mul_m_c_i64;
	VET[P_INT8+MUL_W_C]=(void*)mul_w_c_i8;
	VET[P_INT16+MUL_W_C]=(void*)mul_w_c_i16;
	VET[P_INT32+MUL_W_C]=(void*)mul_w_c_i32;
	VET[P_INT48+MUL_W_C]=(void*)mul_w_c_i48;
	VET[P_INT64+MUL_W_C]=(void*)mul_w_c_i64;
	VET[P_INT8+MUL_W_M]=(void*)mul_w_m_i8;
	VET[P_INT16+MUL_W_M]=(void*)mul_w_m_i16;
	VET[P_INT32+MUL_W_M]=(void*)mul_w_m_i32;
	VET[P_INT48+MUL_W_M]=(void*)mul_w_m_i48;
	VET[P_INT64+MUL_W_M]=(void*)mul_w_m_i64;
	VET[P_INT8+MUL_W_W]=(void*)mul_w_w_i8;
	VET[P_INT16+MUL_W_W]=(void*)mul_w_w_i16;
	VET[P_INT32+MUL_W_W]=(void*)mul_w_w_i32;
	VET[P_INT48+MUL_W_W]=(void*)mul_w_w_i48;
	VET[P_INT64+MUL_W_W]=(void*)mul_w_w_i64;

	VET[P_UINT8+MUL_M_C]=(void*)mul_m_c_ui8;
	VET[P_UINT16+MUL_M_C]=(void*)mul_m_c_ui16;
	VET[P_UINT32+MUL_M_C]=(void*)mul_m_c_ui32;
	VET[P_UINT48+MUL_M_C]=(void*)mul_m_c_ui48;
	VET[P_UINT64+MUL_M_C]=(void*)mul_m_c_ui64;
	VET[P_UINT8+MUL_W_C]=(void*)mul_w_c_ui8;
	VET[P_UINT16+MUL_W_C]=(void*)mul_w_c_ui16;
	VET[P_UINT32+MUL_W_C]=(void*)mul_w_c_ui32;
	VET[P_UINT48+MUL_W_C]=(void*)mul_w_c_ui48;
	VET[P_UINT64+MUL_W_C]=(void*)mul_w_c_ui64;
	VET[P_UINT8+MUL_W_M]=(void*)mul_w_m_ui8;
	VET[P_UINT16+MUL_W_M]=(void*)mul_w_m_ui16;
	VET[P_UINT32+MUL_W_M]=(void*)mul_w_m_ui32;
	VET[P_UINT48+MUL_W_M]=(void*)mul_w_m_ui48;
	VET[P_UINT64+MUL_W_M]=(void*)mul_w_m_ui64;
	VET[P_UINT8+MUL_W_W]=(void*)mul_w_w_ui8;
	VET[P_UINT16+MUL_W_W]=(void*)mul_w_w_ui16;
	VET[P_UINT32+MUL_W_W]=(void*)mul_w_w_ui32;
	VET[P_UINT48+MUL_W_W]=(void*)mul_w_w_ui48;
	VET[P_UINT64+MUL_W_W]=(void*)mul_w_w_ui64;


	//Aritimetic
	VET[P_INT8+DIV_M_C]=(void*)div_m_c_i8;
	VET[P_INT16+DIV_M_C]=(void*)div_m_c_i16;
	VET[P_INT32+DIV_M_C]=(void*)div_m_c_i32;
	VET[P_INT48+DIV_M_C]=(void*)div_m_c_i48;
	VET[P_INT64+DIV_M_C]=(void*)div_m_c_i64;
	VET[P_INT8+DIV_W_C]=(void*)div_w_c_i8;
	VET[P_INT16+DIV_W_C]=(void*)div_w_c_i16;
	VET[P_INT32+DIV_W_C]=(void*)div_w_c_i32;
	VET[P_INT48+DIV_W_C]=(void*)div_w_c_i48;
	VET[P_INT64+DIV_W_C]=(void*)div_w_c_i64;
	VET[P_INT8+DIV_W_M]=(void*)div_w_m_i8;
	VET[P_INT16+DIV_W_M]=(void*)div_w_m_i16;
	VET[P_INT32+DIV_W_M]=(void*)div_w_m_i32;
	VET[P_INT48+DIV_W_M]=(void*)div_w_m_i48;
	VET[P_INT64+DIV_W_M]=(void*)div_w_m_i64;
	VET[P_INT8+DIV_W_W]=(void*)div_w_w_i8;
	VET[P_INT16+DIV_W_W]=(void*)div_w_w_i16;
	VET[P_INT32+DIV_W_W]=(void*)div_w_w_i32;
	VET[P_INT48+DIV_W_W]=(void*)div_w_w_i48;
	VET[P_INT64+DIV_W_W]=(void*)div_w_w_i64;

	VET[P_UINT8+DIV_M_C]=(void*)div_m_c_ui8;
	VET[P_UINT16+DIV_M_C]=(void*)div_m_c_ui16;
	VET[P_UINT32+DIV_M_C]=(void*)div_m_c_ui32;
	VET[P_UINT48+DIV_M_C]=(void*)div_m_c_ui48;
	VET[P_UINT64+DIV_M_C]=(void*)div_m_c_ui64;
	VET[P_UINT8+DIV_W_C]=(void*)div_w_c_ui8;
	VET[P_UINT16+DIV_W_C]=(void*)div_w_c_ui16;
	VET[P_UINT32+DIV_W_C]=(void*)div_w_c_ui32;
	VET[P_UINT48+DIV_W_C]=(void*)div_w_c_ui48;
	VET[P_UINT64+DIV_W_C]=(void*)div_w_c_ui64;
	VET[P_UINT8+DIV_W_M]=(void*)div_w_m_ui8;
	VET[P_UINT16+DIV_W_M]=(void*)div_w_m_ui16;
	VET[P_UINT32+DIV_W_M]=(void*)div_w_m_ui32;
	VET[P_UINT48+DIV_W_M]=(void*)div_w_m_ui48;
	VET[P_UINT64+DIV_W_M]=(void*)div_w_m_ui64;
	VET[P_UINT8+DIV_W_W]=(void*)div_w_w_ui8;
	VET[P_UINT16+DIV_W_W]=(void*)div_w_w_ui16;
	VET[P_UINT32+DIV_W_W]=(void*)div_w_w_ui32;
	VET[P_UINT48+DIV_W_W]=(void*)div_w_w_ui48;
	VET[P_UINT64+DIV_W_W]=(void*)div_w_w_ui64;


	//Aritimetic
	VET[P_INT8+MOD_M_C]=(void*)mod_m_c_i8;
	VET[P_INT16+MOD_M_C]=(void*)mod_m_c_i16;
	VET[P_INT32+MOD_M_C]=(void*)mod_m_c_i32;
	VET[P_INT48+MOD_M_C]=(void*)mod_m_c_i48;
	VET[P_INT64+MOD_M_C]=(void*)mod_m_c_i64;
	VET[P_INT8+MOD_W_C]=(void*)mod_w_c_i8;
	VET[P_INT16+MOD_W_C]=(void*)mod_w_c_i16;
	VET[P_INT32+MOD_W_C]=(void*)mod_w_c_i32;
	VET[P_INT48+MOD_W_C]=(void*)mod_w_c_i48;
	VET[P_INT64+MOD_W_C]=(void*)mod_w_c_i64;
	VET[P_INT8+MOD_W_M]=(void*)mod_w_m_i8;
	VET[P_INT16+MOD_W_M]=(void*)mod_w_m_i16;
	VET[P_INT32+MOD_W_M]=(void*)mod_w_m_i32;
	VET[P_INT48+MOD_W_M]=(void*)mod_w_m_i48;
	VET[P_INT64+MOD_W_M]=(void*)mod_w_m_i64;
	VET[P_INT8+MOD_W_W]=(void*)mod_w_w_i8;
	VET[P_INT16+MOD_W_W]=(void*)mod_w_w_i16;
	VET[P_INT32+MOD_W_W]=(void*)mod_w_w_i32;
	VET[P_INT48+MOD_W_W]=(void*)mod_w_w_i48;
	VET[P_INT64+MOD_W_W]=(void*)mod_w_w_i64;

	VET[P_UINT8+MOD_M_C]=(void*)mod_m_c_ui8;
	VET[P_UINT16+MOD_M_C]=(void*)mod_m_c_ui16;
	VET[P_UINT32+MOD_M_C]=(void*)mod_m_c_ui32;
	VET[P_UINT48+MOD_M_C]=(void*)mod_m_c_ui48;
	VET[P_UINT64+MOD_M_C]=(void*)mod_m_c_ui64;
	VET[P_UINT8+MOD_W_C]=(void*)mod_w_c_ui8;
	VET[P_UINT16+MOD_W_C]=(void*)mod_w_c_ui16;
	VET[P_UINT32+MOD_W_C]=(void*)mod_w_c_ui32;
	VET[P_UINT48+MOD_W_C]=(void*)mod_w_c_ui48;
	VET[P_UINT64+MOD_W_C]=(void*)mod_w_c_ui64;
	VET[P_UINT8+MOD_W_M]=(void*)mod_w_m_ui8;
	VET[P_UINT16+MOD_W_M]=(void*)mod_w_m_ui16;
	VET[P_UINT32+MOD_W_M]=(void*)mod_w_m_ui32;
	VET[P_UINT48+MOD_W_M]=(void*)mod_w_m_ui48;
	VET[P_UINT64+MOD_W_M]=(void*)mod_w_m_ui64;
	VET[P_UINT8+MOD_W_W]=(void*)mod_w_w_ui8;
	VET[P_UINT16+MOD_W_W]=(void*)mod_w_w_ui16;
	VET[P_UINT32+MOD_W_W]=(void*)mod_w_w_ui32;
	VET[P_UINT48+MOD_W_W]=(void*)mod_w_w_ui48;
	VET[P_UINT64+MOD_W_W]=(void*)mod_w_w_ui64;
}
void setCmp(void **VET){

	VET[P_UINT8+CMP_M_C]=(void*)cmp_m_c_ui8;
	VET[P_UINT16+CMP_M_C]=(void*)cmp_m_c_ui16;
	VET[P_UINT32+CMP_M_C]=(void*)cmp_m_c_ui32;
	VET[P_UINT48+CMP_M_C]=(void*)cmp_m_c_ui48;
	VET[P_UINT64+CMP_M_C]=(void*)cmp_m_c_ui64;
	VET[P_UINT8+CMP_M_M]=(void*)cmp_m_m_ui8;
	VET[P_UINT16+CMP_M_M]=(void*)cmp_m_m_ui16;
	VET[P_UINT32+CMP_M_M]=(void*)cmp_m_m_ui32;
	VET[P_UINT48+CMP_M_M]=(void*)cmp_m_m_ui48;
	VET[P_UINT64+CMP_M_M]=(void*)cmp_m_m_ui64;
	VET[P_UINT8+CMP_M_W]=(void*)cmp_m_w_ui8;
	VET[P_UINT16+CMP_M_W]=(void*)cmp_m_w_ui16;
	VET[P_UINT32+CMP_M_W]=(void*)cmp_m_w_ui32;
	VET[P_UINT48+CMP_M_W]=(void*)cmp_m_w_ui48;
	VET[P_UINT64+CMP_M_W]=(void*)cmp_m_w_ui64;
	VET[P_UINT8+CMP_W_C]=(void*)cmp_w_c_ui8;
	VET[P_UINT16+CMP_W_C]=(void*)cmp_w_c_ui16;
	VET[P_UINT32+CMP_W_C]=(void*)cmp_w_c_ui32;
	VET[P_UINT48+CMP_W_C]=(void*)cmp_w_c_ui48;
	VET[P_UINT64+CMP_W_C]=(void*)cmp_w_c_ui64;
	VET[P_UINT8+CMP_W_M]=(void*)cmp_w_m_ui8;
	VET[P_UINT16+CMP_W_M]=(void*)cmp_w_m_ui16;
	VET[P_UINT32+CMP_W_M]=(void*)cmp_w_m_ui32;
	VET[P_UINT48+CMP_W_M]=(void*)cmp_w_m_ui48;
	VET[P_UINT64+CMP_W_M]=(void*)cmp_w_m_ui64;
	VET[P_UINT8+CMP_W_W]=(void*)cmp_w_w_ui8;
	VET[P_UINT16+CMP_W_W]=(void*)cmp_w_w_ui16;
	VET[P_UINT32+CMP_W_W]=(void*)cmp_w_w_ui32;
	VET[P_UINT48+CMP_W_W]=(void*)cmp_w_w_ui48;
	VET[P_UINT64+CMP_W_W]=(void*)cmp_w_w_ui64;


	VET[P_INT8+CMP_M_C]=(void*)cmp_m_c_i8;
	VET[P_INT16+CMP_M_C]=(void*)cmp_m_c_i16;
	VET[P_INT32+CMP_M_C]=(void*)cmp_m_c_i32;
	VET[P_INT48+CMP_M_C]=(void*)cmp_m_c_i48;
	VET[P_INT64+CMP_M_C]=(void*)cmp_m_c_i64;
	VET[P_INT8+CMP_M_M]=(void*)cmp_m_m_i8;
	VET[P_INT16+CMP_M_M]=(void*)cmp_m_m_i16;
	VET[P_INT32+CMP_M_M]=(void*)cmp_m_m_i32;
	VET[P_INT48+CMP_M_M]=(void*)cmp_m_m_i48;
	VET[P_INT64+CMP_M_M]=(void*)cmp_m_m_i64;
	VET[P_INT8+CMP_M_W]=(void*)cmp_m_w_i8;
	VET[P_INT16+CMP_M_W]=(void*)cmp_m_w_i16;
	VET[P_INT32+CMP_M_W]=(void*)cmp_m_w_i32;
	VET[P_INT48+CMP_M_W]=(void*)cmp_m_w_i48;
	VET[P_INT64+CMP_M_W]=(void*)cmp_m_w_i64;
	VET[P_INT8+CMP_W_C]=(void*)cmp_w_c_i8;
	VET[P_INT16+CMP_W_C]=(void*)cmp_w_c_i16;
	VET[P_INT32+CMP_W_C]=(void*)cmp_w_c_i32;
	VET[P_INT48+CMP_W_C]=(void*)cmp_w_c_i48;
	VET[P_INT64+CMP_W_C]=(void*)cmp_w_c_i64;
	VET[P_INT8+CMP_W_M]=(void*)cmp_w_m_i8;
	VET[P_INT16+CMP_W_M]=(void*)cmp_w_m_i16;
	VET[P_INT32+CMP_W_M]=(void*)cmp_w_m_i32;
	VET[P_INT48+CMP_W_M]=(void*)cmp_w_m_i48;
	VET[P_INT64+CMP_W_M]=(void*)cmp_w_m_i64;
	VET[P_INT8+CMP_W_W]=(void*)cmp_w_w_i8;
	VET[P_INT16+CMP_W_W]=(void*)cmp_w_w_i16;
	VET[P_INT32+CMP_W_W]=(void*)cmp_w_w_i32;
	VET[P_INT48+CMP_W_W]=(void*)cmp_w_w_i48;
	VET[P_INT64+CMP_W_W]=(void*)cmp_w_w_i64;
}
