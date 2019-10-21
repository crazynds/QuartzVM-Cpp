/*
* jmp_cmp.cpp
*
*  Created on: 11 de mai de 2019
*      Author: lhlag
*/

#include "../Jit.h"

uint8 jmp_cmp(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v,uint32 startCode,Label reenter){

	switch(jcontent.opcode){
	case PUSH_C:{
		uint64 aux=t.getNext64();

		a.mov(rcx,ptr(rsp));
		pushRegisters(a);
		a.mov(rdx,aux);
		a.call(uint64((void*)Thread::saveInStack));
		popRegisters(a);
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif

	}break;
	case PUSH_W:{
		uint8 aux=t.getNext8();

		a.mov(rcx,ptr(rsp));
		pushRegisters(a);
		if(aux<8){
			a.mov(rdx,qreg[aux]);
		}else{
			a.mov(rdx,ptr(workspace,aux*8));
		}
		a.call(uint64((void*)Thread::saveInStack));
		popRegisters(a);
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif

	}break;
	case POP_W:{
		uint8 aux=t.getNext8();

		a.mov(rcx,ptr(rsp));
		pushRegisters(a);
		a.call(uint64((void*)Thread::recoverInStack));
		popRegisters(a);
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif

		if(aux<8){
			a.mov(qreg[aux],rax);
		}else{
			a.mov(ptr(workspace,aux*8),rax);
		}

	}break;
	case CALL_C:{
		uint32 posAtua=t.getPontCode()-2;
		// empurra a posição atual na pilha
		t.set16InCode(posAtua,JIT_FLAG_ENTER_CODE);
		uint32 aux=t.getNext32();

		a.mov(rcx,ptr(rsp));
		pushRegisters(a);
		a.mov(rdx,((uint64)t.getContexto().getCodContext()<<32)+posAtua);
		a.call(uint64((void*)Thread::saveInStack));
		popRegisters(a);

		if(aux>=jcontent.maxCode|| aux<jcontent.minCode){
			a.mov(rax,uint64(aux));
			a.jmp(end);
		}else for(uint32 x=0;x<v.size();x++){
			#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
			if(v[x].getSecond()==aux){
				a.jmp(v[x].getFirst());
				break;
			}
		}
		t.set32InCode(t.getPontCode()-4,startCode);
	}break;
	case RETURN:{
		a.mov(rcx,ptr(rsp));
		pushRegisters(a);
		a.call(uint64((void*)Thread::recoverInStack));
		a.mov(rdx,rax);
		a.shr(rdx,32);
		popRegisters(a);
		//posição atual é retornada em RAX;
		a.cmp(dx,t.getContexto().getCodContext());
		a.jne(end);
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
		a.cdqe();
		a.mov(rbx,1);
		a.add(rax,6);
		a.jmp(reenter);
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
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
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
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
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

		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
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
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
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
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
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
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
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
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
		a.mov(rax,ptr(memory,aux));
		a.and_(rax,rcx);
		a.cmp(rax,val);
		jcontent.type='u';



	}break;
	case P_INT48+CMP_M_C:{
		uint64 aux=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
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
		#ifndef _FAST_MODE
	a.mov(rcx,0x0000FFFFFFFFFFFF);
#endif
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
