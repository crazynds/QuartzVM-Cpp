/*
* Optimization.cpp
*
*  Created on: 11 de mai de 2019
*      Author: lhlag
*/



#include "../Jit.h"

uint8 optimization(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v){
	Gp memory=rdi;
	Gp workspace=rsi;

	Gp qreg[8];qreg[0]=r8;qreg[1]=r9;qreg[2]=r10;qreg[3]=r11;qreg[4]=r12;qreg[5]=r13;qreg[6]=r14;qreg[7]=r15;
	Gp dreg[8];dreg[0]=r8d;dreg[1]=r9d;dreg[2]=r10d;dreg[3]=r11d;dreg[4]=r12d;dreg[5]=r13d;dreg[6]=r14d;dreg[7]=r15d;
	Gp wreg[8];wreg[0]=r8w;wreg[1]=r9w;wreg[2]=r10w;wreg[3]=r11w;wreg[4]=r12w;wreg[5]=r13w;wreg[6]=r14w;wreg[7]=r15w;
	Gp breg[8];breg[0]=r8b;breg[1]=r9b;breg[2]=r10b;breg[3]=r11b;breg[4]=r12b;breg[5]=r13b;breg[6]=r14b;breg[7]=r15b;

	switch(jcontent.opcode){
	case P_UINT8+COPY_MW_MW_C:
	case P_INT8+COPY_MW_MW_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint32 times=t.getNext32();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		a.mov(rcx,times);
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsb();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT8+COPY_MW_MW_W:
	case P_INT8+COPY_MW_MW_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint8 times=t.getNext8();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsb();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT16+COPY_MW_MW_C:
	case P_INT16+COPY_MW_MW_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint32 times=t.getNext32();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		a.mov(rcx,times);
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsw();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT16+COPY_MW_MW_W:
	case P_INT16+COPY_MW_MW_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint8 times=t.getNext8();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsw();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT32+COPY_MW_MW_C:
	case P_INT32+COPY_MW_MW_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint32 times=t.getNext32();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		a.mov(rcx,times);
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsd();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT32+COPY_MW_MW_W:
	case P_INT32+COPY_MW_MW_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint8 times=t.getNext8();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsd();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT48+COPY_MW_MW_C:
	case P_INT48+COPY_MW_MW_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint32 times=t.getNext32();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		a.mov(rcx,times);
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsw();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT48+COPY_MW_MW_W:
	case P_INT48+COPY_MW_MW_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint8 times=t.getNext8();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.lea(rcx,ptr(rcx,rcx,1));
		a.rep();
		a.movsw();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT64+COPY_MW_MW_C:
	case P_INT64+COPY_MW_MW_C:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint32 times=t.getNext32();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		a.mov(rcx,times);
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsq();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT64+COPY_MW_MW_W:
	case P_INT64+COPY_MW_MW_W:{
		uint8 dst=t.getNext8();
		uint8 val=t.getNext8();
		uint8 times=t.getNext8();
		if(dst>8){

			a.mov(rax,ptr(workspace,dst*8));
		}
		if(val>8){

			a.mov(rbx,ptr(workspace,val*8));
		}
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		if(val<8)a.lea(rsi,ptr(memory,qreg[val]));
		else a.lea(rsi,ptr(memory,rbx));
		if(dst<8)a.add(rdi,qreg[dst]);
		else a.add(rdi,rax);
		a.rep();
		a.movsq();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT8+COPY_M_M_C:
	case P_INT8+COPY_M_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint32 times=t.getNext32();
		a.push(rdi);
		a.push(rsi);
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.mov(rcx,times);
		a.rep();
		a.movsb();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT8+COPY_M_M_W:
	case P_INT8+COPY_M_M_W:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint8 times=t.getNext8();
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.rep();
		a.movsb();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT16+COPY_M_M_C:
	case P_INT16+COPY_M_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint32 times=t.getNext32();
		a.push(rdi);
		a.push(rsi);
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.mov(rcx,times);
		a.rep();
		a.movsw();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT16+COPY_M_M_W:
	case P_INT16+COPY_M_M_W:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint8 times=t.getNext8();
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.rep();
		a.movsw();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT32+COPY_M_M_C:
	case P_INT32+COPY_M_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint32 times=t.getNext32();
		a.push(rdi);
		a.push(rsi);
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.mov(rcx,times);
		a.rep();
		a.movsd();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT32+COPY_M_M_W:
	case P_INT32+COPY_M_M_W:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint8 times=t.getNext8();
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.rep();
		a.movsd();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT48+COPY_M_M_C:
	case P_INT48+COPY_M_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint32 times=t.getNext32();
		a.push(rdi);
		a.push(rsi);
		a.mov(rcx,times*3);
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.rep();
		a.movsw();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT48+COPY_M_M_W:
	case P_INT48+COPY_M_M_W:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint8 times=t.getNext8();
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.lea(rcx,ptr(rcx,rcx,1)); // mul for 3
		a.rep();
		a.movsw();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT64+COPY_M_M_C:
	case P_INT64+COPY_M_M_C:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint32 times=t.getNext32();
		a.push(rdi);
		a.push(rsi);
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.mov(rcx,times);
		a.rep();
		a.movsq();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case P_UINT64+COPY_M_M_W:
	case P_INT64+COPY_M_M_W:{
		uint64 dst=t.getNext48().toInt();
		uint64 val=t.getNext48().toInt();
		uint8 times=t.getNext8();
		a.push(rdi);
		a.push(rsi);
		if(times<8)a.movzx(rcx,dreg[times]);
		else a.movzx(rcx,dword_ptr(workspace,times*8));
		a.lea(rsi,ptr(memory,val));
		a.add(rdi,dst);
		a.rep();
		a.movsq();
		a.pop(rsi);
		a.pop(rdi);


	}break;
	case LOOP_C_W:{
		uint32 aux=t.getNext32();
		uint8 val=t.getNext8();
		Label l=a.newLabel();
		if(val<8){
			a.dec(qreg[val]);
			a.je(l);
		}else{
			a.mov(rax,ptr(workspace,val*8));
			a.dec(rax);
			a.je(l);
			a.mov(ptr(workspace,val*8),rax);

		}
		if(aux>=jcontent.maxCode || aux<jcontent.minCode){
			a.xor_(rax,rax);
			a.mov(eax,aux);
			a.jmp(end);

		}else for(uint32 x=0;x<v.size();x++){
			if(v[x].getSecond()==aux){
				a.jmp(v[x].getFirst());
				break;
			}
		}
		a.bind(l);
	}break;
	case INC_W:{
		uint8 mem=t.getNext8();
		if(mem<8)a.inc(qreg[mem]);
		else a.inc(qword_ptr(workspace,mem*8));
	}break;
	case DEC_W:{
		uint8 mem=t.getNext8();
		if(mem<8)a.dec(qreg[mem]);
		else a.dec(qword_ptr(workspace,mem*8));
	}break;
	case INC_M:{
		uint64 mem=t.getNext48().toInt();
		a.inc(qword_ptr(memory,mem));
	}break;
	case DEC_M:{
		uint64 mem=t.getNext48().toInt();
		a.dec(qword_ptr(memory,mem));
	}break;
	case LEA_W__W_W_C:{
		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();
		uint64 mul=t.getNext64();

		if(src1<8)a.mov(rbx,qreg[src1]);
		else a.mov(rbx,qword_ptr(workspace,src1*8));
		if(src2<8)a.mov(rax,qreg[src2]);
		else a.mov(rax,qword_ptr(workspace,src2*8));

		a.mul(mul);

		if(dst<8){
			a.lea(qreg[dst],ptr(rbx,rax));
		}else{
			a.lea(rdx,ptr(rbx,rax));
			a.mov(qword_ptr(workspace,dst*8),rdx);
		}

	}break;
	case LEA_W__W_W_W:{
		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();
		uint64 src3=t.getNext8();

		if(src1<8)a.mov(rbx,qreg[src1]);
		else a.mov(rbx,qword_ptr(workspace,src1*8));
		if(src2<8)a.mov(rax,qreg[src2]);
		else a.mov(rax,qword_ptr(workspace,src2*8));
		if(src3<8)a.mov(rcx,qreg[src3]);
		else a.mov(rcx,qword_ptr(workspace,src3*8));

		a.mul(rcx);

		if(dst<8){
			a.lea(qreg[dst],ptr(rbx,rax));
		}else{
			a.lea(rcx,ptr(rbx,rax));
			a.mov(qword_ptr(workspace,dst*8),rcx);
		}




	}break;
	case LEA_W__W_W_1:{
		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();
		if(src1<8){
			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],qreg[src2]));
				else{
					a.lea(rax,ptr(qreg[src1],qreg[src2]));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],rbx));
				else{
					a.lea(rax,ptr(qreg[src1],rbx));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}else{
			a.mov(rcx,qword_ptr(workspace,src1*8));

			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(rcx,qreg[src2]));
				else{
					a.lea(rax,ptr(rcx,qreg[src2]));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(rcx,rbx));
				else{
					a.lea(rax,ptr(rcx,rbx));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}
	}break;
	case LEA_W__W_W_2:{

		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();

		if(src1<8){
			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],qreg[src2],1));
				else{
					a.lea(rax,ptr(qreg[src1],qreg[src2],1));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],rbx,1));
				else{
					a.lea(rax,ptr(qreg[src1],rbx,1));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}else{
			a.mov(rcx,qword_ptr(workspace,src1*8));

			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(rcx,qreg[src2],1));
				else{
					a.lea(rax,ptr(rcx,qreg[src2],1));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(rcx,rbx,1));
				else{
					a.lea(rax,ptr(rcx,rbx,1));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}
	}break;
	case LEA_W__W_W_4:{

		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();

		if(src1<8){
			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],qreg[src2],2));
				else{
					a.lea(rax,ptr(qreg[src1],qreg[src2],2));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],rbx,2));
				else{
					a.lea(rax,ptr(qreg[src1],rbx,2));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}else{
			a.mov(rcx,qword_ptr(workspace,src1*8));

			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(rcx,qreg[src2],2));
				else{
					a.lea(rax,ptr(rcx,qreg[src2],2));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(rcx,rbx,2));
				else{
					a.lea(rax,ptr(rcx,rbx,2));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}
	}break;
	case LEA_W__W_W_8:{

		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();

		if(src1<8){
			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],qreg[src2],3));
				else{
					a.lea(rax,ptr(qreg[src1],qreg[src2],3));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],rbx,3));
				else{
					a.lea(rax,ptr(qreg[src1],rbx,3));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}else{
			a.mov(rcx,qword_ptr(workspace,src1*8));

			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(rcx,qreg[src2],3));
				else{
					a.lea(rax,ptr(rcx,qreg[src2],3));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(rcx,rbx,3));
				else{
					a.lea(rax,ptr(rcx,rbx,3));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}
	}break;
	case LEA_W__W_W_16:{

		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();

		if(src1<8){
			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],qreg[src2],4));
				else{
					a.lea(rax,ptr(qreg[src1],qreg[src2],4));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],rbx,4));
				else{
					a.lea(rax,ptr(qreg[src1],rbx,4));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}else{
			a.mov(rcx,qword_ptr(workspace,src1*8));

			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(rcx,qreg[src2],4));
				else{
					a.lea(rax,ptr(rcx,qreg[src2],4));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(rcx,rbx,4));
				else{
					a.lea(rax,ptr(rcx,rbx,4));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}
	}break;
	case LEA_W__W_W_32:{

		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();

		if(src1<8){
			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],qreg[src2],5));
				else{
					a.lea(rax,ptr(qreg[src1],qreg[src2],5));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],rbx,5));
				else{
					a.lea(rax,ptr(qreg[src1],rbx,5));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}else{
			a.mov(rcx,qword_ptr(workspace,src1*8));

			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(rcx,qreg[src2],5));
				else{
					a.lea(rax,ptr(rcx,qreg[src2],5));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(rcx,rbx,5));
				else{
					a.lea(rax,ptr(rcx,rbx,5));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}
	}break;
	case LEA_W__W_W_64:{

		uint8 dst=t.getNext8();
		uint8 src1=t.getNext8();
		uint8 src2=t.getNext8();

		if(src1<8){
			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],qreg[src2],6));
				else{
					a.lea(rax,ptr(qreg[src1],qreg[src2],6));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(qreg[src1],rbx,6));
				else{
					a.lea(rax,ptr(qreg[src1],rbx,6));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}else{
			a.mov(rcx,qword_ptr(workspace,src1*8));

			if(src2<8){
				if(dst<8)a.lea(qreg[dst],ptr(rcx,qreg[src2],6));
				else{
					a.lea(rax,ptr(rcx,qreg[src2],6));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}else{
				a.mov(rbx,qword_ptr(workspace,src2*8));

				if(dst<8)a.lea(qreg[dst],ptr(rcx,rbx,6));
				else{
					a.lea(rax,ptr(rcx,rbx,6));
					a.mov(qword_ptr(workspace,dst*8),rax);

				}
			}
		}
	}break;
	default:
		return 0;
	}
	return 1;
}

