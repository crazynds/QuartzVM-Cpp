/*
 * mov.cpp
 *
 *  Created on: 9 de mai de 2019
 *      Author: lhlag
 */

#include "../Jit.h"

uint8 mov(uint16 p,Thread &t, Assembler &a, uint8 &type, Label &end,  uint32 maxCode, uint32 minCode,std::vector<Dupla<Label,uint32>> &v){
	Gp memory=rdi;
	Gp workspace=rsi;

	Gp qreg[8];qreg[0]=r8;qreg[1]=r9;qreg[2]=r10;qreg[3]=r11;qreg[4]=r12;qreg[5]=r13;qreg[6]=r14;qreg[7]=r15;
	Gp dreg[8];dreg[0]=r8d;dreg[1]=r9d;dreg[2]=r10d;dreg[3]=r11d;dreg[4]=r12d;dreg[5]=r13d;dreg[6]=r14d;dreg[7]=r15d;
	Gp wreg[8];wreg[0]=r8w;wreg[1]=r9w;wreg[2]=r10w;wreg[3]=r11w;wreg[4]=r12w;wreg[5]=r13w;wreg[6]=r14w;wreg[7]=r15w;
	Gp breg[8];breg[0]=r8b;breg[1]=r9b;breg[2]=r10b;breg[3]=r11b;breg[4]=r12b;breg[5]=r13b;breg[6]=r14b;breg[7]=r15b;

	switch(p){
	case P_UINT8+MOV_MMWW_C:
	case P_INT8+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(rax,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(qreg[base1],rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}else{
			a.mov(rax,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(rax,ptr(rax,qreg[index1],shift1,inc1));
			}else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(rax,rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}
		a.and_(rax,rcx);
		a.mov(byte_ptr(memory,rax),val);

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rax=LIXO_REG;
	}break;
	case P_UINT16+MOV_MMWW_C:
	case P_INT16+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint16 val=t.getNext16();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(rax,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(qreg[base1],rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}else{
			a.mov(rax,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(rax,ptr(rax,qreg[index1],shift1,inc1));
			}else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(rax,rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}
		a.and_(rax,rcx);
		a.mov(word_ptr(memory,rax),val);

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rax=LIXO_REG;
	}break;
	case P_UINT32+MOV_MMWW_C:
	case P_INT32+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint32 val=t.getNext32();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(rax,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(qreg[base1],rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}else{
			a.mov(rax,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(rax,ptr(rax,qreg[index1],shift1,inc1));
			}else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(rax,rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}
		a.and_(rax,rcx);
		a.mov(dword_ptr(memory,rax),val);

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rax=LIXO_REG;
	}break;
	case P_UINT48+MOV_MMWW_C:
	case P_INT48+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint32 val=t.getNext32();
		uint16 val2=t.getNext16();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(rax,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(qreg[base1],rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}else{
			a.mov(rax,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(rax,ptr(rax,qreg[index1],shift1,inc1));
			}else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(rax,rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}
		a.and_(rax,rcx);
		a.mov(dword_ptr(memory,rax),val);
		a.mov(word_ptr(memory,rax,0,2),val2);

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rax=LIXO_REG;
	}break;
	case P_UINT64+MOV_MMWW_C:
	case P_INT64+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint64 val=t.getNext64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(rax,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(qreg[base1],rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}else{
			a.mov(rax,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(rax,ptr(rax,qreg[index1],shift1,inc1));
			}else{
				a.mov(rbx,ptr(workspace,index1*8));
				a.lea(rax,ptr(rax,rbx,shift1,inc1));
				val_rbx=LIXO_REG;
			}
		}
		a.and_(rax,rcx);
		a.mov(qword_ptr(memory,rax),val);

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rax=LIXO_REG;
	}break;
	case P_UINT8+MOV_MMW_W:
	case P_INT8+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(rbx,qreg[dst]);
		else a.mov(rbx,qword_ptr(workspace,dst*8));
		a.and_(rbx,rcx);
		if(val<8)a.mov(ptr(memory,rbx,0,valinc),breg[val]);
		else{
			a.mov(al,ptr(workspace,val*8));
			a.mov(ptr(memory,rbx,0,valinc),al);
			val_rax=LIXO_REG;
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT16+MOV_MMW_W:
	case P_INT16+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(rbx,qreg[dst]);
		else a.mov(rbx,qword_ptr(workspace,dst*8));
		a.and_(rbx,rcx);
		if(val<8)a.mov(ptr(memory,rbx,0,valinc),wreg[val]);
		else{
			a.mov(ax,ptr(workspace,val*8));
			a.mov(ptr(memory,rbx,0,valinc),ax);
			val_rax=LIXO_REG;
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT32+MOV_MMW_W:
	case P_INT32+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(rbx,qreg[dst]);
		else a.mov(rbx,qword_ptr(workspace,dst*8));
		a.and_(rbx,rcx);
		if(val<8)a.mov(ptr(memory,rbx,0,valinc),dreg[val]);
		else{
			a.mov(eax,ptr(workspace,val*8));
			a.mov(ptr(memory,rbx,0,valinc),eax);
			val_rax=LIXO_REG;
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT48+MOV_MMW_W:
	case P_INT48+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(rbx,qreg[dst]);
		else a.mov(rbx,qword_ptr(workspace,dst*8));
		a.and_(rbx,rcx);
		if(val<8){
			a.mov(rax,qreg[val]);
			a.mov(ptr(memory,rbx,0,valinc),eax);
			a.shr(rax,32);
			a.mov(ptr(memory,rbx,0,valinc+4),ax);
		}else{
			a.mov(rax,ptr(workspace,val*8));
			a.mov(ptr(memory,rbx,0,valinc),eax);
			a.shr(rax,32);
			a.mov(ptr(memory,rbx,0,valinc),ax);
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT64+MOV_MMW_W:
	case P_INT64+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(rbx,qreg[dst]);
		else a.mov(rbx,qword_ptr(workspace,dst*8));
		a.and_(rbx,rcx);
		if(val<8)a.mov(ptr(memory,rbx,0,valinc),qreg[val]);
		else{
			a.mov(rax,ptr(workspace,val*8));
			a.mov(ptr(memory,rbx,0,valinc),rax);
			val_rax=LIXO_REG;
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT8+MOV_W_MMW:
	case P_INT8+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val*8));
		a.and_(rbx,rcx);
		if(dst<8)a.mov(breg[dst],ptr(memory,rbx,0,valinc));
		else{
			a.mov(al,ptr(memory,rbx,0,valinc));
			a.mov(ptr(workspace,dst*8),al);
			val_rax=LIXO_REG;
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT16+MOV_W_MMW:
	case P_INT16+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val*8));
		a.and_(rbx,rcx);
		if(dst<8)a.mov(wreg[dst],ptr(memory,rbx,0,valinc));
		else{
			a.mov(ax,ptr(memory,rbx,0,valinc));
			a.mov(ptr(workspace,dst*8),ax);
			val_rax=LIXO_REG;
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT32+MOV_W_MMW:
	case P_INT32+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val*8));
		a.and_(rbx,rcx);
		if(dst<8)a.mov(dreg[dst],ptr(memory,rbx,0,valinc));
		else{
			a.mov(eax,ptr(memory,rbx,0,valinc));
			a.mov(ptr(workspace,dst*8),eax);
			val_rax=LIXO_REG;
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT48+MOV_W_MMW:
	case P_INT48+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val*8));
		a.and_(rbx,rcx);
		if(dst<8){
			a.mov(eax,ptr(memory,rbx,0,valinc+2));
			a.shl(rax,32);
			a.mov(ax,ptr(memory,rbx,0,valinc));
			a.not_(rcx);
			a.and_(qreg[dst],rcx);
			a.or_(qreg[dst],rax);
		}else{
			a.mov(rax,ptr(memory,rbx,0,valinc));
			a.mov(ptr(workspace,dst*8),eax);
			a.shr(rax,32);
			a.mov(ptr(workspace,dst*8+4),ax);
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT64+MOV_W_MMW:
	case P_INT64+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val*8));
		a.and_(rbx,rcx);
		if(dst<8)a.mov(qreg[dst],ptr(memory,rbx,0,valinc));
		else{
			a.mov(rax,ptr(memory,rbx,0,valinc));
			a.mov(ptr(workspace,dst*8),rax);
		}

		val_rcx=0x0000FFFFFFFFFFFF;
		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
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
		a.mov(qword_ptr(memory,mem),val);
	}break;
	case P_UINT8+MOV_W_C:
	case P_INT8+MOV_W_C:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(mem<8) a.mov(breg[mem],val);
		else a.mov(byte_ptr(workspace,mem*8),val);
	}break;
	case P_UINT16+MOV_W_C:
	case P_INT16+MOV_W_C:{
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();
		if(mem<8) a.mov(wreg[mem],val);
		else a.mov(word_ptr(workspace,mem*8),val);
	}break;
	case P_UINT32+MOV_W_C:
	case P_INT32+MOV_W_C:{
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();
		if(mem<8) a.mov(dreg[mem],val);
		else a.mov(dword_ptr(workspace,mem*8),val);
	}break;
	case P_UINT48+MOV_W_C:
	case P_INT48+MOV_W_C:{
		uint8 mem=t.getNext8();
		if(mem<8){
			uint64 aux=t.getNext48().toInt();
			a.mov(rcx,0x0000FFFFFFFFFFFF);
			a.mov(rax,aux);
			a.andn(qreg[mem],rcx,qreg[mem]);
			a.add(qreg[mem],rax);

			val_rcx=0x0000FFFFFFFFFFFF;
			val_rax=LIXO_REG;
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
		if(mem<8) a.mov(qreg[mem],val);
		else a.mov(qword_ptr(workspace,mem*8),val);
	}break;
	case P_UINT8+MOV_W_W:
	case P_INT8+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8) {
			if(mem<8)a.mov(breg[mem],breg[val]);
			else a.mov(ptr(workspace,mem*8),breg[val]);
		}else{
			if(mem<8)a.mov(breg[mem],ptr(workspace,val*8));
			else{
				a.mov(al,byte_ptr(workspace,val*8));
				a.mov(byte_ptr(workspace,mem*8),al);
				val_rax=LIXO_REG;
			}
		}
	}break;
	case P_UINT16+MOV_W_W:
	case P_INT16+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8) {
			if(mem<8)a.mov(wreg[mem],wreg[val]);
			else a.mov(ptr(workspace,mem*8),wreg[val]);
		}else{
			if(mem<8)a.mov(wreg[mem],ptr(workspace,val*8));
			else{
				a.mov(ax,byte_ptr(workspace,val*8));
				a.mov(byte_ptr(workspace,mem*8),ax);
				val_rax=LIXO_REG;
			}
		}
	}break;
	case P_UINT32+MOV_W_W:
	case P_INT32+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8) {
			if(mem<8)a.mov(dreg[mem],dreg[val]);
			else a.mov(ptr(workspace,mem*8),dreg[val]);
		}else{
			if(mem<8)a.mov(dreg[mem],ptr(workspace,val*8));
			else{
				a.mov(eax,byte_ptr(workspace,val*8));
				a.mov(byte_ptr(workspace,mem*8),eax);
				val_rax=LIXO_REG;
			}
		}
	}break;
	case P_UINT48+MOV_W_W:
	case P_INT48+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8){
			a.mov(rax,qreg[val]);
		}else{
			a.mov(rax,qword_ptr(workspace,val*8));
		}
		a.and_(rax,rcx);
		if(mem<8){
			a.andn(qreg[mem],rcx,qreg[mem]);
			a.add(qreg[mem],rax);
		}else{
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.shr(rax,32);
			a.mov(word_ptr(workspace,(mem*8)+4),ax);
		}
		val_rax=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT64+MOV_W_W:
	case P_INT64+MOV_W_W:{
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();
		if(val<8) {
			if(mem<8)a.mov(qreg[mem],qreg[val]);
			else a.mov(ptr(workspace,mem*8),qreg[val]);
		}else{
			if(mem<8)a.mov(qreg[mem],ptr(workspace,val*8));
			else{
				a.mov(rax,byte_ptr(workspace,val*8));
				a.mov(byte_ptr(workspace,mem*8),rax);
				val_rax=LIXO_REG;
			}
		}
	}break;
	case P_UINT8+MOV_W_M:
	case P_INT8+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8)a.mov(breg[mem],byte_ptr(memory,val));
		else{
			a.mov(al,byte_ptr(memory,val));
			a.mov(byte_ptr(workspace,mem*8),al);
			val_rax=LIXO_REG;
		}
	}break;
	case P_UINT16+MOV_W_M:
	case P_INT16+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8)a.mov(wreg[mem],word_ptr(memory,val));
		else{
			a.mov(ax,word_ptr(memory,val));
			a.mov(word_ptr(workspace,mem*8),ax);
			val_rax=LIXO_REG;
		}
	}break;
	case P_UINT32+MOV_W_M:
	case P_INT32+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8)a.mov(dreg[mem],dword_ptr(memory,val));
		else{
			a.mov(eax,dword_ptr(memory,val));
			a.mov(dword_ptr(workspace,mem*8),eax);
			val_rax=LIXO_REG;
		}
	}break;
	case P_UINT48+MOV_W_M:
	case P_INT48+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8){
			//OPTIMIZATION - Incluido um sistema de economia de 2 clocks
			a.xor_(rax,rax);
			a.xor_(rbx,rbx);
			a.mov(eax,dword_ptr(memory,val));
			a.mov(bx,word_ptr(memory,val+4));
			//
			a.and_(qreg[mem],0xFFFF000000000000);
			a.shl(rbx,32);
			a.add(rax,rbx);
			a.add(qreg[mem],rax);
		}else {
			//Necessário para optimização acima
			a.mov(eax,dword_ptr(memory,val));
			a.mov(bx,word_ptr(memory,val+4));
			//
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.mov(word_ptr(workspace,(mem*8)+4),bx);
		}
		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT64+MOV_W_M:
	case P_INT64+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8)a.mov(qreg[mem],qword_ptr(memory,val));
		else{
			a.mov(rax,qword_ptr(memory,val));
			a.mov(qword_ptr(workspace,mem*8),rax);
			val_rax=LIXO_REG;
		}
	}break;
	case P_UINT8+MOV_M_W:
	case P_INT8+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8)a.mov(byte_ptr(memory,mem),breg[val]);
		else{
			a.mov(al,byte_ptr(workspace,val*8));
			a.mov(byte_ptr(memory,mem),al);
			val_rax=LIXO_REG;
		}
	}break;
	case P_UINT16+MOV_M_W:
	case P_INT16+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8)a.mov(word_ptr(memory,mem),wreg[val]);
		else{
			a.mov(ax,word_ptr(workspace,val*8));
			a.mov(word_ptr(memory,mem),ax);
			val_rax=LIXO_REG;
		}
	}break;
	case P_UINT32+MOV_M_W:
	case P_INT32+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8)a.mov(dword_ptr(memory,mem),dreg[val]);
		else{
			a.mov(eax,dword_ptr(workspace,val*8));
			a.mov(dword_ptr(memory,mem),eax);
			val_rax=LIXO_REG;
		}
	}break;
	case P_UINT48+MOV_M_W:
	case P_INT48+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8){
			a.mov(rbx,qreg[val]);
			a.mov(eax,ebx);
			a.shr(rbx,32);
			a.mov(dx,bx);
			val_rbx=LIXO_REG;
		}else{
			a.mov(eax,dword_ptr(workspace,val*8));
			a.mov(dx,word_ptr(workspace,(val*8)+4));
		}
		a.mov(dword_ptr(memory,mem),eax);
		a.mov(word_ptr(memory,mem+4),dx);

		val_rax=LIXO_REG;
		val_rdx=LIXO_REG;
	}break;
	case P_UINT64+MOV_M_W:
	case P_INT64+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8)a.mov(qword_ptr(memory,mem),qreg[val]);
		else{
			a.mov(rax,qword_ptr(workspace,val*8));
			a.mov(qword_ptr(memory,mem),rax);
			val_rax=LIXO_REG;
		}
	}break;
	case P_UINT8+MOV_M_M:
	case P_INT8+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		a.mov(al,byte_ptr(memory,val));
		a.mov(byte_ptr(memory,mem),al);
		val_rax=LIXO_REG;
	}break;
	case P_UINT16+MOV_M_M:
	case P_INT16+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		a.mov(ax,word_ptr(memory,val));
		a.mov(word_ptr(memory,mem),ax);
		val_rax=LIXO_REG;
	}break;
	case P_UINT32+MOV_M_M:
	case P_INT32+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		a.mov(eax,dword_ptr(memory,val));
		a.mov(dword_ptr(memory,mem),eax);
		val_rax=LIXO_REG;
	}break;
	case P_UINT48+MOV_M_M:
	case P_INT48+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();


		a.mov(eax,dword_ptr(memory,val));
		a.mov(bx,word_ptr(memory,val+4));

		a.mov(dword_ptr(memory,mem),eax);
		a.mov(word_ptr(memory,mem+4),bx);
		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
	}break;
	case P_UINT64+MOV_M_M:
	case P_INT64+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		a.mov(rax,qword_ptr(memory,val));
		a.mov(qword_ptr(memory,mem),rax);
		val_rax=LIXO_REG;
	}break;
	case P_UINT8+MOV_MMW_M:
	case P_INT8+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();


		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.mov(al,byte_ptr(memory,val));
		a.and_(rbx,rcx);

		a.mov(byte_ptr(memory,rbx,0,inc),al);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT16+MOV_MMW_M:
	case P_INT16+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();


		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.mov(ax,word_ptr(memory,val));
		a.and_(rbx,rcx);

		a.mov(word_ptr(memory,rbx,0,inc),ax);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT32+MOV_MMW_M:
	case P_INT32+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.mov(eax,dword_ptr(memory,val));
		a.and_(rbx,rcx);
		a.mov(dword_ptr(memory,rbx,0,inc),eax);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT48+MOV_MMW_M:
	case P_INT48+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.mov(eax,dword_ptr(memory,val));
		a.mov(dx,word_ptr(memory,val+4));
		a.and_(rbx,rcx);

		a.mov(dword_ptr(memory,rbx,0,inc),eax);
		a.add(rbx,4);
		a.mov(word_ptr(memory,rbx,0,inc),dx);


		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rdx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT64+MOV_MMW_M:
	case P_INT64+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.mov(rax,qword_ptr(memory,val));
		a.and_(rbx,rcx);
		a.mov(qword_ptr(memory,rbx,0,inc),rax);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT8+MOV_M_MMW:
	case P_INT8+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val));
		a.and_(rbx,rcx);
		a.mov(al,byte_ptr(memory,rbx,0,inc));
		a.mov(byte_ptr(memory,mem),al);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT16+MOV_M_MMW:
	case P_INT16+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val));
		a.and_(rbx,rcx);
		a.mov(ax,word_ptr(memory,rbx,0,inc));
		a.mov(word_ptr(memory,mem),ax);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT32+MOV_M_MMW:
	case P_INT32+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val));
		a.and_(rbx,rcx);
		a.mov(eax,dword_ptr(memory,rbx,0,inc));
		a.mov(dword_ptr(memory,mem),eax);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT48+MOV_M_MMW:
	case P_INT48+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val));
		a.and_(rbx,rcx);
		a.mov(eax,dword_ptr(memory,rbx,0,inc));
		a.add(rbx,4);
		a.mov(dx,word_ptr(memory,rbx,0,inc));
		a.mov(dword_ptr(memory,mem),eax);
		a.mov(word_ptr(memory,mem+4),dx);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rdx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT64+MOV_M_MMW:
	case P_INT64+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(rbx,qreg[val]);
		else a.mov(rbx,qword_ptr(workspace,val));
		a.and_(rbx,rcx);
		a.mov(rax,qword_ptr(memory,rbx,0,inc));
		a.mov(qword_ptr(memory,mem),rax);

		val_rax=LIXO_REG;
		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT8+MOV_MMW_C:
	case P_INT8+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.and_(rbx,rcx);
		a.mov(byte_ptr(memory,rbx,0,inc),val);

		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT16+MOV_MMW_C:
	case P_INT16+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.and_(rbx,rcx);
		a.mov(word_ptr(memory,rbx,0,inc),val);

		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT32+MOV_MMW_C:
	case P_INT32+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.and_(rbx,rcx);
		a.mov(dword_ptr(memory,rbx,0,inc),val);

		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT48+MOV_MMW_C:
	case P_INT48+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint32 val1=t.getNext32();
		uint16 val2=t.getNext16();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.and_(rbx,rcx);
		a.mov(dword_ptr(memory,rbx,0,inc),val1);
		a.add(rbx,4);
		a.mov(word_ptr(memory,rbx,0,inc),val2);

		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	case P_UINT64+MOV_MMW_C:
	case P_INT64+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(rbx,qreg[mem]);
		else a.mov(rbx,qword_ptr(workspace,mem*8));
		a.and_(rbx,rcx);
		a.mov(qword_ptr(memory,rbx,0,inc),val);

		val_rbx=LIXO_REG;
		val_rcx=0x0000FFFFFFFFFFFF;
	}break;
	default:
		return 0;
	}
	return 1;
}

