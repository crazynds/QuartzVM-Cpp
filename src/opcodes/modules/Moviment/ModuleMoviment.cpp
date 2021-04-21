/*
 * ModuleMoviment.cpp
 *
 *  Created on: 19 de jun de 2020
 *      Author: lhlag
 */

#include "ModuleMoviment.h"

#include "../Jit/Jit.h"

#include "mov.h"

/*
 *  w = 1 byte
 *  m = 6 bytes
 *  mmw = 6 bytes + 1 byte + 1 btye
 *  r = 1 byte
 *  rrw = 1 byte + 1 byte + 1 byte + 8 bytes
possibilities{
 w <- c
 w <- w

 m <- c
 m <- w
 m <- m
 w <- m

 mmw <- c
 mmw <- w
 mmw <- m
 mmw <- mmw
 m <- mmw
 w <- mmw
 r <- c
 r <- w
 r <- r
 w <- r
 rrw <- c
 rrw <- w
 rrw <- rrw
 w <- rrw
-------------------
 m <- r
 m <- rrw
 mmw <- rrw
 mmw <- r
 r <- rrw
 r <- m
 r <- mmw
 rrw <- m
 rrw <- mmw
}
*/



ModuleMoviment::ModuleMoviment() {
	uint16 *arr=getListOpcodes();
	uint16 x=0;
	while(arr[x]!=0)x++;
	sizeArray=x;
}

ModuleMoviment::~ModuleMoviment() {
}

uint16* ModuleMoviment::getListOpcodes(){
	static uint16 arr[]={
		P_INT8+MOV_W_W,
		P_UINT8+MOV_W_W,
		P_INT16+MOV_W_W,
		P_UINT16+MOV_W_W,
		P_INT32+MOV_W_W,
		P_UINT32+MOV_W_W,
		P_INT48+MOV_W_W,
		P_UINT48+MOV_W_W,
		P_INT64+MOV_W_W,
		P_UINT64+MOV_W_W,
		P_INT8+MOV_W_C,
		P_INT16+MOV_W_C,
		P_INT32+MOV_W_C,
		P_INT48+MOV_W_C,
		P_INT64+MOV_W_C,
		P_UINT8+MOV_W_C,
		P_UINT16+MOV_W_C,
		P_UINT32+MOV_W_C,
		P_UINT48+MOV_W_C,
		P_UINT64+MOV_W_C,

		P_INT8+MOV_M_C,
		P_INT16+MOV_M_C,
		P_INT32+MOV_M_C,
		P_INT48+MOV_M_C,
		P_INT64+MOV_M_C,
		P_UINT8+MOV_M_C,
		P_UINT16+MOV_M_C,
		P_UINT32+MOV_M_C,
		P_UINT48+MOV_M_C,
		P_UINT64+MOV_M_C,
		P_INT8+MOV_M_W,
		P_INT16+MOV_M_W,
		P_INT32+MOV_M_W,
		P_INT48+MOV_M_W,
		P_INT64+MOV_M_W,
		P_UINT8+MOV_M_W,
		P_UINT16+MOV_M_W,
		P_UINT32+MOV_M_W,
		P_UINT48+MOV_M_W,
		P_UINT64+MOV_M_W,
		P_INT8+MOV_M_M,
		P_INT16+MOV_M_M,
		P_INT32+MOV_M_M,
		P_INT48+MOV_M_M,
		P_INT64+MOV_M_M,
		P_UINT8+MOV_M_M,
		P_UINT16+MOV_M_M,
		P_UINT32+MOV_M_M,
		P_UINT48+MOV_M_M,
		P_UINT64+MOV_M_M,
		P_INT8+MOV_W_M,
		P_INT16+MOV_W_M,
		P_INT32+MOV_W_M,
		P_INT48+MOV_W_M,
		P_INT64+MOV_W_M,
		P_UINT8+MOV_W_M,
		P_UINT16+MOV_W_M,
		P_UINT32+MOV_W_M,
		P_UINT48+MOV_W_M,
		P_UINT64+MOV_W_M,
		0};
	return arr;
}

bool ModuleMoviment::check_jit(Thread &t,Assembler &a,std::map<uint32,Label> &vector,uint16 opcode){
	switch(opcode){
		case P_INT8+MOV_W_C:
		case P_UINT8+MOV_W_C:
		case P_INT8+MOV_W_W:
		case P_UINT8+MOV_W_W:
		case P_INT16+MOV_W_W:
		case P_UINT16+MOV_W_W:
		case P_INT32+MOV_W_W:
		case P_UINT32+MOV_W_W:
		case P_INT48+MOV_W_W:
		case P_UINT48+MOV_W_W:
		case P_INT64+MOV_W_W:
		case P_UINT64+MOV_W_W:
			{t.checkUseCode(2);t.setPontCode(t.getPontCode()+2);}break;
		case P_INT16+MOV_W_C:
		case P_UINT16+MOV_W_C:
			{t.checkUseCode(3);t.setPontCode(t.getPontCode()+3);}break;
		case P_INT32+MOV_W_C:
		case P_UINT32+MOV_W_C:
			{t.checkUseCode(5);t.setPontCode(t.getPontCode()+5);}break;
		case P_INT48+MOV_W_C:
		case P_UINT48+MOV_W_C:
		case P_UINT8+MOV_M_C:
		case P_INT8+MOV_M_C:
		case P_INT8+MOV_M_W:
		case P_UINT8+MOV_M_W:
		case P_INT16+MOV_M_W:
		case P_UINT16+MOV_M_W:
		case P_INT32+MOV_M_W:
		case P_UINT32+MOV_M_W:
		case P_INT48+MOV_M_W:
		case P_UINT48+MOV_M_W:
		case P_INT64+MOV_M_W:
		case P_UINT64+MOV_M_W:
			{t.checkUseCode(7);t.setPontCode(t.getPontCode()+7);}break;
		case P_UINT16+MOV_M_C:
		case P_INT16+MOV_M_C:
			{t.checkUseCode(8);t.setPontCode(t.getPontCode()+8);}break;
		case P_INT64+MOV_W_C:
		case P_UINT64+MOV_W_C:
			{t.checkUseCode(9);t.setPontCode(t.getPontCode()+9);}break;
		case P_UINT32+MOV_M_C:
		case P_INT32+MOV_M_C:
			{t.checkUseCode(10);t.setPontCode(t.getPontCode()+10);}break;
		case P_UINT48+MOV_M_C:
		case P_INT48+MOV_M_C:
			{t.checkUseCode(12);t.setPontCode(t.getPontCode()+12);}break;
		case P_UINT64+MOV_M_C:
		case P_INT64+MOV_M_C:
			{t.checkUseCode(14);t.setPontCode(t.getPontCode()+14);}break;
		default:
			return false;
	}
	return true;
}
bool ModuleMoviment::set_opcode_jit(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::map<uint32,Label> &v){
	switch(jcontent.opcode){
	case P_INT8+MOV_M_M:
	case P_UINT8+MOV_M_M:{
		uint64 mem1=t.getNext48().toInt();
		uint64 mem2=t.getNext48().toInt();
		uint8 size=8;

		Gp reg = a.getRegister(size);

		a.mov(reg,ptr(memory,mem2));
		a.mov(ptr(memory,mem1),reg);
	}break;
	case P_INT16+MOV_M_M:
	case P_UINT16+MOV_M_M:{
		uint64 mem1=t.getNext48().toInt();
		uint64 mem2=t.getNext48().toInt();
		uint8 size=16;

		Gp reg = a.getRegister(size);

		a.mov(reg,ptr(memory,mem2));
		a.mov(ptr(memory,mem1),reg);
	}break;
	case P_INT32+MOV_M_M:
	case P_UINT32+MOV_M_M:{
		uint64 mem1=t.getNext48().toInt();
		uint64 mem2=t.getNext48().toInt();
		uint8 size=32;

		Gp reg = a.getRegister(size);

		a.mov(reg,ptr(memory,mem2));
		a.mov(ptr(memory,mem1),reg);
	}break;
	case P_INT48+MOV_M_M:
	case P_UINT48+MOV_M_M:{
		uint64 mem1=t.getNext48().toInt();
		uint64 mem2=t.getNext48().toInt();

		Gp reg1 = a.getRegister(32);
		Gp reg2 = a.getRegister(16);

		a.mov(reg1,ptr(memory,mem2));
		a.mov(reg2,ptr(memory,mem2+4));
		a.mov(ptr(memory,mem1),reg1);
		a.mov(ptr(memory,mem1+4),reg2);
	}break;
	case P_INT64+MOV_M_M:
	case P_UINT64+MOV_M_M:{
		uint64 mem1=t.getNext48().toInt();
		uint64 mem2=t.getNext48().toInt();
		uint8 size=64;

		Gp reg = a.getRegister(size);

		a.mov(reg,ptr(memory,mem2));
		a.mov(ptr(memory,mem1),reg);
	}break;
	case P_INT8+MOV_M_W:
	case P_UINT8+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		uint8 size=8;

		bool has = a.hasWorkspace(val);
		Gp wk2 = a.getRegisterWorkspace(size,val);
		a.mov(ptr(memory,mem),wk2);
		if(!has)a.ignoreWorkspace(val);
	}break;
	case P_INT16+MOV_M_W:
	case P_UINT16+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		uint8 size=16;

		bool has = a.hasWorkspace(val);
		Gp wk2 = a.getRegisterWorkspace(size,val);
		a.mov(ptr(memory,mem),wk2);
		if(!has)a.ignoreWorkspace(val);
	}break;
	case P_INT32+MOV_M_W:
	case P_UINT32+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		uint8 size=32;

		bool has = a.hasWorkspace(val);
		Gp wk2 = a.getRegisterWorkspace(size,val);
		a.mov(ptr(memory,mem),wk2);
		if(!has)a.ignoreWorkspace(val);
	}break;
	case P_INT48+MOV_M_W:
	case P_UINT48+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		uint8 size=64;

		bool has = a.hasWorkspace(val);
		Gp wk2 = a.getRegisterWorkspace(64,val);
		Gp wkAux = a.getRegisterWorkspace(32,val);
		Gp wkBux = a.getRegisterWorkspace(16,val);
		if(has)a.push(wk2);
		a.mov(ptr(memory,mem),wkAux);
		a.shr(wk2,32);
		a.mov(ptr(memory,mem+4),wkBux);
		if(has)a.pop(wk2);
		else a.ignoreWorkspace(val);
	}break;
	case P_INT64+MOV_M_W:
	case P_UINT64+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		uint8 size=64;

		bool has = a.hasWorkspace(val);
		Gp wk2 = a.getRegisterWorkspace(size,val);
		a.mov(ptr(memory,mem),wk2);
		if(!has)a.ignoreWorkspace(val);
	}break;
	case P_UINT8+MOV_M_C:
	case P_INT8+MOV_M_C:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();

		a.mov(byte_ptr(memory,mem),val);

	}break;
	case P_UINT16+MOV_M_C:
	case P_INT16+MOV_M_C:{
		uint64 mem=t.getNext48().toInt();
		uint16 val=t.getNext16();

		a.mov(word_ptr(memory,mem),val);

	}break;
	case P_UINT32+MOV_M_C:
	case P_INT32+MOV_M_C:{
		uint64 mem=t.getNext48().toInt();
		uint32 val=t.getNext32();

		a.mov(dword_ptr(memory,mem),val);

	}break;
	case P_UINT48+MOV_M_C:
	case P_INT48+MOV_M_C:{
		uint64 mem=t.getNext48().toInt();
		uint32 val1=t.getNext32();
		uint16 val2=t.getNext16();

		a.mov(dword_ptr(memory,mem),val1);
		a.mov(word_ptr(memory,mem+4),val2);

	}break;
	case P_UINT64+MOV_M_C:
	case P_INT64+MOV_M_C:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext64();

		Gp aux = a.getRegisterImediateValue64(val);

		a.mov(qword_ptr(memory,mem),aux);

	}break;
	case P_UINT8+MOV_W_W:
	case P_INT8+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		uint8 size=8;

		if(val==mem){
			a.getRegisterWorkspace(size,mem);	//Se for mover um registrador para ele mesmo carrega ele já em um registrador como 'cache'
		}else if(a.hasWorkspace(mem)){
			Gp wk1 = a.getRegisterWorkspace(size,mem);
			if(a.hasWorkspace(val)){
				Gp wk2 = a.getRegisterWorkspace(size,val);
				a.mov(wk1,wk2);
			}else{
				a.mov(wk1,ptr(workspace,8*val));
			}
		}else{
			if(a.hasWorkspace(val)){
				Gp wk2 = a.getRegisterWorkspace(size,val);
				a.mov(ptr(workspace,8*mem),wk2);
			}else{
				Gp wk1 = a.getRegisterWorkspace(size,mem);
				a.mov(wk1,ptr(workspace,8*val));
			}
		}

	}break;
	case P_UINT16+MOV_W_W:
	case P_INT16+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		uint8 size=16;

		if(val==mem){
			a.getRegisterWorkspace(size,mem);	//Se for mover um registrador para ele mesmo carrega ele já em um registrador como 'cache'
		}else if(a.hasWorkspace(mem)){
			Gp wk1 = a.getRegisterWorkspace(size,mem);
			if(a.hasWorkspace(val)){
				Gp wk2 = a.getRegisterWorkspace(size,val);
				a.mov(wk1,wk2);
			}else{
				a.mov(wk1,ptr(workspace,8*val));
			}
		}else{
			if(a.hasWorkspace(val)){
				Gp wk2 = a.getRegisterWorkspace(size,val);
				a.mov(ptr(workspace,8*mem),wk2);
			}else{
				Gp wk1 = a.getRegisterWorkspace(size,mem);
				a.mov(wk1,ptr(workspace,8*val));
			}
		}
	}break;
	case P_UINT32+MOV_W_W:
	case P_INT32+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		uint8 size=32;

		if(val==mem){
			a.getRegisterWorkspace(size,mem);	//Se for mover um registrador para ele mesmo carrega ele já em um registrador como 'cache'
		}else if(a.hasWorkspace(mem)){
			Gp wk1 = a.getRegisterWorkspace(size,mem);
			if(a.hasWorkspace(val)){
				Gp wk2 = a.getRegisterWorkspace(size,val);
				a.mov(wk1,wk2);
			}else{
				a.mov(wk1,ptr(workspace,8*val));
			}
		}else{
			if(a.hasWorkspace(val)){
				Gp wk2 = a.getRegisterWorkspace(size,val);
				a.mov(ptr(workspace,8*mem),wk2);
			}else{
				Gp wk1 = a.getRegisterWorkspace(size,mem);
				a.mov(wk1,ptr(workspace,8*val));
			}
		}
	}break;
	case P_UINT48+MOV_W_W:
	case P_INT48+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();

		if(val==mem){
			a.getRegisterWorkspace(64,mem);	//Se for mover um registrador para ele mesmo carrega ele já em um registrador como 'cache'
			break;
		}

		Mem xo = a.getMemory48bitsInvertedSuport();
		Mem ox = a.getMemory48bitsSuport();

		Gp reg= a.getRegisterWorkspace64(mem);
		if(a.hasWorkspace(val)){
			Gp value= a.getRegisterWorkspace64(val);
			a.and_(reg,xo);
			a.push(value);
			a.and_(value,ox);
			a.or_(reg,value);
			a.pop(value);
		}else{
			Gp value= a.getRegisterWorkspace64(val);
			a.and_(reg,xo);
			a.and_(value,ox);
			a.or_(reg,value);
			a.ignoreWorkspace(val);
		}
	}break;
	case P_UINT64+MOV_W_W:
	case P_INT64+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		uint8 size=64;

		if(val==mem){
			a.getRegisterWorkspace(size,mem);	//Se for mover um registrador para ele mesmo carrega ele já em um registrador como 'cache'
		}else if(a.hasWorkspace(mem)){
			Gp wk1 = a.getRegisterWorkspace(size,mem);
			if(a.hasWorkspace(val)){
				Gp wk2 = a.getRegisterWorkspace(size,val);
				a.mov(wk1,wk2);
			}else{
				a.mov(wk1,ptr(workspace,8*val));
			}
		}else{
			Gp wk2 = a.getRegisterWorkspace(size,val);
			a.mov(ptr(workspace,8*mem),wk2);
		}
	}break;
	case P_UINT8+MOV_W_C:
	case P_INT8+MOV_W_C:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		uint8 size=8;
		if(a.hasWorkspace(mem)){
			Gp wk1 = a.getRegisterWorkspace(size,mem);
			a.mov(wk1,val);
		}else{
			a.mov(byte_ptr(workspace,8*mem),val);
		}
	}break;
	case P_UINT16+MOV_W_C:
	case P_INT16+MOV_W_C:{
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();
		uint8 size=16;
		if(a.hasWorkspace(mem)){
			Gp wk1 = a.getRegisterWorkspace(size,mem);
			a.mov(wk1,val);
		}else{
			a.mov(word_ptr(workspace,8*mem),val);
		}
	}break;
	case P_UINT32+MOV_W_C:
	case P_INT32+MOV_W_C:{
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();
		uint8 size=32;
		if(a.hasWorkspace(mem)){
			Gp wk1 = a.getRegisterWorkspace(size,mem);
			a.mov(wk1,val);
		}else{
			a.mov(dword_ptr(workspace,8*mem),val);
		}
	}break;
	case P_UINT48+MOV_W_C:
	case P_INT48+MOV_W_C:{
		uint8 mem=t.getNext8();

		if(a.hasWorkspace(mem)){
			uint64 value=t.getNext48().toInt();
			Gp aux = a.getRegister64();
			Mem xo = a.getMemory48bitsInvertedSuport();
			Gp reg= a.getRegisterWorkspace64(mem);
			a.and_(reg,xo);
			a.mov(aux,value);
			a.or_(reg,aux);
		}else{
			uint32 val1=t.getNext32();
			uint16 val2=t.getNext16();
			a.mov(dword_ptr(workspace,mem*8),val1);
			a.mov(word_ptr(workspace,(mem*8)+4),val2);
		}
	}break;
	case P_UINT64+MOV_W_C:
	case P_INT64+MOV_W_C:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();
		uint8 size=64;
		if(a.hasWorkspace(mem)){
			Gp wk1 = a.getRegisterWorkspace(size,mem);
			a.mov(wk1,val);
		}else{
			a.mov(qword_ptr(workspace,8*mem),val);
		}
	}break;
	default:
		return false;
	}
	return true;
}



void ModuleMoviment::setInterpretedOpcodes(ManagerOpcodes& man){
	{
		CodeHolder ch;
		Error e =ch.init(man.getJitRuntime().environment());
		if(e)throw VMException(_CREATE_FUNCTION_JIT_STR);
		c_mov_w_w8(&ch);
		man.createOpcodeJit(P_INT8+MOV_W_W,ch);
		man.createOpcodeJit(P_UINT8+MOV_W_W,ch);
	}
	{
		CodeHolder ch;
		Error e =ch.init(man.getJitRuntime().environment());
		if(e)throw VMException(_CREATE_FUNCTION_JIT_STR);
		c_mov_w_w8(&ch);
		man.createOpcodeJit(P_INT16+MOV_W_W,ch);
		man.createOpcodeJit(P_UINT16+MOV_W_W,ch);
	}
	{
		CodeHolder ch;
		Error e =ch.init(man.getJitRuntime().environment());
		if(e)throw VMException(_CREATE_FUNCTION_JIT_STR);
		c_mov_w_w8(&ch);
		man.createOpcodeJit(P_INT32+MOV_W_W,ch);
		man.createOpcodeJit(P_UINT32+MOV_W_W,ch);
	}
	{
		CodeHolder ch;
		Error e =ch.init(man.getJitRuntime().environment());
		if(e)throw VMException(_CREATE_FUNCTION_JIT_STR);
		c_mov_w_w8(&ch);
		man.createOpcodeJit(P_INT48+MOV_W_W,ch);
		man.createOpcodeJit(P_UINT48+MOV_W_W,ch);
	}
	{
		CodeHolder ch;
		Error e =ch.init(man.getJitRuntime().environment());
		if(e)throw VMException(_CREATE_FUNCTION_JIT_STR);
		c_mov_w_w8(&ch);
		man.createOpcodeJit(P_INT64+MOV_W_W,ch);
		man.createOpcodeJit(P_UINT64+MOV_W_W,ch);
	}
	man.createOpcode(P_INT8+MOV_W_C,(void*)mov_w_c8);
	man.createOpcode(P_INT16+MOV_W_C,(void*)mov_w_c16);
	man.createOpcode(P_INT32+MOV_W_C,(void*)mov_w_c32);
	man.createOpcode(P_INT48+MOV_W_C,(void*)mov_w_c48);
	man.createOpcode(P_INT64+MOV_W_C,(void*)mov_w_c64);
	man.createOpcode(P_UINT8+MOV_W_C,(void*)mov_w_c8);
	man.createOpcode(P_UINT16+MOV_W_C,(void*)mov_w_c16);
	man.createOpcode(P_UINT32+MOV_W_C,(void*)mov_w_c32);
	man.createOpcode(P_UINT48+MOV_W_C,(void*)mov_w_c48);
	man.createOpcode(P_UINT64+MOV_W_C,(void*)mov_w_c64);

	//p2

	man.createOpcode(P_INT8+MOV_M_C,(void*)mov_m_c8);
	man.createOpcode(P_INT16+MOV_M_C,(void*)mov_m_c16);
	man.createOpcode(P_INT32+MOV_M_C,(void*)mov_m_c32);
	man.createOpcode(P_INT48+MOV_M_C,(void*)mov_m_c48);
	man.createOpcode(P_INT64+MOV_M_C,(void*)mov_m_c64);
	man.createOpcode(P_UINT8+MOV_M_C,(void*)mov_m_c8);
	man.createOpcode(P_UINT16+MOV_M_C,(void*)mov_m_c16);
	man.createOpcode(P_UINT32+MOV_M_C,(void*)mov_m_c32);
	man.createOpcode(P_UINT48+MOV_M_C,(void*)mov_m_c48);
	man.createOpcode(P_UINT64+MOV_M_C,(void*)mov_m_c64);

	man.createOpcode(P_INT8+MOV_M_M,(void*)mov_m_m8);
	man.createOpcode(P_INT16+MOV_M_M,(void*)mov_m_m16);
	man.createOpcode(P_INT32+MOV_M_M,(void*)mov_m_m32);
	man.createOpcode(P_INT48+MOV_M_M,(void*)mov_m_m48);
	man.createOpcode(P_INT64+MOV_M_M,(void*)mov_m_m64);
	man.createOpcode(P_UINT8+MOV_M_M,(void*)mov_m_m8);
	man.createOpcode(P_UINT16+MOV_M_M,(void*)mov_m_m16);
	man.createOpcode(P_UINT32+MOV_M_M,(void*)mov_m_m32);
	man.createOpcode(P_UINT48+MOV_M_M,(void*)mov_m_m48);
	man.createOpcode(P_UINT64+MOV_M_M,(void*)mov_m_m64);

	man.createOpcode(P_INT8+MOV_M_W,(void*)mov_m_w8);
	man.createOpcode(P_INT16+MOV_M_W,(void*)mov_m_w16);
	man.createOpcode(P_INT32+MOV_M_W,(void*)mov_m_w32);
	man.createOpcode(P_INT48+MOV_M_W,(void*)mov_m_w48);
	man.createOpcode(P_INT64+MOV_M_W,(void*)mov_m_w64);
	man.createOpcode(P_UINT8+MOV_M_W,(void*)mov_m_w8);
	man.createOpcode(P_UINT16+MOV_M_W,(void*)mov_m_w16);
	man.createOpcode(P_UINT32+MOV_M_W,(void*)mov_m_w32);
	man.createOpcode(P_UINT48+MOV_M_W,(void*)mov_m_w48);
	man.createOpcode(P_UINT64+MOV_M_W,(void*)mov_m_w64);

	man.createOpcode(P_INT8+MOV_W_M,(void*)mov_w_m8);
	man.createOpcode(P_INT16+MOV_W_M,(void*)mov_w_m16);
	man.createOpcode(P_INT32+MOV_W_M,(void*)mov_w_m32);
	man.createOpcode(P_INT48+MOV_W_M,(void*)mov_w_m48);
	man.createOpcode(P_INT64+MOV_W_M,(void*)mov_w_m64);
	man.createOpcode(P_UINT8+MOV_W_M,(void*)mov_w_m8);
	man.createOpcode(P_UINT16+MOV_W_M,(void*)mov_w_m16);
	man.createOpcode(P_UINT32+MOV_W_M,(void*)mov_w_m32);
	man.createOpcode(P_UINT48+MOV_W_M,(void*)mov_w_m48);
	man.createOpcode(P_UINT64+MOV_W_M,(void*)mov_w_m64);


	void **VET=man.getVetorOpcode();

	VET[P_UINT8+MOV_R_C]=(void*)mov_r_c8;
	VET[P_UINT16+MOV_R_C]=(void*)mov_r_c16;
	VET[P_UINT32+MOV_R_C]=(void*)mov_r_c32;
	VET[P_UINT48+MOV_R_C]=(void*)mov_r_c48;
	VET[P_UINT64+MOV_R_C]=(void*)mov_r_c64;
	VET[P_INT8+MOV_R_C]=(void*)mov_r_c8;
	VET[P_INT16+MOV_R_C]=(void*)mov_r_c16;
	VET[P_INT32+MOV_R_C]=(void*)mov_r_c32;
	VET[P_INT48+MOV_R_C]=(void*)mov_r_c48;
	VET[P_INT64+MOV_R_C]=(void*)mov_r_c64;

	VET[P_UINT8+MOV_R_W]=(void*)mov_r_w8;
	VET[P_UINT16+MOV_R_W]=(void*)mov_r_w16;
	VET[P_UINT32+MOV_R_W]=(void*)mov_r_w32;
	VET[P_UINT48+MOV_R_W]=(void*)mov_r_w48;
	VET[P_UINT64+MOV_R_W]=(void*)mov_r_w64;
	VET[P_INT8+MOV_R_W]=(void*)mov_r_w8;
	VET[P_INT16+MOV_R_W]=(void*)mov_r_w16;
	VET[P_INT32+MOV_R_W]=(void*)mov_r_w32;
	VET[P_INT48+MOV_R_W]=(void*)mov_r_w48;
	VET[P_INT64+MOV_R_W]=(void*)mov_r_w64;

	VET[P_UINT8+MOV_R_R]=(void*)mov_r_r8;
	VET[P_UINT16+MOV_R_R]=(void*)mov_r_r16;
	VET[P_UINT32+MOV_R_R]=(void*)mov_r_r32;
	VET[P_UINT48+MOV_R_R]=(void*)mov_r_r48;
	VET[P_UINT64+MOV_R_R]=(void*)mov_r_r64;
	VET[P_INT8+MOV_R_R]=(void*)mov_r_r8;
	VET[P_INT16+MOV_R_R]=(void*)mov_r_r16;
	VET[P_INT32+MOV_R_R]=(void*)mov_r_r32;
	VET[P_INT48+MOV_R_R]=(void*)mov_r_r48;
	VET[P_INT64+MOV_R_R]=(void*)mov_r_r64;

	VET[P_UINT8+MOV_W_R]=(void*)mov_w_r8;
	VET[P_UINT16+MOV_W_R]=(void*)mov_w_r16;
	VET[P_UINT32+MOV_W_R]=(void*)mov_w_r32;
	VET[P_UINT48+MOV_W_R]=(void*)mov_w_r48;
	VET[P_UINT64+MOV_W_R]=(void*)mov_w_r64;
	VET[P_INT8+MOV_W_R]=(void*)mov_w_r8;
	VET[P_INT16+MOV_W_R]=(void*)mov_w_r16;
	VET[P_INT32+MOV_W_R]=(void*)mov_w_r32;
	VET[P_INT48+MOV_W_R]=(void*)mov_w_r48;
	VET[P_INT64+MOV_W_R]=(void*)mov_w_r64;


	VET[P_UINT8+MOV_RRW_C]=(void*)mov_rrw_c8;
	VET[P_UINT16+MOV_RRW_C]=(void*)mov_rrw_c16;
	VET[P_UINT32+MOV_RRW_C]=(void*)mov_rrw_c32;
	VET[P_UINT48+MOV_RRW_C]=(void*)mov_rrw_c48;
	VET[P_UINT64+MOV_RRW_C]=(void*)mov_rrw_c64;
	VET[P_INT8+MOV_RRW_C]=(void*)mov_rrw_c8;
	VET[P_INT16+MOV_RRW_C]=(void*)mov_rrw_c16;
	VET[P_INT32+MOV_RRW_C]=(void*)mov_rrw_c32;
	VET[P_INT48+MOV_RRW_C]=(void*)mov_rrw_c48;
	VET[P_INT64+MOV_RRW_C]=(void*)mov_rrw_c64;

	VET[P_UINT8+MOV_RRW_W]=(void*)mov_rrw_w8;
	VET[P_UINT16+MOV_RRW_W]=(void*)mov_rrw_w16;
	VET[P_UINT32+MOV_RRW_W]=(void*)mov_rrw_w32;
	VET[P_UINT48+MOV_RRW_W]=(void*)mov_rrw_w48;
	VET[P_UINT64+MOV_RRW_W]=(void*)mov_rrw_w64;
	VET[P_INT8+MOV_RRW_W]=(void*)mov_rrw_w8;
	VET[P_INT16+MOV_RRW_W]=(void*)mov_rrw_w16;
	VET[P_INT32+MOV_RRW_W]=(void*)mov_rrw_w32;
	VET[P_INT48+MOV_RRW_W]=(void*)mov_rrw_w48;
	VET[P_INT64+MOV_RRW_W]=(void*)mov_rrw_w64;

	VET[P_UINT8+MOV_W_RRW]=(void*)mov_w_rrw8;
	VET[P_UINT16+MOV_W_RRW]=(void*)mov_w_rrw16;
	VET[P_UINT32+MOV_W_RRW]=(void*)mov_w_rrw32;
	VET[P_UINT48+MOV_W_RRW]=(void*)mov_w_rrw48;
	VET[P_UINT64+MOV_W_RRW]=(void*)mov_w_rrw64;
	VET[P_INT8+MOV_W_RRW]=(void*)mov_w_rrw8;
	VET[P_INT16+MOV_W_RRW]=(void*)mov_w_rrw16;
	VET[P_INT32+MOV_W_RRW]=(void*)mov_w_rrw32;
	VET[P_INT48+MOV_W_RRW]=(void*)mov_w_rrw48;
	VET[P_INT64+MOV_W_RRW]=(void*)mov_w_rrw64;

	VET[P_UINT8+MOV_RRW_RRW]=(void*)mov_rrw_rrw8;
	VET[P_UINT16+MOV_RRW_RRW]=(void*)mov_rrw_rrw16;
	VET[P_UINT32+MOV_RRW_RRW]=(void*)mov_rrw_rrw32;
	VET[P_UINT48+MOV_RRW_RRW]=(void*)mov_rrw_rrw48;
	VET[P_UINT64+MOV_RRW_RRW]=(void*)mov_rrw_rrw64;
	VET[P_INT8+MOV_RRW_RRW]=(void*)mov_rrw_rrw8;
	VET[P_INT16+MOV_RRW_RRW]=(void*)mov_rrw_rrw16;
	VET[P_INT32+MOV_RRW_RRW]=(void*)mov_rrw_rrw32;
	VET[P_INT48+MOV_RRW_RRW]=(void*)mov_rrw_rrw48;
	VET[P_INT64+MOV_RRW_RRW]=(void*)mov_rrw_rrw64;

	VET[P_INT8+MOV_MMW_MMW]=(void*)mov_mmw_mmw8;
	VET[P_INT16+MOV_MMW_MMW]=(void*)mov_mmw_mmw16;
	VET[P_INT32+MOV_MMW_MMW]=(void*)mov_mmw_mmw32;
	VET[P_INT48+MOV_MMW_MMW]=(void*)mov_mmw_mmw48;
	VET[P_INT64+MOV_MMW_MMW]=(void*)mov_mmw_mmw64;
	VET[P_INT8+MOV_W_MMW]=(void*)mov_w_mmw8;
	VET[P_INT16+MOV_W_MMW]=(void*)mov_w_mmw16;
	VET[P_INT32+MOV_W_MMW]=(void*)mov_w_mmw32;
	VET[P_INT48+MOV_W_MMW]=(void*)mov_w_mmw48;
	VET[P_INT64+MOV_W_MMW]=(void*)mov_w_mmw64;
	VET[P_INT8+MOV_MMW_W]=(void*)mov_mmw_w8;
	VET[P_INT16+MOV_MMW_W]=(void*)mov_mmw_w16;
	VET[P_INT32+MOV_MMW_W]=(void*)mov_mmw_w32;
	VET[P_INT48+MOV_MMW_W]=(void*)mov_mmw_w48;
	VET[P_INT64+MOV_MMW_W]=(void*)mov_mmw_w64;

	VET[P_UINT8+MOV_MMW_MMW]=(void*)mov_mmw_mmw8;
	VET[P_UINT16+MOV_MMW_MMW]=(void*)mov_mmw_mmw16;
	VET[P_UINT32+MOV_MMW_MMW]=(void*)mov_mmw_mmw32;
	VET[P_UINT48+MOV_MMW_MMW]=(void*)mov_mmw_mmw48;
	VET[P_UINT64+MOV_MMW_MMW]=(void*)mov_mmw_mmw64;
	VET[P_UINT8+MOV_W_MMW]=(void*)mov_w_mmw8;
	VET[P_UINT16+MOV_W_MMW]=(void*)mov_w_mmw16;
	VET[P_UINT32+MOV_W_MMW]=(void*)mov_w_mmw32;
	VET[P_UINT48+MOV_W_MMW]=(void*)mov_w_mmw48;
	VET[P_UINT64+MOV_W_MMW]=(void*)mov_w_mmw64;
	VET[P_UINT8+MOV_MMW_W]=(void*)mov_mmw_w8;
	VET[P_UINT16+MOV_MMW_W]=(void*)mov_mmw_w16;
	VET[P_UINT32+MOV_MMW_W]=(void*)mov_mmw_w32;
	VET[P_UINT48+MOV_MMW_W]=(void*)mov_mmw_w48;
	VET[P_UINT64+MOV_MMW_W]=(void*)mov_mmw_w64;


	VET[P_UINT8+MOV_MMW_C]=(void*)mov_mmw_c8;
	VET[P_UINT16+MOV_MMW_C]=(void*)mov_mmw_c16;
	VET[P_UINT32+MOV_MMW_C]=(void*)mov_mmw_c32;
	VET[P_UINT48+MOV_MMW_C]=(void*)mov_mmw_c48;
	VET[P_UINT64+MOV_MMW_C]=(void*)mov_mmw_c64;
	VET[P_UINT8+MOV_MMW_M]=(void*)mov_mmw_m8;
	VET[P_UINT16+MOV_MMW_M]=(void*)mov_mmw_m16;
	VET[P_UINT32+MOV_MMW_M]=(void*)mov_mmw_m32;
	VET[P_UINT48+MOV_MMW_M]=(void*)mov_mmw_m48;
	VET[P_UINT64+MOV_MMW_M]=(void*)mov_mmw_m64;
	VET[P_UINT8+MOV_M_MMW]=(void*)mov_m_mmw8;
	VET[P_UINT16+MOV_M_MMW]=(void*)mov_m_mmw16;
	VET[P_UINT32+MOV_M_MMW]=(void*)mov_m_mmw32;
	VET[P_UINT48+MOV_M_MMW]=(void*)mov_m_mmw48;
	VET[P_UINT64+MOV_M_MMW]=(void*)mov_m_mmw64;

	VET[P_INT8+MOV_MMW_C]=(void*)mov_mmw_c8;
	VET[P_INT16+MOV_MMW_C]=(void*)mov_mmw_c16;
	VET[P_INT32+MOV_MMW_C]=(void*)mov_mmw_c32;
	VET[P_INT48+MOV_MMW_C]=(void*)mov_mmw_c48;
	VET[P_INT64+MOV_MMW_C]=(void*)mov_mmw_c64;
	VET[P_INT8+MOV_MMW_M]=(void*)mov_mmw_m8;	//mov m[w[?]],m[?] (8 bits)
	VET[P_INT16+MOV_MMW_M]=(void*)mov_mmw_m16;
	VET[P_INT32+MOV_MMW_M]=(void*)mov_mmw_m32;
	VET[P_INT48+MOV_MMW_M]=(void*)mov_mmw_m48;
	VET[P_INT64+MOV_MMW_M]=(void*)mov_mmw_m64;
	VET[P_INT8+MOV_M_MMW]=(void*)mov_m_mmw8;
	VET[P_INT16+MOV_M_MMW]=(void*)mov_m_mmw16;
	VET[P_INT32+MOV_M_MMW]=(void*)mov_m_mmw32;
	VET[P_INT48+MOV_M_MMW]=(void*)mov_m_mmw48;
	VET[P_INT64+MOV_M_MMW]=(void*)mov_m_mmw64;
}

