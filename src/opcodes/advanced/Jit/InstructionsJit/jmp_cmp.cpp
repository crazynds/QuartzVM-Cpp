/*
* jmp_cmp.cpp
*
*  Created on: 11 de mai de 2019
*      Author: lhlag
*/

#include "../Jit.h"

uint8 jmp_cmp(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v,uint32 startCode){
	Gp memory=rdi;
	Gp workspace=rsi;

	Gp qreg[8];qreg[0]=r8;qreg[1]=r9;qreg[2]=r10;qreg[3]=r11;qreg[4]=r12;qreg[5]=r13;qreg[6]=r14;qreg[7]=r15;
	Gp dreg[8];dreg[0]=r8d;dreg[1]=r9d;dreg[2]=r10d;dreg[3]=r11d;dreg[4]=r12d;dreg[5]=r13d;dreg[6]=r14d;dreg[7]=r15d;
	Gp wreg[8];wreg[0]=r8w;wreg[1]=r9w;wreg[2]=r10w;wreg[3]=r11w;wreg[4]=r12w;wreg[5]=r13w;wreg[6]=r14w;wreg[7]=r15w;
	Gp breg[8];breg[0]=r8b;breg[1]=r9b;breg[2]=r10b;breg[3]=r11b;breg[4]=r12b;breg[5]=r13b;breg[6]=r14b;breg[7]=r15b;

	switch(jcontent.opcode){
	case CALL_C:{
		uint32 posAtual=t.getPontCode();
		// empurra a posição atual na pilha
		t.set16InCode(t.getPontCode()-2,JIT_FLAG_ENTER_CODE);
		uint32 aux=t.getNext32();

		a.pop(rcx);
		a.push(rcx);
		pushRegisters(a);
		a.mov(rdx,t.getPontCode());
		a.sub(rsp,0x8);
		a.call(uint64((void*)Thread::saveInStack));
		a.add(rsp,0x8);
		popRegisters(a);
		a.mov(rcx,0x0000FFFFFFFFFFFF);

		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			a.mov(rax,uint64(aux));
			a.jmp(end);
		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				a.jmp(v[x].getFirst());
				break;
			}
		}
		t.set32InCode(t.getPontCode()-4,startCode);
	}break;
	case RETURN:{

		a.pop(rcx);
		a.push(rcx);
		pushRegisters(a);
		a.sub(rsp,0x8);
		a.call(uint64((void*)Thread::recoverInStack));
		a.add(rsp,0x8);
		popRegisters(a);

		//posição atual é retornada em RAX;
		a.mov(rcx,0x0000FFFFFFFFFFFF);


		a.jmp(end);
	}break;
	case JMP_C:{
		uint32 aux=t.getNext32();
		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			a.mov(rax,uint64(aux));
			a.jmp(end);
		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				a.jmp(v[x].getFirst());
				break;
			}
		}
	}break;
	case JMP_C_DI:{
		uint32 aux=t.getNext32();
		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			Label l=a.newLabel();
			a.je(l);
			a.mov(rax,uint64(aux));
			a.jmp(end);
			a.bind(l);

		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				a.jne(v[x].getFirst());
				break;
			}
		}
	}break;
	case JMP_C_IG:{
		uint32 aux=t.getNext32();
		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			Label l=a.newLabel();
			a.jne(l);
			a.mov(rax,uint64(aux));
			a.jmp(end);
			a.bind(l);

		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				a.je(v[x].getFirst());
				break;
			}
		}
	}break;
	case JMP_C_MA:{
		uint32 aux=t.getNext32();
		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jbe(l);
			else a.jle(l);
			a.mov(rax,uint64(aux));
			a.jmp(end);
			a.bind(l);

		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				if(jcontent.type=='u')a.ja(v[x].getFirst());
				else a.jg(v[x].getFirst());
				break;
			}
		}
	}break;
	case JMP_C_MA_IG:{
		uint32 aux=t.getNext32();
		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jb(l);
			else a.jl(l);
			a.mov(rax,uint64(aux));
			a.jmp(end);
			a.bind(l);

		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				if(jcontent.type=='u')a.jae(v[x].getFirst());
				else a.jge(v[x].getFirst());
				break;
			}
		}
	}break;
	case JMP_C_ME:{
		uint32 aux=t.getNext32();
		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jae(l);
			else a.jge(l);
			a.mov(rax,uint64(aux));
			a.jmp(end);
			a.bind(l);

		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				if(jcontent.type=='u')a.jb(v[x].getFirst());
				else a.jl(v[x].getFirst());
				break;
			}
		}
	}break;
	case JMP_C_ME_IG:{
		uint32 aux=t.getNext32();
		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			Label l=a.newLabel();
			if(jcontent.type=='u')a.ja(l);
			else a.jg(l);
			a.mov(rax,uint64(aux));
			a.jmp(end);
			a.bind(l);

		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				if(jcontent.type=='u')a.jbe(v[x].getFirst());
				else a.jle(v[x].getFirst());
				break;
			}
		}
	}break;
	case P_UINT8+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(aux<8){
			a.cmp(breg[aux],ptr(memory,val));
		}else{
			a.mov(al,ptr(workspace,aux*8));
			a.cmp(al,ptr(memory,val));

		}

		jcontent.type='u';
	}break;
	case P_INT8+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(aux<8){
			a.cmp(breg[aux],ptr(memory,val));
		}else{
			a.mov(al,ptr(memory,val));
			a.cmp(ptr(workspace,aux*8),al);

		}

		jcontent.type='i';
	}break;
	case P_UINT16+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(aux<8){
			a.cmp(wreg[aux],ptr(memory,val));
		}else{
			a.mov(ax,ptr(workspace,aux*8));
			a.cmp(ax,ptr(memory,val));

		}
		jcontent.type='u';
	}break;
	case P_INT16+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(aux<8){
			a.cmp(wreg[aux],ptr(memory,val));
		}else{
			a.mov(ax,ptr(workspace,aux*8));
			a.cmp(ax,ptr(memory,val));

		}
		jcontent.type='i';
	}break;
	case P_UINT32+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(aux<8){
			a.cmp(dreg[aux],ptr(memory,val));
		}else{
			a.mov(eax,ptr(workspace,aux*8));
			a.cmp(eax,ptr(memory,val));

		}
		jcontent.type='u';
	}break;
	case P_INT32+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(aux<8){
			a.cmp(dreg[aux],ptr(memory,val));
		}else{
			a.mov(eax,ptr(workspace,aux*8));
			a.cmp(eax,ptr(memory,val));

		}
		jcontent.type='i';
	}break;
	case P_UINT48+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(rbx,ptr(memory,val));
		if(aux<8){
			a.mov(rax,qreg[aux]);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
		}
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.and_(rax,rcx);
		a.and_(rbx,rcx);
		a.cmp(rax,rbx);
		jcontent.type='u';



	}break;
	case P_INT48+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0xFFFF000000000000);
		if(aux<8){
			a.mov(rax,qreg[aux]);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
		}
		a.mov(rbx,ptr(memory,val));
		a.andn(rax,rcx,rax);
		a.andn(rbx,rcx,rax);
		Label l=a.newLabel();
		Label l1=a.newLabel();
		a.bt(rax,47);
		a.jnc(l);
		a.or_(rax,rcx);
		a.bind(l);
		a.bt(rbx,47);
		a.jnc(l1);
		a.or_(rbx,rcx);
		a.bind(l1);

		a.cmp(rax,rbx);
		jcontent.type='i';



	}break;
	case P_UINT64+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(aux<8){
			a.cmp(qreg[aux],ptr(memory,val));
		}else{
			a.mov(rax,ptr(workspace,aux*8));
			a.cmp(rax,ptr(memory,val));

		}
		jcontent.type='u';
	}break;
	case P_INT64+CMP_W_M:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(aux<8){
			a.cmp(qreg[aux],ptr(memory,val));
		}else{
			a.mov(rax,ptr(workspace,aux*8));
			a.cmp(rax,ptr(memory,val));

		}
		jcontent.type='i';
	}break;
	case P_UINT8+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		if(aux<8){
			a.cmp(ptr(memory,val),breg[aux]);
		}else{
			a.mov(al,ptr(workspace,aux*8));
			a.cmp(ptr(memory,val),al);

		}
		jcontent.type='u';
	}break;
	case P_INT8+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		if(aux<8){
			a.cmp(ptr(memory,val),breg[aux]);
		}else{
			a.mov(al,ptr(workspace,aux*8));
			a.cmp(ptr(memory,val),al);

		}
		jcontent.type='i';
	}break;
	case P_UINT16+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		if(aux<8){
			a.cmp(ptr(memory,val),wreg[aux]);
		}else{
			a.mov(ax,ptr(workspace,aux*8));
			a.cmp(ptr(memory,val),ax);

		}
		jcontent.type='u';
	}break;
	case P_INT16+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		if(aux<8){
			a.cmp(ptr(memory,val),wreg[aux]);
		}else{
			a.mov(ax,ptr(workspace,aux*8));
			a.cmp(ptr(memory,val),ax);

		}
		jcontent.type='i';
	}break;
	case P_UINT32+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		if(aux<8){
			a.cmp(ptr(memory,val),dreg[aux]);
		}else{
			a.mov(eax,ptr(workspace,aux*8));
			a.cmp(ptr(memory,val),eax);

		}
		jcontent.type='u';
	}break;
	case P_INT32+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		if(aux<8){
			a.cmp(ptr(memory,val),dreg[aux]);
		}else{
			a.mov(eax,ptr(workspace,aux*8));
			a.cmp(ptr(memory,val),eax);

		}
		jcontent.type='i';
	}break;
	case P_UINT48+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(aux<8){
			a.mov(rax,qreg[aux]);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
		}
		a.mov(rbx,ptr(memory,val));
		a.and_(rax,rcx);
		a.and_(rbx,rcx);
		a.cmp(rbx,rax);
		jcontent.type='u';


	}break;
	case P_INT48+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(aux<8){
			a.mov(rax,qreg[aux]);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
		}
		a.mov(rbx,ptr(memory,val));
		a.and_(rax,rcx);
		a.and_(rbx,rcx);
		a.cmp(rbx,rax);

		jcontent.type='i';


	}break;
	case P_UINT64+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		if(aux<8){
			a.cmp(ptr(memory,val),qreg[aux]);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
			a.cmp(ptr(memory,val),rax);

		}
		jcontent.type='u';
	}break;
	case P_INT64+CMP_M_W:{
		uint64 val=t.getNext48().toInt();
		uint8 aux=t.getNext8();
		if(aux<8){
			a.cmp(ptr(memory,val),qreg[aux]);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
			a.cmp(ptr(memory,val),rax);

		}
		jcontent.type='i';
	}break;
	case P_UINT8+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(al,ptr(memory,aux));
		a.cmp(ptr(memory,val),al);
		jcontent.type='u';

	}break;
	case P_INT8+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(al,ptr(memory,aux));
		a.cmp(ptr(memory,val),al);
		jcontent.type='i';

	}break;
	case P_UINT16+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(ax,ptr(memory,aux));
		a.cmp(ptr(memory,val),ax);
		jcontent.type='u';

	}break;
	case P_INT16+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(ax,ptr(memory,aux));
		a.cmp(ptr(memory,val),ax);
		jcontent.type='i';

	}break;
	case P_UINT32+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(eax,ptr(memory,aux));
		a.cmp(ptr(memory,val),eax);
		jcontent.type='u';

	}break;
	case P_INT32+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(eax,ptr(memory,aux));
		a.cmp(ptr(memory,val),eax);
		jcontent.type='i';

	}break;
	case P_UINT48+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.mov(rax,ptr(memory,aux));
		a.mov(rbx,ptr(memory,val));
		a.and_(rax,rcx);
		a.and_(rbx,rcx);
		a.cmp(rbx,rax);
		jcontent.type='u';


	}break;
	case P_INT48+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.mov(rax,ptr(memory,aux));
		a.mov(rbx,ptr(memory,val));
		a.and_(rax,rcx);
		a.and_(rbx,rcx);
		a.cmp(rbx,rax);
		jcontent.type='i';


	}break;
	case P_UINT64+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(rax,ptr(memory,aux));
		a.cmp(ptr(memory,val),rax);
		jcontent.type='u';

	}break;
	case P_INT64+CMP_M_M:{
		uint64 val=t.getNext48().toInt();
		uint64 aux=t.getNext48().toInt();
		a.mov(rax,ptr(memory,aux));
		a.cmp(ptr(memory,val),rax);
		jcontent.type='i';

	}break;
	case P_UINT8+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			a.cmp(breg[aux],val);
		}else{
			a.cmp(byte_ptr(workspace,aux*8),val);
		}
		jcontent.type='u';
	}break;
	case P_INT8+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			a.cmp(breg[aux],val);
		}else{
			a.cmp(byte_ptr(workspace,aux*8),val);
		}
		jcontent.type='i';
	}break;
	case P_UINT16+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint16 val=t.getNext16();
		if(aux<8){
			a.cmp(wreg[aux],val);
		}else{
			a.cmp(word_ptr(workspace,aux*8),val);
		}
		jcontent.type='u';
	}break;
	case P_INT16+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint16 val=t.getNext16();
		if(aux<8){
			a.cmp(wreg[aux],val);
		}else{
			a.cmp(word_ptr(workspace,aux*8),val);
		}
		jcontent.type='i';
	}break;
	case P_UINT32+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint32 val=t.getNext32();
		if(aux<8){
			a.cmp(dreg[aux],val);
		}else{
			a.cmp(dword_ptr(workspace,aux*8),val);
		}
		jcontent.type='u';
	}break;
	case P_INT32+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint32 val=t.getNext32();
		if(aux<8){
			a.cmp(dreg[aux],val);
		}else{
			a.cmp(dword_ptr(workspace,aux*8),val);
		}
		jcontent.type='i';
	}break;
	case P_UINT48+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(aux<8){
			a.mov(rax,qreg[aux]);
			a.and_(rax,rcx);
			a.cmp(rax,val);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
			a.and_(rax,rcx);
			a.cmp(rax,val);
		}
		jcontent.type='u';


	}break;
	case P_INT48+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext48().toInt();
		Label l=a.newLabel();

		a.mov(rcx,0xFFFF000000000000);
		if(val&uint64(1)<<47)val|=0xFFFF000000000000;
		if(aux<8){
			a.mov(rax,qreg[aux]);
			a.andn(rax,rcx,rax);
			a.bt(rax,47);
			a.jnc(l);
			a.or_(rax,rcx);
			a.bind(l);
			a.cmp(rax,val);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
			a.andn(rax,rcx,rax);
			a.bt(rax,47);
			a.jnc(l);
			a.or_(rax,rcx);
			a.bind(l);
			a.cmp(rax,val);
		}
		jcontent.type='i';


	}break;
	case P_UINT64+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext64();
		if(aux<8){
			a.cmp(qreg[aux],val);
		}else{
			a.cmp(qword_ptr(workspace,aux*8),val);
		}
		jcontent.type='u';
	}break;
	case P_INT64+CMP_W_C:{
		uint8 aux=t.getNext8();
		uint64 val=t.getNext64();
		if(aux<8){
			a.cmp(qreg[aux],val);
		}else{
			a.cmp(qword_ptr(workspace,aux*8),val);
		}
		jcontent.type='i';
	}break;
	case P_UINT8+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint8 val=t.getNext8();
		a.cmp(byte_ptr(memory,aux),val);
		jcontent.type='u';
	}break;
	case P_INT8+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint8 val=t.getNext8();
		a.cmp(byte_ptr(memory,aux),val);
		jcontent.type='i';
	}break;
	case P_UINT16+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint16 val=t.getNext16();
		a.cmp(byte_ptr(memory,aux),val);
		jcontent.type='u';
	}break;
	case P_INT16+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint16 val=t.getNext16();
		a.cmp(word_ptr(memory,aux),val);
		jcontent.type='i';
	}break;
	case P_UINT32+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint32 val=t.getNext32();
		a.cmp(word_ptr(memory,aux),val);
		jcontent.type='u';
	}break;
	case P_INT32+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint32 val=t.getNext32();
		a.cmp(dword_ptr(memory,aux),val);
		jcontent.type='i';
	}break;
	case P_UINT48+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.mov(rax,ptr(memory,aux));
		a.and_(rax,rcx);
		a.cmp(rax,val);
		jcontent.type='u';



	}break;
	case P_INT48+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.mov(rax,ptr(memory,aux));
		a.and_(rax,rcx);
		a.cmp(rax,val);
		jcontent.type='i';


	}break;
	case P_UINT64+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint64 val=t.getNext64();
		a.cmp(qword_ptr(memory,aux),val);
		jcontent.type='u';
	}break;
	case P_INT64+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint64 val=t.getNext64();
		a.cmp(qword_ptr(memory,aux),val);
		jcontent.type='i';
	}break;
	case P_UINT8+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			if(val<8){
				a.cmp(breg[aux],breg[val]);
			}else{
				a.cmp(breg[aux],ptr(workspace,val*8));
			}
		}else{
			if(val<8){
				a.cmp(ptr(workspace,aux*8),breg[val]);
			}else{
				a.mov(al,ptr(workspace,val*8));
				a.cmp(ptr(workspace,aux*8),al);

			}
		}
		jcontent.type='u';
	}break;
	case P_INT8+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			if(val<8){
				a.cmp(breg[aux],breg[val]);
			}else{
				a.cmp(breg[aux],ptr(workspace,val*8));
			}
		}else{
			if(val<8){
				a.cmp(ptr(workspace,aux*8),breg[val]);
			}else{
				a.mov(al,ptr(workspace,val*8));
				a.cmp(ptr(workspace,aux*8),al);

			}
		}
		jcontent.type='i';
	}break;
	case P_UINT16+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			if(val<8){
				a.cmp(wreg[aux],wreg[val]);
			}else{
				a.cmp(wreg[aux],ptr(workspace,val*8));
			}
		}else{
			if(val<8){
				a.cmp(ptr(workspace,aux*8),wreg[val]);
			}else{
				a.mov(ax,ptr(workspace,val*8));
				a.cmp(ptr(workspace,aux*8),ax);

			}
		}
		jcontent.type='u';
	}break;
	case P_INT16+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			if(val<8){
				a.cmp(wreg[aux],wreg[val]);
			}else{
				a.cmp(wreg[aux],ptr(workspace,val*8));
			}
		}else{
			if(val<8){
				a.cmp(ptr(workspace,aux*8),wreg[val]);
			}else{
				a.mov(ax,ptr(workspace,val*8));
				a.cmp(ptr(workspace,aux*8),ax);

			}
		}
		jcontent.type='i';
	}break;
	case P_UINT32+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			if(val<8){
				a.cmp(dreg[aux],dreg[val]);
			}else{
				a.cmp(dreg[aux],ptr(workspace,val*8));
			}
		}else{
			if(val<8){
				a.cmp(ptr(workspace,aux*8),dreg[val]);
			}else{
				a.mov(eax,ptr(workspace,val*8));
				a.cmp(ptr(workspace,aux*8),eax);

			}
		}
		jcontent.type='u';
	}break;
	case P_INT32+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			if(val<8){
				a.cmp(dreg[aux],dreg[val]);
			}else{
				a.cmp(dreg[aux],ptr(workspace,val*8));
			}
		}else{
			if(val<8){
				a.cmp(ptr(workspace,aux*8),dreg[val]);
			}else{
				a.mov(eax,ptr(workspace,val*8));
				a.cmp(ptr(workspace,aux*8),eax);

			}
		}
		jcontent.type='i';
	}break;
	case P_UINT48+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(aux<8){
			a.mov(rax,qreg[aux]);
		}else{
			a.mov(rax,ptr(workspace,aux*8));
		}
		if(val<8){
			a.mov(rbx,qreg[val]);
		}else{
			a.mov(rbx,ptr(workspace,val*8));
		}
		a.and_(rax,rcx);
		a.and_(rbx,rcx);
		a.cmp(rax,rbx);
		jcontent.type='u';



	}break;
	case P_INT48+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		a.mov(rcx,0xFFFF000000000000);
		if(aux<8)a.mov(rax,qreg[aux]);
		else a.mov(rax,ptr(workspace,aux*8));
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,ptr(workspace,val*8));
		a.andn(rax,rcx,rax);
		a.andn(rbx,rcx,rax);
		Label l=a.newLabel();
		Label l1=a.newLabel();
		a.bt(rbx,47);
		a.jnc(l);
		a.or_(rbx,rcx);
		a.bind(l);
		a.bt(rax,47);
		a.jnc(l1);
		a.or_(rax,rcx);
		a.bind(l1);
		a.cmp(rax,rbx);
		jcontent.type='i';



	}break;
	case P_UINT64+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			if(val<8){
				a.cmp(qreg[aux],qreg[val]);
			}else{
				a.cmp(dreg[aux],ptr(workspace,val*8));
			}
		}else{
			if(val<8){
				a.cmp(ptr(workspace,aux*8),qreg[val]);
			}else{
				a.mov(rax,ptr(workspace,val*8));
				a.cmp(ptr(workspace,aux*8),rax);

			}
		}
		jcontent.type='u';
	}break;
	case P_INT64+CMP_W_W:{
		uint8 aux=t.getNext8();
		uint8 val=t.getNext8();
		if(aux<8){
			if(val<8){
				a.cmp(qreg[aux],qreg[val]);
			}else{
				a.cmp(dreg[aux],ptr(workspace,val*8));
			}
		}else{
			if(val<8){
				a.cmp(ptr(workspace,aux*8),qreg[val]);
			}else{
				a.mov(rax,ptr(workspace,val*8));
				a.cmp(ptr(workspace,aux*8),rax);

			}
		}
		jcontent.type='i';
	}break;
	default:
		return 0;
	}
	return 1;
}
