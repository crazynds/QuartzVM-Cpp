/*
 * jit.h
 *
 *  Created on: 3 de abr de 2019
 *      Author: lhlag
 */

#ifndef SRC_OPCODES_JIT_H_
#define SRC_OPCODES_JIT_H_

	#include "Jit.h"
	#include "pre_jit.h"

	void laco_jit(Thread &t,CodeHolder *code);


	uint8 cmov(JitContentsAuxiliar jcontent, Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v);
	uint8 mov(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v);
	uint8 aritimetic(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v);
	uint8 optimization(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v);
	uint8 jmp_cmp(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v);

	void init_jit(Thread &t){
		if(t.checkUseCode(2))return;

		uint32 posInit=t.getPontCode();
		{
			uint16 *pt=(uint16*)&t.getContexto().cod[posInit-2];
			*pt=JIT_FLAG_EXECUTE;
		}

		//Necessaries libs
		JitRuntime& rt=t.getJitRuntime();
		CodeHolder code;
		code.init(rt.codeInfo());
		//Create code
		laco_jit(t,&code);
		if(t.isFinalized())return;
		//Save code
		FuncJit& fn=t.getContexto().createFunction(posInit);
		//Generate executable code
		Error err = rt.add(&fn, &code);
		if (err){
			std::cout << "[ERROR] - Deu um erro importante aqui! " << err <<  std::endl;
			t.error_flags|=INTERNAL_ERROR_;
			return;
		}
		uint64 result= fn(t.mem.getPointerMem(),t.workspace,0);
		uint32 flags=result>>32;
		switch(flags){
		case ERROR_JMP_ENTER_JIT_STATE:
			t.error_flags|=INVALID_JMP_JIT_;
			t.setPontCode((uint32)result);
			break;
		case OK_JIT_STATE:
		default:
			t.setPontCode((uint32)result);
			break;
		}
		if(t.checkUseCode(2))return;
	}
	void enter_jit(Thread &t){
		if(t.checkUseCode(4))return;
		uint32 pos=t.getNext32();
		uint32 enter=t.getPontCode();
		FuncJit fn=t.getContexto().getFunction(pos);

		if(fn==0){
			t.setPontCode(pos);
			if(t.checkUseCode(2))return;
			uint32 posInit=t.getPontCode();
			{
				uint16 *pt=(uint16*)&t.getContexto().cod[posInit-2];
				*pt=JIT_FLAG_EXECUTE;
			}
			JitRuntime& rt=t.getJitRuntime();
			CodeHolder code;
			code.init(rt.codeInfo());
			laco_jit(t,&code);
			if(t.isFinalized())return;
			FuncJit &f=t.getContexto().createFunction(posInit);
			Error err = rt.add(&fn, &code);
			if (err){
				std::cout << "[ERROR] - Deu um erro importante aqui! " << err <<  std::endl;
				t.error_flags|=INTERNAL_ERROR_;
				return;
			}
			fn=f;
		}

		uint64 result= fn(t.mem.getPointerMem(),t.workspace,enter);
		uint32 flags=result>>32;
		switch(flags){
		case ERROR_JMP_ENTER_JIT_STATE:
			t.error_flags|=INVALID_JMP_JIT_;
			t.setPontCode((uint32)result);
			break;
		case OK_JIT_STATE:
		default:
			t.setPontCode((uint32)result);
			break;
		}


		if(t.checkUseCode(2))return;
	}

	void execute_jit(Thread &t){

		//std::cout << "Executado jit compilado!!" << std::endl;

		FuncJit fn=t.getContexto().getFunction(t.getPontCode());

		if(fn==0){
			t.error_flags|=NO_OPCODE_COMMAND_;
			return;
		}

		uint64 result= fn(t.mem.getPointerMem(),t.workspace,0);

		uint32 flags=result>>32;
		switch(flags){
		case ERROR_JMP_ENTER_JIT_STATE:
			t.error_flags|=INVALID_JMP_JIT_;
			t.setPontCode((uint32)result);
			break;
		case OK_JIT_STATE:
		default:
			t.setPontCode((uint32)result);
			break;
		}

		if(t.checkUseCode(2))return;
	}

	void end_jit(Thread &t){
		std::cout << "Executou o fim" << std::endl;
		if(t.checkUseCode(2))return;
	}

	void laco_jit(Thread &t,CodeHolder *code){
		JitContentsAuxiliar jcontent;
		AssemblerJIT a(code);
		//20 Clocks perdidos no inicio + 20 clocks no fim
		a.push(rbx);
		a.push(rdi);
		a.push(rsi);
		a.push(r12);
		a.push(r13);
		a.push(r14);
		a.push(r15);
		//qreg free for use r8-r15(8) para workspace
		//rax - rbx - rcx - rdx  para calculos normais
		//rdi - rsi para uso de ponteiros para mem e workspace
		Gp memory=rdi;
		Gp workspace=rsi;
		Gp qreg[8];qreg[0]=r8;qreg[1]=r9;qreg[2]=r10;qreg[3]=r11;qreg[4]=r12;qreg[5]=r13;qreg[6]=r14;qreg[7]=r15;
		Gp dreg[8];dreg[0]=r8d;dreg[1]=r9d;dreg[2]=r10d;dreg[3]=r11d;dreg[4]=r12d;dreg[5]=r13d;dreg[6]=r14d;dreg[7]=r15d;
		Gp wreg[8];wreg[0]=r8w;wreg[1]=r9w;wreg[2]=r10w;wreg[3]=r11w;wreg[4]=r12w;wreg[5]=r13w;wreg[6]=r14w;wreg[7]=r15w;
		Gp breg[8];breg[0]=r8b;breg[1]=r9b;breg[2]=r10b;breg[3]=r11b;breg[4]=r12b;breg[5]=r13b;breg[6]=r14b;breg[7]=r15b;
		a.mov(workspace,rdx); // RSI - WORKSPACE THREAD
		a.mov(memory,qword_ptr(rcx)); //RDI - MEMORIA CONTEXTO
		a.mov(rax,r8); // PRAMETRO goTo
		for(uint16 x=0;x<8;x++)a.mov(qreg[x],qword_ptr(workspace,x*8));
		a.cld();
		a.prefetchnta(ptr(workspace,8*8));	//Move a workspace para perto do processador nos caches.

		Label auxiLabel=a.newLabel();
		Label end=a.newLabel();
		a.cmp(rax,0);
		a.jz(auxiLabel);

		std::vector<Dupla<Label,uint32>> &v=*pre_check_jig(t,a);
		if(t.isFinalized()){//Caso encontrado algum erro, é finalizado o processo.
			return;
		}else if(&v==0){
			t.error_flags|=OVERLOAD_COD_ERROR_;
			return;
		}

		jcontent.maxCode=v[v.size()-1].getSecond();
		jcontent.minCode=t.getPontCode();
		v.erase(v.begin()+v.size()-1);


		a.mov(rax,ERROR_JMP_ENTER_JIT_STATE);  //Caso não tenha encontrado nenhuma opção para entrar no programa, sai da função e retorna um erro.
		a.shl(rax,32);
		a.mov(eax,jcontent.maxCode);
		a.jmp(end);

		a.bind(auxiLabel);
		jcontent.opcode=t.getNext16();
		uint8 type='u';	//Para fins de auxilio nas comparações
		while(jcontent.opcode!=JIT_FLAG_END){
			{
				uint32 aux=t.getPontCode()-2;
				for(uint32 x=0;x<v.size();x++){
					if(v[x].getSecond()==aux){
						a.bind(v[x].getFirst());
						break;
					}
				}
			}
			switch(jcontent.opcode){
			case JIT_FLAG_ENTER_CODE:{
				t.getNext32();
			}break;
			default:
				if(mov(jcontent,t,a,end,v))break;
				if(aritimetic(jcontent,t,a,end,v))break;
				if(optimization(jcontent,t,a,end,v))break;
				if(jmp_cmp(jcontent,t,a,end,v))break;
				if(cmov(jcontent,t,a,end,v))break;
				t.error_flags|=INVALID_OPCODE_JIT_;
				return;
			}
			jcontent.opcode=t.getNext16();
		}


		a.mov(eax,t.getPontCode()); // return values

		a.bind(end);
		for(uint16 x=0;x<8;x++)a.mov(qword_ptr(workspace,x*8),qreg[x]);

		//recover registers
		a.pop(r15);
		a.pop(r14);
		a.pop(r13);
		a.pop(r12);
		a.pop(rsi);
		a.pop(rdi);
		a.pop(rbx);
		a.ret();


		for(uint32 x=0;x<v.size();x++){
			delete &v[x].getFirst();
		}
		delete &v;

	}


#endif /* SRC_OPCODES_JIT_H_ */
