

#include "../Jit.h"




uint8 cmov(JitContentsAuxiliar jcontent,Thread &t, Assembler &a, Label &end,std::vector<Dupla<Label,uint32>> &v){
	Gp memory=rdi;
	Gp workspace=rsi;

	Gp qreg[8];qreg[0]=r8;qreg[1]=r9;qreg[2]=r10;qreg[3]=r11;qreg[4]=r12;qreg[5]=r13;qreg[6]=r14;qreg[7]=r15;
	Gp dreg[8];dreg[0]=r8d;dreg[1]=r9d;dreg[2]=r10d;dreg[3]=r11d;dreg[4]=r12d;dreg[5]=r13d;dreg[6]=r14d;dreg[7]=r15d;
	Gp wreg[8];wreg[0]=r8w;wreg[1]=r9w;wreg[2]=r10w;wreg[3]=r11w;wreg[4]=r12w;wreg[5]=r13w;wreg[6]=r14w;wreg[7]=r15w;
	Gp breg[8];breg[0]=r8b;breg[1]=r9b;breg[2]=r10b;breg[3]=r11b;breg[4]=r12b;breg[5]=r13b;breg[6]=r14b;breg[7]=r15b;

	switch(jcontent.opcode){
	case CMOV_IG_W_C+P_UINT8:
	case CMOV_IG_W_C+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			a.cmove(breg[mem],val);
		}else{
			Label aux=a.newLabel();
			a.jne(aux);
			a.mov(byte_ptr(workspace,8*mem),val);
			a.bind(aux);
		}
	}break;
	case CMOV_IG_W_C+P_UINT16:
	case CMOV_IG_W_C+P_INT16:{
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();
		if(mem<8){
			a.cmove(wreg[mem],val);
		}else{
			Label aux=a.newLabel();
			a.jne(aux);
			a.mov(word_ptr(workspace,8*mem),val);
			a.bind(aux);
		}
	}break;
	case CMOV_IG_W_C+P_UINT32:
	case CMOV_IG_W_C+P_INT32:{
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();
		if(mem<8){
			a.cmove(dreg[mem],val);
		}else{
			Label aux=a.newLabel();
			a.jne(aux);
			a.mov(dword_ptr(workspace,8*mem),val);
			a.bind(aux);
		}
	}break;
	case CMOV_IG_W_C+P_UINT48:
	case CMOV_IG_W_C+P_INT48:{
		uint8 mem=t.getNext8();
		Label l=a.newLabel();
		a.jne(l);
		if(mem<8){
			uint64 aux=t.getNext48().toInt();
			a.mov(rcx,0xFFFF000000000000);
			a.mov(rax,aux);
			a.and_(qreg[mem],rcx);
			a.add(qreg[mem],rax);
		}else {
			uint32 val1=t.getNext32();
			uint16 val2=t.getNext16();
			a.mov(dword_ptr(workspace,mem*8),val1);
			a.mov(word_ptr(workspace,(mem*8)+4),val2);
		}
		a.bind(l);
	}break;
	case CMOV_IG_W_C+P_UINT64:
	case CMOV_IG_W_C+P_INT64:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();
		if(mem<8){
			a.cmove(qreg[mem],val);
		}else{
			Label aux=a.newLabel();
			a.jne(aux);
			a.mov(qword_ptr(workspace,8*mem),val);
			a.bind(aux);
		}
	}break;
	case CMOV_IG_W_W+P_UINT8:
	case CMOV_IG_W_W+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				a.cmove(breg[mem],breg[val]);
			}else{
				a.mov(al,ptr(workspace,8*val));
				a.cmove(breg[mem],al);
			}
		}else{
			Label l=a.newLabel();
			a.jne(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),breg[val]);
			}else{
				a.mov(bl,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bl);
			}
			a.bind(l);
		}
	}break;
	case CMOV_IG_W_W+P_UINT16:
	case CMOV_IG_W_W+P_INT16:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				a.cmove(wreg[mem],wreg[val]);
			}else{
				a.mov(ax,ptr(workspace,8*val));
				a.cmove(wreg[mem],ax);
			}
		}else{
			Label l=a.newLabel();
			a.jne(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),wreg[val]);
			}else{
				a.mov(bx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_IG_W_W+P_UINT32:
	case CMOV_IG_W_W+P_INT32:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				a.cmove(dreg[mem],dreg[val]);
			}else{
				a.mov(eax,ptr(workspace,8*val));
				a.cmove(dreg[mem],eax);
			}
		}else{
			Label l=a.newLabel();
			a.jne(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),dreg[val]);
			}else{
				a.mov(ebx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),ebx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_IG_W_W+P_UINT48:
	case CMOV_IG_W_W+P_INT48:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		Label l=a.newLabel();
		a.jne(l);
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8){
			a.mov(rax,qreg[val]);
		}else{
			a.mov(rax,qword_ptr(workspace,val*8));
		}
		a.and_(rax,rcx);
	
		if(mem<8){
			a.not_(rcx);
			a.and_(qreg[mem],rcx);
			a.add(qreg[mem],rax);
		}else{
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.shr(rax,32);
			a.mov(word_ptr(workspace,(mem*8)+4),ax);
		}
		a.bind(l);
	}break;
	case CMOV_IG_W_W+P_UINT64:
	case CMOV_IG_W_W+P_INT64:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				a.cmove(qreg[mem],qreg[val]);
			}else{
				a.mov(rax,ptr(workspace,8*val));
				a.cmove(qreg[mem],rax);
			}
		}else{
			Label l=a.newLabel();
			a.jne(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),qreg[val]);
			}else{
				a.mov(rbx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),rbx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_DI_W_C+P_UINT8:
	case CMOV_DI_W_C+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			a.cmovne(breg[mem],val);
		}else{
			Label aux=a.newLabel();
			a.je(aux);
			a.mov(byte_ptr(workspace,8*mem),val);
			a.bind(aux);
		}
	}break;
	case CMOV_DI_W_C+P_UINT16:
	case CMOV_DI_W_C+P_INT16:{
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();
		if(mem<8){
			a.cmovne(wreg[mem],val);
		}else{
			Label aux=a.newLabel();
			a.je(aux);
			a.mov(word_ptr(workspace,8*mem),val);
			a.bind(aux);
		}
	}break;
	case CMOV_DI_W_C+P_UINT32:
	case CMOV_DI_W_C+P_INT32:{
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();
		if(mem<8){
			a.cmovne(dreg[mem],val);
		}else{
			Label aux=a.newLabel();
			a.je(aux);
			a.mov(dword_ptr(workspace,8*mem),val);
			a.bind(aux);
		}
	}break;
	case CMOV_DI_W_C+P_UINT48:
	case CMOV_DI_W_C+P_INT48:{
		uint8 mem=t.getNext8();
		Label l=a.newLabel();
		a.je(l);
		if(mem<8){
			uint64 aux=t.getNext48().toInt();
			a.mov(rax,aux);
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(rax,qreg[mem]);
			a.mov(qreg[mem],rax);
		}else {
			uint32 val1=t.getNext32();
			uint16 val2=t.getNext16();
			a.mov(dword_ptr(workspace,mem*8),val1);
			a.mov(word_ptr(workspace,(mem*8)+4),val2);
		}
		a.bind(l);
	}break;
	case CMOV_DI_W_C+P_UINT64:
	case CMOV_DI_W_C+P_INT64:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();
		if(mem<8){
			a.cmovne(qreg[mem],val);
		}else{
			Label aux=a.newLabel();
			a.je(aux);
			a.mov(qword_ptr(workspace,8*mem),val);
			a.bind(aux);
		}
	}break;
	case CMOV_DI_W_W+P_UINT8:
	case CMOV_DI_W_W+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				a.cmovne(breg[mem],breg[val]);
			}else{
				a.mov(al,ptr(workspace,8*val));
				a.cmovne(breg[mem],al);
			}
		}else{
			Label l=a.newLabel();
			a.je(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),breg[val]);
			}else{
				a.mov(bl,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bl);
			}
			a.bind(l);
		}
	}break;
	case CMOV_DI_W_W+P_UINT16:
	case CMOV_DI_W_W+P_INT16:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				a.cmovne(wreg[mem],wreg[val]);
			}else{
				a.mov(ax,ptr(workspace,8*val));
				a.cmovne(wreg[mem],ax);
			}
		}else{
			Label l=a.newLabel();
			a.je(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),wreg[val]);
			}else{
				a.mov(bx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_DI_W_W+P_UINT32:
	case CMOV_DI_W_W+P_INT32:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				a.cmovne(dreg[mem],dreg[val]);
			}else{
				a.mov(eax,ptr(workspace,8*val));
				a.cmovne(dreg[mem],eax);
			}
		}else{
			Label l=a.newLabel();
			a.je(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),dreg[val]);
			}else{
				a.mov(ebx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),ebx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_DI_W_W+P_UINT48:
	case CMOV_DI_W_W+P_INT48:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		Label l=a.newLabel();
		a.je(l);
		if(val<8){
			a.mov(rax,qreg[val]);
		}else{
			a.mov(rax,qword_ptr(workspace,val*8));
		}
		a.and_(rax,0x0000FFFFFFFFFFFF);
		if(mem<8){
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(qreg[mem],rax);
		}else{
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.shr(rax,32);
			a.mov(word_ptr(workspace,(mem*8)+4),ax);
		}
		a.bind(l);
	}break;
	case CMOV_DI_W_W+P_UINT64:
	case CMOV_DI_W_W+P_INT64:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				a.cmovne(qreg[mem],qreg[val]);
			}else{
				a.mov(rax,ptr(workspace,8*val));
				a.cmovne(qreg[mem],rax);
			}
		}else{
			Label l=a.newLabel();
			a.je(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),qreg[val]);
			}else{
				a.mov(rbx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),rbx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_MA_W_C+P_UINT8:
	case CMOV_MA_W_C+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(jcontent.type=='u')a.cmova(breg[mem],val);
			else a.cmovg(breg[mem],val);
		}else{
			a.mov(al,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmova(al,val);
			else a.cmovg(al,val);
			a.mov(ptr(workspace,8*mem),al);
		}
	}break;
	case CMOV_MA_W_C+P_UINT16:
	case CMOV_MA_W_C+P_INT16:{
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();
		if(mem<8){
			if(jcontent.type=='u')a.cmova(wreg[mem],val);
			else a.cmovg(wreg[mem],val);
		}else{
			a.mov(ax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmova(ax,val);
			else a.cmovg(ax,val);
			a.mov(ptr(workspace,8*mem),ax);
		}
	}break;
	case CMOV_MA_W_C+P_UINT32:
	case CMOV_MA_W_C+P_INT32:{
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();
		if(mem<8){
			if(jcontent.type=='u')a.cmova(dreg[mem],val);
			else a.cmovg(dreg[mem],val);
		}else{
			a.mov(eax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmova(eax,val);
			else a.cmovg(eax,val);
			a.mov(ptr(workspace,8*mem),eax);
		}
	}break;
	case CMOV_MA_W_C+P_UINT48:
	case CMOV_MA_W_C+P_INT48:{
		uint8 mem=t.getNext8();
		Label l=a.newLabel();
		if(jcontent.type=='u')a.jbe(l);
		else a.jle(l);
		if(mem<8){
			uint64 aux=t.getNext48().toInt();
			a.mov(rax,aux);
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(rax,qreg[mem]);
			a.mov(qreg[mem],rax);
		}else {
			uint32 val1=t.getNext32();
			uint16 val2=t.getNext16();
			a.mov(dword_ptr(workspace,mem*8),val1);
			a.mov(word_ptr(workspace,(mem*8)+4),val2);
		}
		a.bind(l);
	}break;
	case CMOV_MA_W_C+P_UINT64:
	case CMOV_MA_W_C+P_INT64:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();
		if(mem<8){
			if(jcontent.type=='u')a.cmova(qreg[mem],val);
			else a.cmovg(qreg[mem],val);
		}else{
			a.mov(rax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmova(rax,val);
			else a.cmovg(rax,val);
			a.mov(ptr(workspace,8*mem),rax);
		}
	}break;
	case CMOV_MA_W_W+P_UINT8:
	case CMOV_MA_W_W+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmova(breg[mem],breg[val]);
				else a.cmovg(breg[mem],breg[val]);
			}else{
				a.mov(al,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmova(breg[mem],al);
				else a.cmovg(breg[mem],al);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jbe(l);
			else a.jle(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),breg[val]);
			}else{
				a.mov(bl,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bl);
			}
			a.bind(l);
		}
	}break;
	case CMOV_MA_W_W+P_UINT16:
	case CMOV_MA_W_W+P_INT16:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmova(wreg[mem],wreg[val]);
				else a.cmovg(wreg[mem],wreg[val]);
			}else{
				a.mov(ax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmova(wreg[mem],ax);
				else a.cmovg(wreg[mem],ax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jbe(l);
			else a.jle(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),wreg[val]);
			}else{
				a.mov(bx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_MA_W_W+P_UINT32:
	case CMOV_MA_W_W+P_INT32:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmova(dreg[mem],dreg[val]);
				else a.cmovg(dreg[mem],dreg[val]);
			}else{
				a.mov(eax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmova(dreg[mem],eax);
				else a.cmovg(dreg[mem],eax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jbe(l);
			else a.jle(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),dreg[val]);
			}else{
				a.mov(ebx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),ebx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_MA_W_W+P_UINT48:
	case CMOV_MA_W_W+P_INT48:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		Label l=a.newLabel();
		if(jcontent.type=='u')a.jbe(l);
		else a.jle(l);
		if(val<8){
			a.mov(rax,qreg[val]);
		}else{
			a.mov(rax,qword_ptr(workspace,val*8));
		}
		a.and_(rax,0x0000FFFFFFFFFFFF);
	
		if(mem<8){
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(qreg[mem],rax);
		}else{
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.shr(rax,32);
			a.mov(word_ptr(workspace,(mem*8)+4),ax);
		}
		a.bind(l);
	}break;
	case CMOV_MA_W_W+P_UINT64:
	case CMOV_MA_W_W+P_INT64:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmova(qreg[mem],qreg[val]);
				else a.cmovg(qreg[mem],qreg[val]);
			}else{
				a.mov(rax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmova(qreg[mem],rax);
				else a.cmovg(qreg[mem],rax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jbe(l);
			else a.jle(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),qreg[val]);
			}else{
				a.mov(rbx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),rbx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_ME_W_C+P_UINT8:
	case CMOV_ME_W_C+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(jcontent.type=='u')a.cmovb(breg[mem],val);
			else a.cmovl(breg[mem],val);
		}else{
			a.mov(al,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovb(al,val);
			else a.cmovl(al,val);
			a.mov(ptr(workspace,8*mem),al);
		}
	}break;
	case CMOV_ME_W_C+P_UINT16:
	case CMOV_ME_W_C+P_INT16:{
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();
		if(mem<8){
			if(jcontent.type=='u')a.cmovb(wreg[mem],val);
			else a.cmovl(wreg[mem],val);
		}else{
			a.mov(ax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovb(ax,val);
			else a.cmovl(ax,val);
			a.mov(ptr(workspace,8*mem),ax);
		}
	}break;
	case CMOV_ME_W_C+P_UINT32:
	case CMOV_ME_W_C+P_INT32:{
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();
		if(mem<8){
			if(jcontent.type=='u')a.cmovb(dreg[mem],val);
			else a.cmovl(dreg[mem],val);
		}else{
			a.mov(eax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovb(eax,val);
			else a.cmovl(eax,val);
			a.mov(ptr(workspace,8*mem),eax);
		}
	}break;
	case CMOV_ME_W_C+P_UINT48:
	case CMOV_ME_W_C+P_INT48:{
		uint8 mem=t.getNext8();
		Label l=a.newLabel();
		if(jcontent.type=='u')a.jae(l);
		else a.jge(l);
		if(mem<8){
			uint64 aux=t.getNext48().toInt();
			a.mov(rax,aux);
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(rax,qreg[mem]);
			a.mov(qreg[mem],rax);
		}else {
			uint32 val1=t.getNext32();
			uint16 val2=t.getNext16();
			a.mov(dword_ptr(workspace,mem*8),val1);
			a.mov(word_ptr(workspace,(mem*8)+4),val2);
		}
		a.bind(l);
	}break;
	case CMOV_ME_W_C+P_UINT64:
	case CMOV_ME_W_C+P_INT64:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();
		if(mem<8){
			if(jcontent.type=='u')a.cmovb(qreg[mem],val);
			else a.cmovl(qreg[mem],val);
		}else{
			a.mov(rax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovb(rax,val);
			else a.cmovl(rax,val);
			a.mov(ptr(workspace,8*mem),rax);
		}
	}break;
	case CMOV_ME_W_W+P_UINT8:
	case CMOV_ME_W_W+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovb(breg[mem],breg[val]);
				else a.cmovl(breg[mem],breg[val]);
			}else{
				a.mov(al,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovb(breg[mem],al);
				else a.cmovl(breg[mem],al);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jae(l);
			else a.jge(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),breg[val]);
			}else{
				a.mov(bl,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bl);
			}
			a.bind(l);
		}
	}break;
	case CMOV_ME_W_W+P_UINT16:
	case CMOV_ME_W_W+P_INT16:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovb(wreg[mem],wreg[val]);
				else a.cmovl(wreg[mem],wreg[val]);
			}else{
				a.mov(ax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovb(wreg[mem],ax);
				else a.cmovl(wreg[mem],ax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jae(l);
			else a.jge(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),wreg[val]);
			}else{
				a.mov(bx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_ME_W_W+P_UINT32:
	case CMOV_ME_W_W+P_INT32:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovb(dreg[mem],dreg[val]);
				else a.cmovl(dreg[mem],dreg[val]);
			}else{
				a.mov(eax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovb(dreg[mem],eax);
				else a.cmovl(dreg[mem],eax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jae(l);
			else a.jge(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),dreg[val]);
			}else{
				a.mov(ebx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),ebx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_ME_W_W+P_UINT48:
	case CMOV_ME_W_W+P_INT48:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		Label l=a.newLabel();
		if(jcontent.type=='u')a.jae(l);
		else a.jge(l);
		if(val<8){
			a.mov(rax,qreg[val]);
		}else{
			a.mov(rax,qword_ptr(workspace,val*8));
		}
		a.and_(rax,0x0000FFFFFFFFFFFF);
	
		if(mem<8){
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(qreg[mem],rax);
		}else{
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.shr(rax,32);
			a.mov(word_ptr(workspace,(mem*8)+4),ax);
		}
		a.bind(l);
	}break;
	case CMOV_ME_W_W+P_UINT64:
	case CMOV_ME_W_W+P_INT64:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovb(qreg[mem],qreg[val]);
				else a.cmovl(qreg[mem],qreg[val]);
			}else{
				a.mov(rax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovb(qreg[mem],rax);
				else a.cmovl(qreg[mem],rax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jae(l);
			else a.jge(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),qreg[val]);
			}else{
				a.mov(rbx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),rbx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_ME_IG_W_C+P_UINT8:
	case CMOV_ME_IG_W_C+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(jcontent.type=='u')a.cmovbe(breg[mem],val);
			else a.cmovle(breg[mem],val);
		}else{
			a.mov(al,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovbe(al,val);
			else a.cmovle(al,val);
			a.mov(ptr(workspace,8*mem),al);
		}
	}break;
	case CMOV_ME_IG_W_C+P_UINT16:
	case CMOV_ME_IG_W_C+P_INT16:{
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();
		if(mem<8){
			if(jcontent.type=='u')a.cmovbe(wreg[mem],val);
			else a.cmovle(wreg[mem],val);
		}else{
			a.mov(ax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovbe(ax,val);
			else a.cmovle(ax,val);
			a.mov(ptr(workspace,8*mem),ax);
		}
	}break;
	case CMOV_ME_IG_W_C+P_UINT32:
	case CMOV_ME_IG_W_C+P_INT32:{
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();
		if(mem<8){
			if(jcontent.type=='u')a.cmovbe(dreg[mem],val);
			else a.cmovle(dreg[mem],val);
		}else{
			a.mov(eax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovbe(eax,val);
			else a.cmovle(eax,val);
			a.mov(ptr(workspace,8*mem),eax);
		}
	}break;
	case CMOV_ME_IG_W_C+P_UINT48:
	case CMOV_ME_IG_W_C+P_INT48:{
		uint8 mem=t.getNext8();
		Label l=a.newLabel();
		if(jcontent.type=='u')a.ja(l);
		else a.jg(l);
		if(mem<8){
			uint64 aux=t.getNext48().toInt();
			a.mov(rax,aux);
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(rax,qreg[mem]);
			a.mov(qreg[mem],rax);
		}else {
			uint32 val1=t.getNext32();
			uint16 val2=t.getNext16();
			a.mov(dword_ptr(workspace,mem*8),val1);
			a.mov(word_ptr(workspace,(mem*8)+4),val2);
		}
		a.bind(l);
	}break;
	case CMOV_ME_IG_W_C+P_UINT64:
	case CMOV_ME_IG_W_C+P_INT64:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();
		if(mem<8){
			if(jcontent.type=='u')a.cmovbe(qreg[mem],val);
			else a.cmovle(qreg[mem],val);
		}else{
			a.mov(rax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovbe(rax,val);
			else a.cmovle(rax,val);
			a.mov(ptr(workspace,8*mem),rax);
		}
	}break;
	case CMOV_ME_IG_W_W+P_UINT8:
	case CMOV_ME_IG_W_W+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovbe(breg[mem],breg[val]);
				else a.cmovle(breg[mem],breg[val]);
			}else{
				a.mov(al,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovbe(breg[mem],al);
				else a.cmovle(breg[mem],al);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.ja(l);
			else a.jg(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),breg[val]);
			}else{
				a.mov(bl,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bl);
			}
			a.bind(l);
		}
	}break;
	case CMOV_ME_IG_W_W+P_UINT16:
	case CMOV_ME_IG_W_W+P_INT16:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovbe(wreg[mem],wreg[val]);
				else a.cmovle(wreg[mem],wreg[val]);
			}else{
				a.mov(ax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovbe(wreg[mem],ax);
				else a.cmovle(wreg[mem],ax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.ja(l);
			else a.jg(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),wreg[val]);
			}else{
				a.mov(bx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_ME_IG_W_W+P_UINT32:
	case CMOV_ME_IG_W_W+P_INT32:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovbe(dreg[mem],dreg[val]);
				else a.cmovle(dreg[mem],dreg[val]);
			}else{
				a.mov(eax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovbe(dreg[mem],eax);
				else a.cmovle(dreg[mem],eax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.ja(l);
			else a.jg(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),dreg[val]);
			}else{
				a.mov(ebx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),ebx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_ME_IG_W_W+P_UINT48:
	case CMOV_ME_IG_W_W+P_INT48:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		Label l=a.newLabel();
		if(jcontent.type=='u')a.ja(l);
		else a.jg(l);
		if(val<8){
			a.mov(rax,qreg[val]);
		}else{
			a.mov(rax,qword_ptr(workspace,val*8));
		}
		a.and_(rax,0x0000FFFFFFFFFFFF);
	
		if(mem<8){
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(qreg[mem],rax);
		}else{
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.shr(rax,32);
			a.mov(word_ptr(workspace,(mem*8)+4),ax);
		}
		a.bind(l);
	}break;
	case CMOV_ME_IG_W_W+P_UINT64:
	case CMOV_ME_IG_W_W+P_INT64:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovbe(qreg[mem],qreg[val]);
				else a.cmovle(qreg[mem],qreg[val]);
			}else{
				a.mov(rax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovbe(qreg[mem],rax);
				else a.cmovle(qreg[mem],rax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.ja(l);
			else a.jg(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),qreg[val]);
			}else{
				a.mov(rbx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),rbx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_MA_IG_W_C+P_UINT8:
	case CMOV_MA_IG_W_C+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(jcontent.type=='u')a.cmovae(breg[mem],val);
			else a.cmovge(breg[mem],val);
		}else{
			a.mov(al,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovae(al,val);
			else a.cmovge(al,val);
			a.mov(ptr(workspace,8*mem),al);
		}
	}break;
	case CMOV_MA_IG_W_C+P_UINT16:
	case CMOV_MA_IG_W_C+P_INT16:{
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();
		if(mem<8){
			if(jcontent.type=='u')a.cmovae(wreg[mem],val);
			else a.cmovge(wreg[mem],val);
		}else{
			a.mov(ax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovae(ax,val);
			else a.cmovge(ax,val);
			a.mov(ptr(workspace,8*mem),ax);
		}
	}break;
	case CMOV_MA_IG_W_C+P_UINT32:
	case CMOV_MA_IG_W_C+P_INT32:{
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();
		if(mem<8){
			if(jcontent.type=='u')a.cmovae(dreg[mem],val);
			else a.cmovge(dreg[mem],val);
		}else{
			a.mov(eax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovae(eax,val);
			else a.cmovge(eax,val);
			a.mov(ptr(workspace,8*mem),eax);
		}
	}break;
	case CMOV_MA_IG_W_C+P_UINT48:
	case CMOV_MA_IG_W_C+P_INT48:{
		uint8 mem=t.getNext8();
		Label l=a.newLabel();
		if(jcontent.type=='u')a.jb(l);
		else a.jl(l);
		if(mem<8){
			uint64 aux=t.getNext48().toInt();
			a.mov(rax,aux);
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(rax,qreg[mem]);
			a.mov(qreg[mem],rax);
		}else {
			uint32 val1=t.getNext32();
			uint16 val2=t.getNext16();
			a.mov(dword_ptr(workspace,mem*8),val1);
			a.mov(word_ptr(workspace,(mem*8)+4),val2);
		}
		a.bind(l);
	}break;
	case CMOV_MA_IG_W_C+P_UINT64:
	case CMOV_MA_IG_W_C+P_INT64:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();
		if(mem<8){
			if(jcontent.type=='u')a.cmovae(qreg[mem],val);
			else a.cmovge(qreg[mem],val);
		}else{
			a.mov(rax,byte_ptr(workspace,8*mem));
			if(jcontent.type=='u')a.cmovae(rax,val);
			else a.cmovge(rax,val);
			a.mov(ptr(workspace,8*mem),rax);
		}
	}break;
	case CMOV_MA_IG_W_W+P_UINT8:
	case CMOV_MA_IG_W_W+P_INT8:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovae(breg[mem],breg[val]);
				else a.cmovge(breg[mem],breg[val]);
			}else{
				a.mov(al,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovae(breg[mem],al);
				else a.cmovge(breg[mem],al);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jb(l);
			else a.jl(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),breg[val]);
			}else{
				a.mov(bl,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bl);
			}
			a.bind(l);
		}
	}break;
	case CMOV_MA_IG_W_W+P_UINT16:
	case CMOV_MA_IG_W_W+P_INT16:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovae(wreg[mem],wreg[val]);
				else a.cmovge(wreg[mem],wreg[val]);
			}else{
				a.mov(ax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovae(wreg[mem],ax);
				else a.cmovge(wreg[mem],ax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jb(l);
			else a.jl(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),wreg[val]);
			}else{
				a.mov(bx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),bx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_MA_IG_W_W+P_UINT32:
	case CMOV_MA_IG_W_W+P_INT32:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovae(dreg[mem],dreg[val]);
				else a.cmovge(dreg[mem],dreg[val]);
			}else{
				a.mov(eax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovae(dreg[mem],eax);
				else a.cmovge(dreg[mem],eax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jb(l);
			else a.jl(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),dreg[val]);
			}else{
				a.mov(ebx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),ebx);
			}
			a.bind(l);
		}
	}break;
	case CMOV_MA_IG_W_W+P_UINT48:
	case CMOV_MA_IG_W_W+P_INT48:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		Label l=a.newLabel();
		if(jcontent.type=='u')a.jb(l);
		else a.jl(l);
		if(val<8){
			a.mov(rax,qreg[val]);
		}else{
			a.mov(rax,qword_ptr(workspace,val*8));
		}
		a.and_(rax,0x0000FFFFFFFFFFFF);
	
		if(mem<8){
			a.and_(qreg[mem],0xFFFF000000000000);
			a.add(qreg[mem],rax);
		}else{
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.shr(rax,32);
			a.mov(word_ptr(workspace,(mem*8)+4),ax);
		}
		a.bind(l);
	}break;
	case CMOV_MA_IG_W_W+P_UINT64:
	case CMOV_MA_IG_W_W+P_INT64:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8){
			if(val<8){
				if(jcontent.type=='u')a.cmovae(qreg[mem],qreg[val]);
				else a.cmovge(qreg[mem],qreg[val]);
			}else{
				a.mov(rax,ptr(workspace,8*val));
				if(jcontent.type=='u')a.cmovae(qreg[mem],rax);
				else a.cmovge(qreg[mem],rax);
			}
		}else{
			Label l=a.newLabel();
			if(jcontent.type=='u')a.jb(l);
			else a.jl(l);
			if(val<8){
				a.mov(ptr(workspace,8*mem),qreg[val]);
			}else{
				a.mov(rbx,ptr(workspace,8*val));
				a.mov(ptr(workspace,8*mem),rbx);
			}
			a.bind(l);
		}
	}break;
	default:
		return 0;
	}
	return 1;
}
