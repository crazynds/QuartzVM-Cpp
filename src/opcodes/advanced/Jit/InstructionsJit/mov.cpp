/*
 * mov.cpp
 *
 *  Created on: 9 de mai de 2019
 *      Author: lhlag
 */

#include "../Jit.h"

uint8 mov(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v){
	Gp memory=rdi;
	Gp workspace=rsi;

	Gp qreg[8];qreg[0]=r8;qreg[1]=r9;qreg[2]=r10;qreg[3]=r11;qreg[4]=r12;qreg[5]=r13;qreg[6]=r14;qreg[7]=r15;
	Gp dreg[8];dreg[0]=r8d;dreg[1]=r9d;dreg[2]=r10d;dreg[3]=r11d;dreg[4]=r12d;dreg[5]=r13d;dreg[6]=r14d;dreg[7]=r15d;
	Gp wreg[8];wreg[0]=r8w;wreg[1]=r9w;wreg[2]=r10w;wreg[3]=r11w;wreg[4]=r12w;wreg[5]=r13w;wreg[6]=r14w;wreg[7]=r15w;
	Gp breg[8];breg[0]=r8b;breg[1]=r9b;breg[2]=r10b;breg[3]=r11b;breg[4]=r12b;breg[5]=r13b;breg[6]=r14b;breg[7]=r15b;

	switch(jcontent.opcode){
	case P_UINT8+MOV_MMWW_C:
	case P_INT8+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint8 val=t.getNext8();

		Gp reg1_aux64=a.getNextRegister64();
		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(reg1_aux64,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(qreg[base1],reg2_aux64,shift1,inc1));
			}
		}else{
			a.mov(reg1_aux64,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(reg1_aux64,ptr(reg1_aux64,qreg[index1],shift1,inc1));
			}else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(reg1_aux64,reg2_aux64,shift1,inc1));
			}
		}
		a.and_(reg1_aux64,rcx);
		a.mov(byte_ptr(memory,reg1_aux64),val);

	}break;
	case P_UINT16+MOV_MMWW_C:
	case P_INT16+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint16 val=t.getNext16();

		Gp reg1_aux64=a.getNextRegister64();
		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(reg1_aux64,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(qreg[base1],reg2_aux64,shift1,inc1));
			}
		}else{
			a.mov(reg1_aux64,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(reg1_aux64,ptr(reg1_aux64,qreg[index1],shift1,inc1));
			}else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(reg1_aux64,reg2_aux64,shift1,inc1));
			}
		}
		a.and_(reg1_aux64,rcx);
		a.mov(word_ptr(memory,reg1_aux64),val);
	}break;
	case P_UINT32+MOV_MMWW_C:
	case P_INT32+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint32 val=t.getNext32();
		Gp reg1_aux64=a.getNextRegister64();
		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(reg1_aux64,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(qreg[base1],reg2_aux64,shift1,inc1));
			}
		}else{
			a.mov(reg1_aux64,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(reg1_aux64,ptr(reg1_aux64,qreg[index1],shift1,inc1));
			}else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(reg1_aux64,reg2_aux64,shift1,inc1));
			}
		}
		a.and_(reg1_aux64,rcx);
		a.mov(dword_ptr(memory,reg1_aux64),val);
	}break;
	case P_UINT48+MOV_MMWW_C:
	case P_INT48+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint32 val=t.getNext32();
		uint16 val2=t.getNext16();
		Gp reg1_aux64=a.getNextRegister64();
		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(reg1_aux64,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(qreg[base1],reg2_aux64,shift1,inc1));
			}
		}else{
			a.mov(reg1_aux64,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(reg1_aux64,ptr(reg1_aux64,qreg[index1],shift1,inc1));
			}else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(reg1_aux64,reg2_aux64,shift1,inc1));
			}
		}
		a.and_(reg1_aux64,rcx);
		a.mov(dword_ptr(memory,reg1_aux64),val);
		a.mov(word_ptr(memory,reg1_aux64,0,4),val2);
	}break;
	case P_UINT64+MOV_MMWW_C:
	case P_INT64+MOV_MMWW_C:{
		uint32 inc1=t.getNext32();
		uint8 base1=t.getNext8();
		uint8 index1=t.getNext8();
		uint8 shift1=t.getNext8();

		uint64 val=t.getNext64();
		Gp reg1_aux64=a.getNextRegister64();
		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(base1<8){
			if(index1<8)a.lea(reg1_aux64,ptr(qreg[base1],qreg[index1],shift1,inc1));
			else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(qreg[base1],reg2_aux64,shift1,inc1));
			}
		}else{
			a.mov(reg1_aux64,ptr(workspace,base1*8));
			if(index1<8){
				a.lea(reg1_aux64,ptr(reg1_aux64,qreg[index1],shift1,inc1));
			}else{
				a.mov(reg2_aux64,ptr(workspace,index1*8));
				a.lea(reg1_aux64,ptr(reg1_aux64,reg2_aux64,shift1,inc1));
			}
		}
		a.and_(reg1_aux64,rcx);
		a.mov(qword_ptr(memory,reg1_aux64),val);
	}break;
	case P_UINT8+MOV_MMW_W:
	case P_INT8+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();


		Gp reg2_aux64=a.getNextRegister64();
		Gp reg1_aux8=a.getNextRegister8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(reg2_aux64,qreg[dst]);
		else a.mov(reg2_aux64,qword_ptr(workspace,dst*8));
		a.and_(reg2_aux64,rcx);
		if(val<8)a.mov(ptr(memory,reg2_aux64,0,valinc),breg[val]);
		else{
			a.mov(reg1_aux8,ptr(workspace,val*8));
			a.mov(ptr(memory,reg2_aux64,0,valinc),reg1_aux8);
		}

	}break;
	case P_UINT16+MOV_MMW_W:
	case P_INT16+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(reg2_aux64,qreg[dst]);
		else a.mov(reg2_aux64,qword_ptr(workspace,dst*8));
		a.and_(reg2_aux64,rcx);
		if(val<8)a.mov(ptr(memory,reg2_aux64,0,valinc),wreg[val]);
		else{
			Gp reg1_aux16=a.getNextRegister16();
			a.mov(reg1_aux16,ptr(workspace,val*8));
			a.mov(ptr(memory,reg2_aux64,0,valinc),reg1_aux16);
		}
	}break;
	case P_UINT32+MOV_MMW_W:
	case P_INT32+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();


		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(reg2_aux64,qreg[dst]);
		else a.mov(reg2_aux64,qword_ptr(workspace,dst*8));
		a.and_(reg2_aux64,rcx);
		if(val<8)a.mov(ptr(memory,reg2_aux64,0,valinc),dreg[val]);
		else{
			a.mov(eax,ptr(workspace,val*8));
			a.mov(ptr(memory,reg2_aux64,0,valinc),eax);
		}
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
			a.mov(ptr(memory,rbx,0,valinc+4),ax);
		}

	}break;
	case P_UINT64+MOV_MMW_W:
	case P_INT64+MOV_MMW_W:{
		uint8 valinc=t.getNext32();
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();

		Gp reg1_aux64=a.getNextRegister64();
		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(dst<8)a.mov(reg2_aux64,qreg[dst]);
		else a.mov(reg2_aux64,qword_ptr(workspace,dst*8));
		a.and_(reg2_aux64,rcx);
		if(val<8)a.mov(ptr(memory,reg2_aux64,0,valinc),qreg[val]);
		else{
			a.mov(reg1_aux64,ptr(workspace,val*8));
			a.mov(ptr(memory,reg2_aux64,0,valinc),reg1_aux64);
		}

	}break;
	case P_UINT8+MOV_W_MMW:
	case P_INT8+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();
		Gp reg1_aux8=a.getNextRegister8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val*8));
		a.and_(reg2_aux64,rcx);
		if(dst<8)a.mov(breg[dst],ptr(memory,reg2_aux64,0,valinc));
		else{
			a.mov(reg1_aux8,ptr(memory,reg2_aux64,0,valinc));
			a.mov(ptr(workspace,dst*8),reg1_aux8);
		}

	}break;
	case P_UINT16+MOV_W_MMW:
	case P_INT16+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val*8));
		a.and_(reg2_aux64,rcx);
		if(dst<8)a.mov(wreg[dst],ptr(memory,reg2_aux64,0,valinc));
		else{
			Gp reg1_aux16=a.getNextRegister16();
			a.mov(reg1_aux16,ptr(memory,reg2_aux64,0,valinc));
			a.mov(ptr(workspace,dst*8),reg1_aux16);
		}

	}break;
	case P_UINT32+MOV_W_MMW:
	case P_INT32+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val*8));
		a.and_(reg2_aux64,rcx);
		if(dst<8)a.mov(dreg[dst],ptr(memory,reg2_aux64,0,valinc));
		else{
			a.mov(eax,ptr(memory,reg2_aux64,0,valinc));
			a.mov(ptr(workspace,dst*8),eax);
		}
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
	}break;
	case P_UINT64+MOV_W_MMW:
	case P_INT64+MOV_W_MMW:{
		uint8 dst=t.getNext8();
		uint8 valinc=t.getNext32();
		uint8 val=t.getNext8();

		Gp reg1_aux64=a.getNextRegister64();
		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val*8));
		a.and_(reg2_aux64,rcx);
		if(dst<8)a.mov(qreg[dst],ptr(memory,reg2_aux64,0,valinc));
		else{
			a.mov(reg1_aux64,ptr(memory,reg2_aux64,0,valinc));
			a.mov(ptr(workspace,dst*8),reg1_aux64);
		}
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
		if(mem<8) a._mov(wreg[mem],val);
		else a._mov(word_ptr(workspace,mem*8),val);
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
			Gp reg1_aux64=a.getNextRegister64();
			a.mov(rcx,0x0000FFFFFFFFFFFF);
			a.mov(reg1_aux64,aux);
			a.andn(qreg[mem],rcx,qreg[mem]);
			a.add(qreg[mem],reg1_aux64);
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
				Gp reg1_aux8=a.getNextRegister8();
				a.mov(reg1_aux8,byte_ptr(workspace,val*8));
				a.mov(byte_ptr(workspace,mem*8),reg1_aux8);
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
				Gp reg1_aux16=a.getNextRegister16();
				a.mov(reg1_aux16,byte_ptr(workspace,val*8));
				a.mov(byte_ptr(workspace,mem*8),reg1_aux16);
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
				Gp reg1_aux64=a.getNextRegister64();
				a.mov(reg1_aux64,byte_ptr(workspace,val*8));
				a.mov(byte_ptr(workspace,mem*8),reg1_aux64);
			}
		}
	}break;
	case P_UINT8+MOV_W_M:
	case P_INT8+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8)a.mov(breg[mem],byte_ptr(memory,val));
		else{
			Gp reg1_aux8=a.getNextRegister8();
			a.mov(reg1_aux8,byte_ptr(memory,val));
			a.mov(byte_ptr(workspace,mem*8),reg1_aux8);
		}
	}break;
	case P_UINT16+MOV_W_M:
	case P_INT16+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8)a.mov(wreg[mem],word_ptr(memory,val));
		else{
			Gp reg1_aux16=a.getNextRegister16();
			a.mov(reg1_aux16,word_ptr(memory,val));
			a.mov(word_ptr(workspace,mem*8),reg1_aux16);
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
		}
	}break;
	case P_UINT48+MOV_W_M:
	case P_INT48+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8){
			//OPTIMIZATION - Incluido um sistema de economia de 2 clocks
			Gp reg1_aux64=a.getNextRegister64();
			Gp reg2_aux64=a.getNextRegister64();
			a.xor_(reg1_aux64,reg1_aux64);
			a.xor_(reg2_aux64,reg2_aux64);
			a.mov(eax,dword_ptr(memory,val));
			a.mov(bx,word_ptr(memory,val+4));
			//
			a.and_(qreg[mem],0xFFFF000000000000);
			a.shl(reg2_aux64,32);
			a.add(reg1_aux64,reg2_aux64);
			a.add(qreg[mem],reg1_aux64);
		}else {
			//Necessário para optimização acima
			a.mov(eax,dword_ptr(memory,val));
			a.mov(bx,word_ptr(memory,val+4));
			//
			a.mov(dword_ptr(workspace,mem*8),eax);
			a.mov(word_ptr(workspace,(mem*8)+4),bx);
		}
	}break;
	case P_UINT64+MOV_W_M:
	case P_INT64+MOV_W_M:{
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		if(mem<8)a.mov(qreg[mem],qword_ptr(memory,val));
		else{
			Gp reg1_aux64=a.getNextRegister64();
			a.mov(reg1_aux64,qword_ptr(memory,val));
			a.mov(qword_ptr(workspace,mem*8),reg1_aux64);
		}
	}break;
	case P_UINT8+MOV_M_W:
	case P_INT8+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8)a.mov(byte_ptr(memory,mem),breg[val]);
		else{
			Gp reg1_aux8=a.getNextRegister8();
			a.mov(reg1_aux8,byte_ptr(workspace,val*8));
			a.mov(byte_ptr(memory,mem),reg1_aux8);
		}
	}break;
	case P_UINT16+MOV_M_W:
	case P_INT16+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8)a.mov(word_ptr(memory,mem),wreg[val]);
		else{
			Gp reg1_aux16=a.getNextRegister16();
			a.mov(reg1_aux16,word_ptr(workspace,val*8));
			a.mov(word_ptr(memory,mem),reg1_aux16);
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
		}
	}break;
	case P_UINT48+MOV_M_W:
	case P_INT48+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8){
			Gp reg2_aux64=a.getNextRegister64();
			a.mov(reg2_aux64,qreg[val]);
			a.mov(eax,ebx);
			a.shr(reg2_aux64,32);
			a.mov(dx,bx);
		}else{
			a.mov(eax,dword_ptr(workspace,val*8));
			a.mov(dx,word_ptr(workspace,(val*8)+4));
		}
		a.mov(dword_ptr(memory,mem),eax);
		a.mov(word_ptr(memory,mem+4),dx);
	}break;
	case P_UINT64+MOV_M_W:
	case P_INT64+MOV_M_W:{
		uint64 mem=t.getNext48().toInt();
		uint8 val=t.getNext8();
		if(val<8)a.mov(qword_ptr(memory,mem),qreg[val]);
		else{
			Gp reg1_aux64=a.getNextRegister64();
			a.mov(reg1_aux64,qword_ptr(workspace,val*8));
			a.mov(qword_ptr(memory,mem),reg1_aux64);
		}
	}break;
	case P_UINT8+MOV_M_M:
	case P_INT8+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		Gp reg1_aux8=a.getNextRegister8();

		a.mov(reg1_aux8,byte_ptr(memory,val));
		a.mov(byte_ptr(memory,mem),reg1_aux8);
	}break;
	case P_UINT16+MOV_M_M:
	case P_INT16+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		Gp reg1_aux16=a.getNextRegister16();
		a.mov(reg1_aux16,word_ptr(memory,val));
		a.mov(word_ptr(memory,mem),reg1_aux16);
	}break;
	case P_UINT32+MOV_M_M:
	case P_INT32+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();

		a.mov(eax,dword_ptr(memory,val));
		a.mov(dword_ptr(memory,mem),eax);
	}break;
	case P_UINT48+MOV_M_M:
	case P_INT48+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();


		a.mov(eax,dword_ptr(memory,val));
		a.mov(bx,word_ptr(memory,val+4));

		a.mov(dword_ptr(memory,mem),eax);
		a.mov(word_ptr(memory,mem+4),bx);
	}break;
	case P_UINT64+MOV_M_M:
	case P_INT64+MOV_M_M:{
		uint64 mem=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		Gp reg1_aux64=a.getNextRegister64();
		a.mov(reg1_aux64,qword_ptr(memory,val));
		a.mov(qword_ptr(memory,mem),reg1_aux64);
	}break;
	case P_UINT8+MOV_MMW_M:
	case P_INT8+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();

		Gp reg2_aux64=a.getNextRegister64();
		Gp reg1_aux8=a.getNextRegister8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.mov(reg1_aux8,byte_ptr(memory,val));
		a.and_(reg2_aux64,rcx);

		a.mov(byte_ptr(memory,reg2_aux64,0,inc),reg1_aux8);

	}break;
	case P_UINT16+MOV_MMW_M:
	case P_INT16+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();

		Gp reg2_aux64=a.getNextRegister64();
		Gp reg1_aux16=a.getNextRegister16();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.mov(reg1_aux16,word_ptr(memory,val));
		a.and_(reg2_aux64,rcx);

		a.mov(word_ptr(memory,reg2_aux64,0,inc),reg1_aux16);

	}break;
	case P_UINT32+MOV_MMW_M:
	case P_INT32+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();


		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.mov(eax,dword_ptr(memory,val));
		a.and_(reg2_aux64,rcx);
		a.mov(dword_ptr(memory,reg2_aux64,0,inc),eax);

	}break;
	case P_UINT48+MOV_MMW_M:
	case P_INT48+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.mov(eax,dword_ptr(memory,val));
		a.mov(dx,word_ptr(memory,val+4));
		a.and_(reg2_aux64,rcx);

		a.mov(dword_ptr(memory,reg2_aux64,0,inc),eax);
		a.add(reg2_aux64,4);
		a.mov(word_ptr(memory,reg2_aux64,0,inc),dx);

	}break;
	case P_UINT64+MOV_MMW_M:
	case P_INT64+MOV_MMW_M:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext48().toInt();
		Gp reg1_aux64=a.getNextRegister64();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.mov(reg1_aux64,qword_ptr(memory,val));
		a.and_(reg2_aux64,rcx);
		a.mov(qword_ptr(memory,reg2_aux64,0,inc),reg1_aux64);

	}break;
	case P_UINT8+MOV_M_MMW:
	case P_INT8+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();
		Gp reg1_aux8=a.getNextRegister8();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val));
		a.and_(reg2_aux64,rcx);
		a.mov(reg1_aux8,byte_ptr(memory,reg2_aux64,0,inc));
		a.mov(byte_ptr(memory,mem),reg1_aux8);

	}break;
	case P_UINT16+MOV_M_MMW:
	case P_INT16+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();
		Gp reg1_aux16=a.getNextRegister16();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val));
		a.and_(reg2_aux64,rcx);
		a.mov(reg1_aux16,word_ptr(memory,reg2_aux64,0,inc));
		a.mov(word_ptr(memory,mem),reg1_aux16);

	}break;
	case P_UINT32+MOV_M_MMW:
	case P_INT32+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val));
		a.and_(reg2_aux64,rcx);
		a.mov(eax,dword_ptr(memory,reg2_aux64,0,inc));
		a.mov(dword_ptr(memory,mem),eax);

	}break;
	case P_UINT48+MOV_M_MMW:
	case P_INT48+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val));
		a.and_(reg2_aux64,rcx);
		a.mov(eax,dword_ptr(memory,reg2_aux64,0,inc));
		a.add(reg2_aux64,4);
		a.mov(dx,word_ptr(memory,reg2_aux64,0,inc));
		a.mov(dword_ptr(memory,mem),eax);
		a.mov(word_ptr(memory,mem+4),dx);

	}break;
	case P_UINT64+MOV_M_MMW:
	case P_INT64+MOV_M_MMW:{
		uint64 mem=t.getNext48().toInt();
		uint32 inc=t.getNext32();
		uint8 val=t.getNext8();
		Gp reg1_aux64=a.getNextRegister64();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(val<8)a.mov(reg2_aux64,qreg[val]);
		else a.mov(reg2_aux64,qword_ptr(workspace,val));
		a.and_(reg2_aux64,rcx);
		a.mov(reg1_aux64,qword_ptr(memory,reg2_aux64,0,inc));
		a.mov(qword_ptr(memory,mem),reg1_aux64);


	}break;
	case P_UINT8+MOV_MMW_C:
	case P_INT8+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint8 val=t.getNext8();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.and_(reg2_aux64,rcx);
		a.mov(byte_ptr(memory,reg2_aux64,0,inc),val);


	}break;
	case P_UINT16+MOV_MMW_C:
	case P_INT16+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint16 val=t.getNext16();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.and_(reg2_aux64,rcx);
		a.mov(word_ptr(memory,reg2_aux64,0,inc),val);


	}break;
	case P_UINT32+MOV_MMW_C:
	case P_INT32+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint32 val=t.getNext32();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.and_(reg2_aux64,rcx);
		a.mov(dword_ptr(memory,reg2_aux64,0,inc),val);

	}break;
	case P_UINT48+MOV_MMW_C:
	case P_INT48+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint32 val1=t.getNext32();
		uint16 val2=t.getNext16();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.and_(reg2_aux64,rcx);
		a.mov(dword_ptr(memory,reg2_aux64,0,inc),val1);
		a.add(reg2_aux64,4);
		a.mov(word_ptr(memory,reg2_aux64,0,inc),val2);

	}break;
	case P_UINT64+MOV_MMW_C:
	case P_INT64+MOV_MMW_C:{
		uint32 inc=t.getNext32();
		uint8 mem=t.getNext8();
		uint64 val=t.getNext64();

		Gp reg2_aux64=a.getNextRegister64();

		a.mov(rcx,0x0000FFFFFFFFFFFF);
		if(mem<8)a.mov(reg2_aux64,qreg[mem]);
		else a.mov(reg2_aux64,qword_ptr(workspace,mem*8));
		a.and_(reg2_aux64,rcx);
		a.mov(qword_ptr(memory,reg2_aux64,0,inc),val);

	}break;
	default:
		return 0;
	}
	return 1;
}

