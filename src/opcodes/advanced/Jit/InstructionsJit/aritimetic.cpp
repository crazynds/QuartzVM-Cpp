/*
* Aritimetic.cpp
*
*  Created on: 9 de mai de 2019
*      Author: lhlag
*/

#include "../Jit.h"

uint8 aritimetic(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v){
	Gp memory=rdi;
	Gp workspace=rsi;

	Gp qreg[8];qreg[0]=r8;qreg[1]=r9;qreg[2]=r10;qreg[3]=r11;qreg[4]=r12;qreg[5]=r13;qreg[6]=r14;qreg[7]=r15;
	Gp dreg[8];dreg[0]=r8d;dreg[1]=r9d;dreg[2]=r10d;dreg[3]=r11d;dreg[4]=r12d;dreg[5]=r13d;dreg[6]=r14d;dreg[7]=r15d;
	Gp wreg[8];wreg[0]=r8w;wreg[1]=r9w;wreg[2]=r10w;wreg[3]=r11w;wreg[4]=r12w;wreg[5]=r13w;wreg[6]=r14w;wreg[7]=r15w;
	Gp breg[8];breg[0]=r8b;breg[1]=r9b;breg[2]=r10b;breg[3]=r11b;breg[4]=r12b;breg[5]=r13b;breg[6]=r14b;breg[7]=r15b;

	switch(jcontent.opcode){
	case P_UINT8+DD_W_W:
	case P_INT8+DD_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shr(breg[dst],cl);
		else{
			a.mov(al,ptr(workspace,dst*8));
			a.shr(al,cl);
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_INT8+DD_W_C:
	case P_UINT8+DD_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shr(breg[dst],val);
		else{
			a.mov(al,ptr(workspace,dst*8));
			a.shr(al,val);
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_UINT16+DD_W_W:
	case P_INT16+DD_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shr(wreg[dst],cl);
		else{
			a.mov(ax,word_ptr(workspace,dst*8));
			a.shr(ax,cl);
			a.mov(word_ptr(workspace,dst*8),ax);
		}
	}break;
	case P_INT16+DD_W_C:
	case P_UINT16+DD_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shr(wreg[dst],val);
		else{
			a.mov(ax,word_ptr(workspace,dst*8));
			a.shr(ax,val);
			a.mov(word_ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT32+DD_W_W:
	case P_INT32+DD_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shr(dreg[dst],cl);
		else{
			a.mov(eax,dword_ptr(workspace,dst*8));
			a.shr(eax,cl);
			a.mov(dword_ptr(workspace,dst*8),eax);
		}
	}break;
	case P_INT32+DD_W_C:
	case P_UINT32+DD_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shr(dreg[dst],val);
		else{
			a.mov(eax,dword_ptr(workspace,dst*8));
			a.shr(eax,val);
			a.mov(dword_ptr(workspace,dst*8),eax);
		}
	}break;
	case P_UINT48+DD_W_W:
	case P_INT48+DD_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shr(qreg[dst],cl);
		else{
			a.mov(rax,ptr(workspace,dst*8));
			a.shr(rax,cl);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8+4),ax);
		}
	}break;
	case P_INT48+DD_W_C:
	case P_UINT48+DD_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shr(qreg[dst],val);
		else{
			a.mov(rax,ptr(workspace,dst*8));
			a.shr(rax,val);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8+4),ax);
		}
	}break;
	case P_UINT64+DD_W_W:
	case P_INT64+DD_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shr(qreg[dst],cl);
		else{
			a.mov(rax,qword_ptr(workspace,dst*8));
			a.shr(rax,cl);
			a.mov(qword_ptr(workspace,dst*8),rax);
		}
	}break;
	case P_INT64+DD_W_C:
	case P_UINT64+DD_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shr(qreg[dst],val);
		else{
			a.mov(rax,qword_ptr(workspace,dst*8));
			a.shr(rax,val);
			a.mov(qword_ptr(workspace,dst*8),rax);
		}
	}break;

	case P_UINT8+DE_W_W:
	case P_INT8+DE_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shr(breg[dst],cl);
		else{
			a.mov(al,ptr(workspace,dst*8));
			a.shr(al,cl);
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_INT8+DE_W_C:
	case P_UINT8+DE_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shr(breg[dst],val);
		else{
			a.mov(al,ptr(workspace,dst*8));
			a.shr(al,val);
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_UINT16+DE_W_W:
	case P_INT16+DE_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shl(wreg[dst],cl);
		else{
			a.mov(ax,word_ptr(workspace,dst*8));
			a.shl(ax,cl);
			a.mov(word_ptr(workspace,dst*8),ax);
		}
	}break;
	case P_INT16+DE_W_C:
	case P_UINT16+DE_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shl(wreg[dst],val);
		else{
			a.mov(ax,word_ptr(workspace,dst*8));
			a.shl(ax,val);
			a.mov(word_ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT32+DE_W_W:
	case P_INT32+DE_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shl(dreg[dst],cl);
		else{
			a.mov(eax,dword_ptr(workspace,dst*8));
			a.shl(eax,cl);
			a.mov(dword_ptr(workspace,dst*8),eax);
		}
	}break;
	case P_INT32+DE_W_C:
	case P_UINT32+DE_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shl(dreg[dst],val);
		else{
			a.mov(eax,dword_ptr(workspace,dst*8));
			a.shl(eax,val);
			a.mov(dword_ptr(workspace,dst*8),eax);
		}
	}break;
	case P_UINT48+DE_W_W:
	case P_INT48+DE_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shl(qreg[dst],cl);
		else{
			a.mov(rax,ptr(workspace,dst*8));
			a.shl(rax,cl);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8+4),ax);
		}
	}break;
	case P_INT48+DE_W_C:
	case P_UINT48+DE_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shl(qreg[dst],val);
		else{
			a.mov(rax,ptr(workspace,dst*8));
			a.shl(rax,val);
			a.mov(ptr(workspace,dst*8+2),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT64+DE_W_W:
	case P_INT64+DE_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(cl,breg[val]);
		else a.mov(cl,ptr(workspace,val*8));
		if(dst<8)a.shl(qreg[dst],cl);
		else{
			a.mov(rax,qword_ptr(workspace,dst*8));
			a.shl(rax,cl);
			a.mov(qword_ptr(workspace,dst*8),rax);
		}
	}break;
	case P_INT64+DE_W_C:
	case P_UINT64+DE_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8)a.shl(qreg[dst],val);
		else{
			a.mov(rax,qword_ptr(workspace,dst*8));
			a.shl(rax,val);
			a.mov(qword_ptr(workspace,dst*8),rax);
		}
	}break;
	case P_UINT8+SOMA_M_C:
	case P_INT8+SOMA_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint8 val=t.getNext8();

		a.add(byte_ptr(memory,dst),val);
	}break;
	case P_INT16+SOMA_M_C:
	case P_UINT16+SOMA_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint16 val=t.getNext16();

		a.add(word_ptr(memory,dst),val);
	}break;
	case P_INT32+SOMA_M_C:
	case P_UINT32+SOMA_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint32 val=t.getNext32();

		a.add(dword_ptr(memory,dst),val);
	}break;
	case P_INT48+SOMA_M_C:
	case P_UINT48+SOMA_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		a.mov(rax,ptr(memory,dst));
		a.add(rax,val);
		a.mov(ptr(memory,dst),eax);
		a.shr(rax,32);
		a.mov(ptr(memory,dst+4),ax);
	}break;
	case P_INT64+SOMA_M_C:
	case P_UINT64+SOMA_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext64();

		a.add(qword_ptr(memory,dst),val);
	}break;
	case P_UINT8+SOMA_W_C:
	case P_INT8+SOMA_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(dst<8){
			a.add(breg[dst],val);
		}else{
			a.add(byte_ptr(workspace,dst*8),val);
		}
	}break;
	case P_INT16+SOMA_W_C:
	case P_UINT16+SOMA_W_C:{

		uint8 dst=t.getNext8();
		uint16 val=t.getNext16();

		if(dst<8){
			a.add(wreg[dst],val);
		}else{
			a.add(word_ptr(workspace,dst*8),val);
		}
	}break;
	case P_INT32+SOMA_W_C:
	case P_UINT32+SOMA_W_C:{

		uint8 dst=t.getNext8();
		uint32 val=t.getNext32();

		if(dst<8){
			a.add(dreg[dst],val);
		}else{
			a.add(dword_ptr(workspace,dst*8),val);
		}
	}break;
	case P_INT48+SOMA_W_C:
	case P_UINT48+SOMA_W_C:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		if(dst<8){
			a.mov(rbx,0x0000FFFFFFFFFFFF);
			a.mov(rcx,qreg[dst]);
			a.and_(rcx,rcx);
			a.add(rcx,rbx);
			a.andn(qreg[dst],rbx,qreg[dst]);
			a.or_(qreg[dst],rcx);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.add(rax,val);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+SOMA_W_C:
	case P_UINT64+SOMA_W_C:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext64();

		if(dst<8){
			a.add(qreg[dst],val);
		}else{
			a.add(qword_ptr(workspace,dst*8),val);
		}
	}break;
	case P_UINT8+SOMA_W_M:
	case P_INT8+SOMA_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(bl,ptr(memory,val));

		if(dst<8){
			a.add(breg[dst],bl);
		}else{
			a.add(ptr(workspace,dst*8),bl);
		}
	}break;
	case P_INT16+SOMA_W_M:
	case P_UINT16+SOMA_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(bx,ptr(memory,val));

		if(dst<8){
			a.add(wreg[dst],bx);
		}else{
			a.add(ptr(workspace,dst*8),bx);
		}
	}break;
	case P_INT32+SOMA_W_M:
	case P_UINT32+SOMA_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(ebx,ptr(memory,val));

		if(dst<8){
			a.add(dreg[dst],ebx);
		}else{
			a.add(ptr(workspace,dst*8),ebx);
		}
	}break;
	case P_INT48+SOMA_W_M:
	case P_UINT48+SOMA_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(rbx,ptr(memory,val));
		a.and_(rbx,0x0000FFFFFFFFFFFF);

		if(dst<8){
			a.mov(rcx,qreg[dst]);
			a.and_(rcx,0x0000FFFFFFFFFFFF);
			a.add(rcx,rbx);
			a.and_(qreg[dst],0xFFFF000000000000);
			a.or_(qreg[dst],rcx);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.add(rax,rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+SOMA_W_M:
	case P_UINT64+SOMA_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(rbx,ptr(memory,val));

		if(dst<8){
			a.add(qreg[dst],rbx);
		}else{
			a.add(ptr(workspace,dst*8),rbx);
		}
	}break;
	case P_UINT8+SOMA_W_W:
	case P_INT8+SOMA_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(bl,breg[val]);
		else a.mov(bl,ptr(workspace,val*8));

		if(dst<8){
			a.add(breg[dst],bl);
		}else{
			a.add(ptr(workspace,dst*8),bl);
		}
	}break;
	case P_INT16+SOMA_W_W:
	case P_UINT16+SOMA_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(bx,wreg[val]);
		else a.mov(bx,ptr(workspace,val*8));

		if(dst<8){
			a.add(wreg[dst],bx);
		}else{
			a.add(ptr(workspace,dst*8),bx);
		}
	}break;
	case P_INT32+SOMA_W_W:
	case P_UINT32+SOMA_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(ebx,dreg[val]);
		else a.mov(ebx,ptr(workspace,val*8));

		if(dst<8){
			a.add(dreg[dst],ebx);
		}else{
			a.add(ptr(workspace,dst*8),ebx);
		}
	}break;
	case P_INT48+SOMA_W_W:
	case P_UINT48+SOMA_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,ptr(workspace,val*8));

		if(dst<8){
			a.mov(rcx,qreg[dst]);
			a.add(rcx,rbx);
			a.and_(qreg[dst],0xFFFF000000000000);
			a.and_(rcx,0x0000FFFFFFFFFFFF);
			a.or_(qreg[dst],rcx);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.add(rax,rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+SOMA_W_W:
	case P_UINT64+SOMA_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,ptr(workspace,val*8));

		if(dst<8){
			a.add(qreg[dst],rbx);
		}else{
			a.add(ptr(workspace,dst*8),rbx);
		}
	}break;
	case P_UINT8+SUB_M_C:
	case P_INT8+SUB_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint8 val=t.getNext8();

		a.sub(byte_ptr(memory,dst),val);
	}break;
	case P_INT16+SUB_M_C:
	case P_UINT16+SUB_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint16 val=t.getNext16();

		a.sub(word_ptr(memory,dst),val);
	}break;
	case P_INT32+SUB_M_C:
	case P_UINT32+SUB_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint32 val=t.getNext32();

		a.sub(dword_ptr(memory,dst),val);
	}break;
	case P_INT48+SUB_M_C:
	case P_UINT48+SUB_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		a.mov(rax,ptr(memory,dst));
		a.sub(rax,val);
		a.mov(ptr(memory,dst),eax);
		a.shr(rax,32);
		a.mov(ptr(memory,dst+4),ax);
	}break;
	case P_INT64+SUB_M_C:
	case P_UINT64+SUB_M_C:{

		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext64();

		a.sub(qword_ptr(memory,dst),val);
	}break;
	case P_UINT8+SUB_W_C:
	case P_INT8+SUB_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(dst<8){
			a.sub(breg[dst],val);
		}else{
			a.sub(byte_ptr(workspace,dst*8),val);
		}
	}break;
	case P_INT16+SUB_W_C:
	case P_UINT16+SUB_W_C:{

		uint8 dst=t.getNext8();
		uint16 val=t.getNext16();

		if(dst<8){
			a.sub(wreg[dst],val);
		}else{
			a.sub(word_ptr(workspace,dst*8),val);
		}
	}break;
	case P_INT32+SUB_W_C:
	case P_UINT32+SUB_W_C:{

		uint8 dst=t.getNext8();
		uint32 val=t.getNext32();

		if(dst<8){
			a.sub(dreg[dst],val);
		}else{
			a.sub(dword_ptr(workspace,dst*8),val);
		}
	}break;
	case P_INT48+SUB_W_C:
	case P_UINT48+SUB_W_C:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		if(dst<8){
			a.mov(rcx,qreg[dst]);
			a.and_(rcx,0x0000FFFFFFFFFFFF);
			a.sub(rcx,val);
			a.and_(qreg[dst],0xFFFF000000000000);
			a.or_(qreg[dst],rcx);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.sub(rax,val);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+SUB_W_C:
	case P_UINT64+SUB_W_C:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext64();

		if(dst<8){
			a.sub(qreg[dst],val);
		}else{
			a.sub(qword_ptr(workspace,dst*8),val);
		}
	}break;
	case P_UINT8+SUB_W_M:
	case P_INT8+SUB_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(bl,ptr(memory,val));

		if(dst<8){
			a.sub(breg[dst],bl);
		}else{
			a.sub(ptr(workspace,dst*8),bl);
		}
	}break;
	case P_INT16+SUB_W_M:
	case P_UINT16+SUB_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(bx,ptr(memory,val));

		if(dst<8){
			a.sub(wreg[dst],bx);
		}else{
			a.sub(ptr(workspace,dst*8),bx);
		}
	}break;
	case P_INT32+SUB_W_M:
	case P_UINT32+SUB_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(ebx,ptr(memory,val));

		if(dst<8){
			a.sub(dreg[dst],ebx);
		}else{
			a.sub(ptr(workspace,dst*8),ebx);
		}
	}break;
	case P_INT48+SUB_W_M:
	case P_UINT48+SUB_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(rbx,ptr(memory,val));
		a.and_(rbx,0x0000FFFFFFFFFFFF);

		if(dst<8){
			a.mov(rcx,qreg[dst]);
			a.and_(rcx,0x0000FFFFFFFFFFFF);
			a.sub(rcx,rbx);
			a.and_(qreg[dst],0xFFFF000000000000);
			a.or_(qreg[dst],rcx);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.sub(rax,rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+SUB_W_M:
	case P_UINT64+SUB_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(rbx,ptr(memory,val));

		if(dst<8){
			a.sub(qreg[dst],rbx);
		}else{
			a.sub(ptr(workspace,dst*8),rbx);
		}
	}break;
	case P_UINT8+SUB_W_W:
	case P_INT8+SUB_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(bl,breg[val]);
		else a.mov(bl,ptr(workspace,val*8));

		if(dst<8){
			a.sub(breg[dst],bl);
		}else{
			a.sub(ptr(workspace,dst*8),bl);
		}
	}break;
	case P_INT16+SUB_W_W:
	case P_UINT16+SUB_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(bx,wreg[val]);
		else a.mov(bx,ptr(workspace,val*8));

		if(dst<8){
			a.sub(wreg[dst],bx);
		}else{
			a.sub(ptr(workspace,dst*8),bx);
		}
	}break;
	case P_INT32+SUB_W_W:
	case P_UINT32+SUB_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(ebx,dreg[val]);
		else a.mov(ebx,ptr(workspace,val*8));

		if(dst<8){
			a.sub(dreg[dst],ebx);
		}else{
			a.sub(ptr(workspace,dst*8),ebx);
		}
	}break;
	case P_INT48+SUB_W_W:
	case P_UINT48+SUB_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,ptr(workspace,val*8));
		a.and_(rbx,0x0000FFFFFFFFFFFF);

		if(dst<8){
			a.mov(rcx,qreg[dst]);
			a.and_(rcx,0x0000FFFFFFFFFFFF);
			a.sub(rcx,rbx);
			a.and_(qreg[dst],0xFFFF000000000000);
			a.or_(qreg[dst],rcx);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.sub(rax,rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+SUB_W_W:
	case P_UINT64+SUB_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,ptr(workspace,val*8));

		if(dst<8){
			a.sub(qreg[dst],rbx);
		}else{
			a.sub(ptr(workspace,dst*8),rbx);
		}
	}break;
	case P_UINT8+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint8 val=t.getNext8();
		a.mov(bl,val);
		a.mov(al,ptr(memory,dst));
		a.mul(bl);
		a.mov(ptr(memory,dst),al);
	}break;
	case P_UINT16+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint16 val=t.getNext16();
		a.mov(bx,val);
		a.mov(ax,ptr(memory,dst));
		a.mul(bx);
		a.mov(ptr(memory,dst),ax);
	}break;
	case P_UINT32+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint32 val=t.getNext32();
		a.mov(ebx,val);
		a.mov(eax,ptr(memory,dst));
		a.mul(ebx);
		a.mov(ptr(memory,dst),eax);
	}break;
	case P_UINT48+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		a.mov(rax,ptr(memory,dst));
		a.mov(rbx,val);
		a.and_(rax,0x0000FFFFFFFFFFFF);
		a.mul(rbx);
		a.mov(ptr(memory,dst),eax);
		a.shr(rax,32);
		a.mov(ptr(memory,dst+4),ax);
	}break;
	case P_UINT64+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext64();
		a.mov(rbx,val);
		a.mov(rax,ptr(memory,dst));
		a.mul(rbx);
		a.mov(ptr(memory,dst),rax);
	}break;
	case P_UINT8+MUL_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(dst<8){
			a.mov(bl,val);
			a.mov(al,breg[dst]);
			a.mul(bl);
			a.mov(breg[dst],al);
		}else{
			a.mov(bl,val);
			a.mov(al,ptr(workspace,dst*8));
			a.mul(bl);
			a.mov(ptr(workspace,dst*8),al);
		}

	}break;
	case P_UINT16+MUL_W_C:{

		uint8 dst=t.getNext8();
		uint16 val=t.getNext16();

		if(dst<8){
			a.mov(bx,val);
			a.mov(ax,wreg[dst]);
			a.mul(bx);
			a.mov(wreg[dst],ax);
		}else{
			a.mov(bx,val);
			a.mov(ax,ptr(workspace,dst*8));
			a.mul(bx);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT32+MUL_W_C:{

		uint8 dst=t.getNext8();
		uint32 val=t.getNext32();

		if(dst<8){
			a.mov(ebx,val);
			a.mov(eax,dreg[dst]);
			a.mul(ebx);
			a.mov(dreg[dst],eax);
		}else{
			a.mov(ebx,val);
			a.mov(eax,ptr(workspace,dst*8));
			a.mul(ebx);
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_UINT48+MUL_W_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,0x0000FFFFFFFFFFFF);
			a.mov(rbx,val);
			a.mul(rbx);
			a.and_(rax,0x0000FFFFFFFFFFFF);
			a.and_(qreg[dst],0xFFFF000000000000);
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,0x0000FFFFFFFFFFFF);
			a.mov(rbx,val);
			a.mul(rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8+4),ax);
		}
	}break;
	case P_UINT64+MUL_W_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext64();

		if(dst<8){
			a.mov(rbx,val);
			a.mov(rax,qreg[dst]);
			a.mul(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rbx,val);
			a.mov(rax,ptr(workspace,dst*8));
			a.mul(rbx);
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_UINT8+MUL_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		if(dst<8){
			a.mov(bl,ptr(memory,val));
			a.mov(al,breg[dst]);
			a.mul(bl);
			a.mov(breg[dst],al);
		}else{
			a.mov(bl,ptr(memory,val));
			a.mov(al,ptr(workspace,dst*8));
			a.mul(bl);
			a.mov(ptr(workspace,dst*8),al);
		}

	}break;
	case P_UINT16+MUL_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		if(dst<8){
			a.mov(bx,ptr(memory,val));
			a.mov(ax,wreg[dst]);
			a.mul(bx);
			a.mov(wreg[dst],ax);
		}else{
			a.mov(bx,ptr(memory,val));
			a.mov(ax,ptr(workspace,dst*8));
			a.mul(bx);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT32+MUL_W_M:{

		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		if(dst<8){
			a.mov(ebx,ptr(memory,val));
			a.mov(eax,dreg[dst]);
			a.mul(ebx);
			a.mov(dreg[dst],eax);
		}else{
			a.mov(ebx,ptr(memory,val));
			a.mov(eax,ptr(workspace,dst*8));
			a.mul(ebx);
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_UINT48+MUL_W_M:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,0x0000FFFFFFFFFFFF);
			a.mov(rbx,ptr(memory,val));
			a.and_(rbx,0x0000FFFFFFFFFFFF);
			a.mul(rbx);
			a.and_(rax,0x0000FFFFFFFFFFFF);
			a.and_(qreg[dst],0xFFFF000000000000);
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(memory,dst));
			a.and_(rax,0x0000FFFFFFFFFFFF);
			a.mov(rbx,ptr(memory,val));
			a.and_(rbx,0x0000FFFFFFFFFFFF);
			a.mul(rbx);
			a.mov(ptr(memory,dst),eax);
			a.shr(rax,32);
			a.mov(ptr(memory,dst+4),ax);
		}
	}break;
	case P_UINT64+MUL_W_M:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();

		if(dst<8){
			a.mov(rbx,ptr(memory,val));
			a.mov(rax,qreg[dst]);
			a.mul(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rbx,ptr(memory,val));
			a.mov(rax,ptr(workspace,dst*8));
			a.mul(rbx);
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_UINT8+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8){
			a.mov(bl,breg[val]);
		}else{
			a.mov(bl,ptr(workspace,val*8));
		}

		if(dst<8){
			a.mov(al,breg[dst]);
			a.mul(bl);
			a.mov(breg[dst],al);
		}else{
			a.mov(al,ptr(workspace,dst*8));
			a.mul(bl);
			a.mov(ptr(workspace,dst*8),al);
		}

	}break;
	case P_UINT16+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8){
			a.mov(bx,wreg[val]);
		}else{
			a.mov(bx,ptr(workspace,val*8));
		}


		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.mul(bx);
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.mul(bx);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT32+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8){
			a.mov(ebx,dreg[val]);
		}else{
			a.mov(ebx,ptr(workspace,val*8));
		}

		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.mul(ebx);
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.mul(ebx);
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_UINT48+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8){
			a.mov(rbx,qreg[val]);
		}else{
			a.mov(rbx,ptr(workspace,val*8));
		}
		a.and_(rbx,rcx);//0x0000ff..
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx);//0x0000ff..
			a.mul(rbx);
			a.and_(rax,rcx); //0x0000ff..
			a.not_(rcx);
			a.and_(qreg[dst],rcx); //0xffff00..
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(memory,dst));
			a.and_(rax,rcx);//0x0000ff..
			a.mul(rbx);
			a.mov(ptr(memory,dst),eax);
			a.shr(rax,32);
			a.mov(ptr(memory,dst+4),ax);
		}
	}break;
	case P_UINT64+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8){
			a.mov(rbx,qreg[val]);
		}else{
			a.mov(rbx,ptr(workspace,val*8));
		}

		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.mul(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.mul(rbx);
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_INT8+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint8 val=t.getNext8();
		a.mov(al,ptr(memory,dst));
		a.mov(bl,val);
		a.imul(bl);
		a.mov(ptr(memory,dst),al);
	}break;
	case P_INT16+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint16 val=t.getNext16();
		a.mov(ax,ptr(memory,dst));
		a.mov(bx,val);
		a.imul(bx);
		a.mov(ptr(memory,dst),ax);
	}break;
	case P_INT32+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint32 val=t.getNext32();
		a.mov(eax,ptr(memory,dst));
		a.mov(ebx,val);
		a.imul(ebx);
		a.mov(ptr(memory,dst),eax);
	}break;
	case P_INT48+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.mov(rax,ptr(memory,dst));
		a.and_(rax,rcx);//0x0000ff..
		a.bt(rax,47);
		Label t=a.newLabel();
		a.jnc(t);
		a.not_(rcx);
		a.or_(rax,rcx);//0xffff00..
		a.bind(t);
		if(val&(uint64(1)<<47)){
			val|=0xFFFF000000000000;
		}
		a.mov(rbx,val);
		a.imul(rbx);
		a.mov(ptr(memory,dst),eax);
		a.shr(rax,32);
		a.mov(ptr(memory,dst+4),ax);
	}break;
	case P_INT64+MUL_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext64();
		a.mov(rax,ptr(memory,dst));
		a.mov(rbx,val);
		a.imul(rbx);
		a.mov(ptr(memory,dst),rax);
	}break;
	case P_INT8+MUL_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8){
			a.mov(al,breg[dst]);
			a.mov(bl,val);
			a.imul(bl);
			a.mov(breg[dst],al);
		}else{
			a.mov(al,ptr(workspace,dst*8));
			a.mov(bl,val);
			a.imul(bl);
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_INT16+MUL_W_C:{
		uint8 dst=t.getNext8();
		uint16 val=t.getNext16();
		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.mov(bx,val);
			a.imul(bx);
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.mov(bx,val);
			a.imul(bx);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_INT32+MUL_W_C:{
		uint8 dst=t.getNext8();
		uint32 val=t.getNext32();
		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.mov(ebx,val);
			a.imul(ebx);
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.mov(ebx,val);
			a.imul(ebx);
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_INT48+MUL_W_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx);//0x0000ff..
			a.bt(rax,47);
			Label t=a.newLabel();
			a.jnc(t);
			a.not_(rcx);
			a.or_(rax,rcx);//0xffff00..
			a.not_(rcx);
			a.bind(t);
			if(val&(uint64(1)<<47)){
				val|=0xFFFF000000000000;
			}
			a.mov(rbx,val);
			a.imul(rbx);
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.and_(qreg[dst],rcx);//0xffff00..
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,rcx);//0x0000ff..
			a.bt(rax,47);
			Label t=a.newLabel();
			a.jnc(t);
			a.not_(rcx);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			if(val&(uint64(1)<<47)){
				val|=0xFFFF000000000000;
			}
			a.mov(rbx,val);
			a.imul(rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8+4),ax);
		}
	}break;
	case P_INT64+MUL_W_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext64();
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.mov(rbx,val);
			a.imul(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.mov(rbx,val);
			a.imul(rbx);
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_INT8+MUL_W_M:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(dst<8){
			a.mov(al,breg[dst]);
			a.mov(bl,ptr(memory,val));
			a.imul(bl);
			a.mov(breg[dst],al);
		}else{
			a.mov(al,ptr(workspace,dst*8));
			a.mov(bl,ptr(memory,val));
			a.imul(bl);
			a.mov(ptr(workspace,dst*8),al);
		}

	}break;
	case P_INT16+MUL_W_M:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.mov(bx,ptr(memory,val));
			a.imul(bx);
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.mov(bx,ptr(memory,val));
			a.imul(bx);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_INT32+MUL_W_M:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.mov(ebx,ptr(memory,val));
			a.imul(ebx);
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.mov(ebx,ptr(memory,val));
			a.imul(ebx);
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_INT48+MUL_W_M:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx);//0x0000ff..
			a.mov(rbx,ptr(memory,val));
			a.and_(rbx,rcx);//0x0000ff..
			a.bt(rax,47);
			a.not_(rcx);
			Label t=a.newLabel();
			a.jnc(t);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			a.bt(rbx,47);
			Label t2=a.newLabel();
			a.jnc(t2);
			a.or_(rbx,rcx);//0xffff00..
			a.bind(t2);
			a.not_(rcx);
			a.imul(rbx);
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.and_(qreg[dst],rcx);//0xffff00..
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,rcx);//0x0000ff..
			a.mov(rbx,ptr(memory,val));
			a.and_(rbx,rcx);//0x0000ff..
			a.bt(rax,47);
			a.not_(rcx);
			Label t=a.newLabel();
			a.jnc(t);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			a.bt(rbx,47);
			Label t2=a.newLabel();
			a.jnc(t2);
			a.or_(rbx,rcx);//0xffff00..
			a.bind(t2);
			a.not_(rcx);
			a.imul(rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+MUL_W_M:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.mov(rbx,ptr(memory,val));
			a.imul(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.mov(rbx,ptr(memory,val));
			a.imul(rbx);
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_INT8+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(bl,breg[val]);
		else a.mov(bl,ptr(workspace,val*8));
		if(dst<8){
			a.mov(al,breg[dst]);
			a.imul(bl);
			a.mov(breg[dst],al);
		}else{
			a.mov(al,ptr(workspace,dst*8));
			a.imul(bl);
			a.mov(ptr(workspace,dst*8),al);
		}

	}break;
	case P_INT16+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(bx,wreg[val]);
		else a.mov(bx,ptr(workspace,val*8));
		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.imul(bx);
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.imul(bx);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_INT32+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		if(val<8)a.mov(ebx,dreg[val]);
		else a.mov(ebx,ptr(workspace,val*8));
		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.imul(ebx);
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.imul(ebx);
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_INT48+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,ptr(workspace,val*8));
		a.and_(rbx,rcx);//0x0000ff..
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.bt(rax,47);
			Label t=a.newLabel();
			a.jnc(t);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			a.bt(rbx,47);
			Label t2=a.newLabel();
			a.jnc(t2);
			a.or_(rbx,rcx);
			a.bind(t2);
			a.not_(rcx);
			a.imul(rbx);
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.and_(qreg[dst],rcx);//0xffff00..
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.bt(rax,47);
			Label t=a.newLabel();
			a.jnc(t);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			a.bt(rbx,47);
			Label t2=a.newLabel();
			a.jnc(t2);
			a.or_(rbx,rcx);//0xffff00..
			a.bind(t2);
			a.imul(rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+MUL_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,ptr(workspace,val*8));
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.imul(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.imul(rbx);
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_UINT8+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.mov(bl,val);
		if(dst<8){
			a.movzx(ax,breg[dst]);
			a.div(bl);
			a.mov(breg[dst],al);
		}else{
			a.movzx(ax,byte_ptr(workspace,dst*8));
			a.div(bl);
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_UINT16+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint16 val=t.getNext16();
		a.mov(bx,val);
		a.xor_(edx,edx);
		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.div(bx);
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.div(bx);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT32+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint32 val=t.getNext16();
		a.mov(ebx,val);
		a.xor_(edx,edx);
		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.div(ebx);
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.div(ebx);
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_UINT48+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rbx,val);
		a.xor_(rdx,rdx);
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx);
			a.div(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,rcx);
			a.div(rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT64+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext64();
		a.mov(rbx,val);
		a.xor_(rdx,rdx);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.div(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.div(rbx);
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_UINT8+DIV_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint8 val=t.getNext8();
		a.mov(bl,val);
		a.xor_(edx,edx);
		a.movzx(ax,byte_ptr(memory,dst));
		a.div(bl);
		a.mov(byte_ptr(memory,dst),al);
	}break;
	case P_UINT16+DIV_M_C:{
		uint8 dst=t.getNext8();
		uint16 val=t.getNext16();
		a.mov(bx,val);
		a.xor_(edx,edx);
		a.mov(ax,ptr(memory,dst));
		a.div(bx);
		a.mov(ptr(memory,dst),ax);
	}break;
	case P_UINT32+DIV_M_C:{
		uint8 dst=t.getNext8();
		uint32 val=t.getNext16();
		a.mov(ebx,val);
		a.xor_(edx,edx);
		a.mov(eax,ptr(memory,dst));
		a.div(ebx);
		a.mov(ptr(memory,dst),eax);
	}break;
	case P_UINT48+DIV_M_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rbx,val);
		a.xor_(rdx,rdx);
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.mov(rax,ptr(memory,dst));
		a.and_(rax,rcx);
		a.div(rbx);
		a.mov(ptr(memory,dst),eax);
		a.shr(rax,32);
		a.mov(ptr(memory,dst+4),ax);
	}break;
	case P_UINT64+DIV_M_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext64();
		a.mov(rbx,val);
		a.xor_(rdx,rdx);
		a.mov(rax,ptr(memory,dst));
		a.div(rbx);
		a.mov(ptr(memory,dst),rax);
	}break;
	case P_UINT8+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		if(dst<8){
			a.movzx(ax,breg[dst]);
			a.div(byte_ptr(memory,pos));
			a.mov(breg[dst],al);
		}else{
			a.movzx(ax,byte_ptr(workspace,dst*8));
			a.div(byte_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_UINT16+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		a.xor_(edx,edx);
		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.div(word_ptr(memory,pos));
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.div(word_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT32+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		a.mov(ebx,ptr(memory,pos));
		a.xor_(edx,edx);
		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.div(dword_ptr(memory,pos));
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.div(dword_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_UINT48+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		a.mov(rbx,ptr(memory,pos));
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.xor_(rdx,rdx);
		a.and_(rbx,rcx);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx);
			a.div(qword_ptr(memory,pos));
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,rcx);
			a.div(qword_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT64+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		a.mov(rbx,ptr(memory,pos));
		a.xor_(rdx,rdx);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.div(qword_ptr(memory,pos));
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.div(qword_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_INT8+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.mov(bl,val);
		if(dst<8){
			a.movsx(ax,breg[dst]);
			a.idiv(bl);
			a.mov(breg[dst],al);
		}else{
			a.movsx(ax,byte_ptr(workspace,dst*8));
			a.idiv(bl);
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_INT16+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint16 val=t.getNext16();
		a.mov(bx,val);
		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.cwd();
			a.idiv(bx);
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.cwd();
			a.idiv(bx);
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_INT32+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint32 val=t.getNext16();
		a.mov(ebx,val);
		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.cdq();
			a.idiv(ebx);
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.cdq();
			a.idiv(ebx);
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_INT48+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx); // 0x0000ff..
			a.bt(rax,47);
			Label t=a.newLabel();
			a.jnc(t);
			a.not_(rcx);
			a.or_(rax,rcx);//0xffff00..
			a.not_(rcx);
			a.bind(t);
			if(val&(uint64(1)<<47)){
				val|=0xFFFF000000000000;
			}
			a.mov(rbx,val);
			a.cqo();
			a.idiv(rbx);
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.and_(qreg[dst],rcx);//0xffff00..
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,rcx);//0x0000ff..
			a.bt(rax,47);
			Label t=a.newLabel();
			a.jnc(t);
			a.not_(rcx);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			if(val&(uint64(1)<<47)){
				val|=0xFFFF000000000000;
			}
			a.mov(rbx,val);
			a.cqo();
			a.idiv(rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8+4),ax);
		}
	}break;
	case P_INT64+DIV_W_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext64();
		a.mov(rbx,val);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.cqo();
			a.idiv(rbx);
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.cqo();
			a.idiv(rbx);
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_INT8+DIV_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint8 val=t.getNext8();
		a.mov(bl,val);
		a.movsx(ax,byte_ptr(memory,dst));
		a.idiv(bl);
		a.mov(byte_ptr(memory,dst),al);
	}break;
	case P_INT16+DIV_M_C:{
		uint8 dst=t.getNext8();
		uint16 val=t.getNext16();
		a.mov(bx,val);
		a.mov(ax,ptr(memory,dst));
		a.cwd();
		a.idiv(bx);
		a.mov(ptr(memory,dst),ax);
	}break;
	case P_INT32+DIV_M_C:{
		uint8 dst=t.getNext8();
		uint32 val=t.getNext16();
		a.mov(ebx,val);
		a.mov(eax,ptr(memory,dst));
		a.cdq();
		a.idiv(ebx);
		a.mov(ptr(memory,dst),eax);
	}break;
	case P_INT48+DIV_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		a.mov(rax,ptr(memory,dst));
		a.and_(rax,rcx);//0x0000ff..
		a.bt(rax,47);
		Label t=a.newLabel();
		a.jnc(t);
		a.not_(rcx);
		a.or_(rax,rcx);//0xffff00..
		a.bind(t);
		if(val&(uint64(1)<<47)){
			val|=0xFFFF000000000000;
		}
		a.mov(rbx,val);
		a.cqo();
		a.idiv(rbx);
		a.mov(ptr(memory,dst),eax);
		a.shr(rax,32);
		a.mov(ptr(memory,dst+4),ax);
	}break;
	case P_INT64+DIV_M_C:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext64();
		a.mov(rbx,val);
		a.mov(rax,ptr(memory,dst));
		a.cqo();
		a.idiv(rbx);
		a.mov(ptr(memory,dst),rax);
	}break;
	case P_INT8+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		if(dst<8){
			a.movsx(ax,breg[dst]);
			a.idiv(byte_ptr(memory,pos));
			a.mov(breg[dst],al);
		}else{
			a.movsx(ax,byte_ptr(workspace,dst*8));
			a.idiv(byte_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_INT16+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.cwd();
			a.idiv(word_ptr(memory,pos));
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.cwd();
			a.idiv(word_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_INT32+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		a.mov(ebx,ptr(memory,pos));
		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.cdq();
			a.idiv(dword_ptr(memory,pos));
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.cdq();
			a.idiv(dword_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_INT48+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx);//0x0000ff..
			a.mov(rbx,ptr(memory,val));
			a.and_(rbx,rcx);//0x0000ff..
			a.bt(rax,47);
			a.not_(rcx);
			Label t=a.newLabel();
			a.jnc(t);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			a.bt(rbx,47);
			Label t2=a.newLabel();
			a.jnc(t2);
			a.or_(rbx,rcx);//0xffff00..
			a.bind(t2);
			a.not_(rcx);
			a.cqo();
			a.idiv(rbx);
			a.and_(rax,rcx); //0x0000ff..
			a.not_(rcx);
			a.and_(qreg[dst],rcx); // 0xffff00...
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,rcx);//0x0000ff..
			a.mov(rbx,ptr(memory,val));
			a.and_(rbx,rcx);//0x0000ff..
			a.bt(rax,47);
			a.not_(rcx);
			Label t=a.newLabel();
			a.jnc(t);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			a.bt(rbx,47);
			Label t2=a.newLabel();
			a.jnc(t2);
			a.or_(rbx,rcx);//0xffff00..
			a.bind(t2);
			a.cqo();
			a.idiv(rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+DIV_W_M:{
		uint8 dst=t.getNext8();
		uint64 pos=t.getNext48().toInt();
		a.mov(rbx,ptr(memory,pos));
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.cqo();
			a.idiv(qword_ptr(memory,pos));
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.cqo();
			a.idiv(qword_ptr(memory,pos));
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_UINT8+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8){
			a.movzx(ax,breg[dst]);
			if(val<8){
				a.div(breg[val]);
			}else{
				a.div(byte_ptr(workspace,val*8));
			}
			a.mov(breg[dst],al);
		}else{
			a.movzx(ax,byte_ptr(workspace,dst*8));
			if(val<8){
				a.div(breg[val]);
			}else{
				a.div(byte_ptr(workspace,val*8));
			}
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_UINT16+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.xor_(edx,edx);
		if(dst<8){
			a.mov(ax,wreg[dst]);
			if(val<8){
				a.div(wreg[val]);
			}else{
				a.div(word_ptr(workspace,val*8));
			}
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			if(val<8){
				a.div(wreg[val]);
			}else{
				a.div(word_ptr(workspace,val*8));
			}
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_UINT32+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.xor_(edx,edx);
		if(dst<8){
			a.mov(eax,dreg[dst]);
			if(val<8){
				a.div(dreg[val]);
			}else{
				a.div(dword_ptr(workspace,val*8));
			}
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			if(val<8){
				a.div(dreg[val]);
			}else{
				a.div(dword_ptr(workspace,val*8));
			}
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_UINT48+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.xor_(rdx,rdx);
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8){
			a.mov(rbx,qreg[val]);
		}else{
			a.mov(rbx,ptr(workspace,val*8));
		}
		a.and_(rbx,rcx);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx); //0x0000FF..
			a.div(rbx);
			a.and_(rax,rcx);//0x0000FF..
			a.not_(rcx);
			a.and_(qreg[dst],rcx);//0xffff00..
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(memory,dst));
			a.and_(rax,rcx);//0x0000FF..
			a.div(rbx);
			a.mov(ptr(memory,dst),eax);
			a.shr(rax,32);
			a.mov(ptr(memory,dst+4),ax);
		}
	}break;
	case P_UINT64+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.xor_(rdx,rdx);
		if(dst<8){
			a.mov(rax,qreg[dst]);
			if(val<8){
				a.div(qreg[val]);
			}else{
				a.div(qword_ptr(workspace,val*8));
			}
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			if(val<8){
				a.div(qreg[val]);
			}else{
				a.div(qword_ptr(workspace,val*8));
			}
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	case P_INT8+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8){
			a.movsx(ax,breg[dst]);
			if(val<8){
				a.idiv(breg[val]);
			}else{
				a.idiv(byte_ptr(workspace,val*8));
			}
			a.mov(breg[dst],al);
		}else{
			a.movsx(ax,byte_ptr(workspace,dst*8));
			if(val<8){
				a.idiv(breg[val]);
			}else{
				a.idiv(byte_ptr(workspace,val*8));
			}
			a.mov(ptr(workspace,dst*8),al);
		}
	}break;
	case P_INT16+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8){
			a.mov(ax,wreg[dst]);
			a.cwd();
			if(val<8){
				a.idiv(wreg[val]);
			}else{
				a.idiv(word_ptr(workspace,val*8));
			}
			a.mov(wreg[dst],ax);
		}else{
			a.mov(ax,ptr(workspace,dst*8));
			a.cwd();
			if(val<8){
				a.idiv(wreg[val]);
			}else{
				a.idiv(word_ptr(workspace,val*8));
			}
			a.mov(ptr(workspace,dst*8),ax);
		}
	}break;
	case P_INT32+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8){
			a.mov(eax,dreg[dst]);
			a.cdq();
			if(val<8){
				a.idiv(dreg[val]);
			}else{
				a.idiv(dword_ptr(workspace,val*8));
			}
			a.mov(dreg[dst],eax);
		}else{
			a.mov(eax,ptr(workspace,dst*8));
			a.cdq();
			if(val<8){
				a.idiv(dreg[val]);
			}else{
				a.idiv(dword_ptr(workspace,val*8));
			}
			a.mov(ptr(workspace,dst*8),eax);
		}
	}break;
	case P_INT48+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,ptr(workspace,val*8));
		a.and_(rbx,rcx);//0x0000ff..
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.bt(rax,47);
			Label t=a.newLabel();
			a.jnc(t);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			a.bt(rbx,47);
			Label t2=a.newLabel();
			a.jnc(t2);
			a.or_(rbx,rcx);
			a.bind(t2);
			a.not_(rcx);
			a.cqo();
			a.idiv(rbx);
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.and_(qreg[dst],rcx);//0xffff00..
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.and_(rax,rcx);//0x0000ff..
			a.not_(rcx);
			a.bt(rax,47);
			Label t=a.newLabel();
			a.jnc(t);
			a.or_(rax,rcx);//0xffff00..
			a.bind(t);
			a.bt(rbx,47);
			Label t2=a.newLabel();
			a.jnc(t2);
			a.or_(rbx,rcx);//0xffff00..
			a.bind(t2);
			a.cqo();
			a.idiv(rbx);
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,(dst*8)+4),ax);
		}
	}break;
	case P_INT64+DIV_W_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		if(dst<8){
			a.mov(rax,qreg[dst]);
			a.cqo();
			if(val<8){
				a.idiv(qreg[val]);
			}else{
				a.idiv(qword_ptr(workspace,val*8));
			}
			a.mov(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(workspace,dst*8));
			a.cqo();
			if(val<8){
				a.idiv(qreg[val]);
			}else{
				a.idiv(qword_ptr(workspace,val*8));
			}
			a.mov(ptr(workspace,dst*8),rax);
		}
	}break;
	default:
		return 0;
	}
	return 1;
}

