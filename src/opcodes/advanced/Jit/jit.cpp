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
	uint8 jmp_cmp(JitContentsAuxiliar jcontent,Thread &t, AssemblerJIT &a, Label &end,std::vector<Dupla<Label,uint32>> &v,uint32 startCode,Label reentrada);

	uint64 create_jit(Thread &t,uint32 enter){
		if(t.checkUseCode(2))return 0;
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
		if(t.isFinalized())return 0;
		//Save code
		FuncJit& fn=t.getContexto().createFunction(posInit);
		//Generate executable code
		Error err = rt.add(&fn, &code);
		if (err){
			std::cout << "[ERROR] - Deu um erro importante aqui! " << err <<  std::endl;
			t.error_flags|=INTERNAL_ERROR_;
			return 0;
		}
		return fn(t.mem.getPointerMem(),t.workspace,t,enter);

	}


	void init_jit(Thread &t){
		uint64 result=create_jit(t,0);
		if(result==0){
			return;
		}
		uint16 flags=result>>48;
		switch(flags){
		case ERROR_JMP_ENTER_JIT_STATE:{
			t.error_flags|=INVALID_JMP_JIT_;
			uint16 ctx=(uint16)(result>>32);
			if(ctx==0){
				t.setPontCode((uint32)result);
			}else{
				t.setPontCodeCtx((uint48)result);
			}
		}break;
		case OK_JIT_STATE:
		default:{
			uint16 ctx=(uint16)(result>>32);
			if(ctx==0){
				t.setPontCode((uint32)result);
			}else{
				t.setPontCodeCtx((uint48)result);
			}
		}break;
		}
		if(t.checkUseCode(2))return;
	}
	void enter_jit(Thread &t){
		if(t.checkUseCode(4))return;
		uint32 pos=t.getNext32();
		uint32 enter=t.getPontCode();
		FuncJit fn=t.getContexto().getFunction(pos);
		uint64 result;
		if(fn==0){
			t.setPontCode(pos);
			result=create_jit(t,enter);
		}else{
			result=fn(t.mem.getPointerMem(),t.workspace,t,enter);
		}
		uint16 flags=result>>48;
		switch(flags){
		case ERROR_JMP_ENTER_JIT_STATE:{
			t.error_flags|=INVALID_JMP_JIT_;
			uint16 ctx=(uint16)(result>>32);
			if(ctx==0){
				t.setPontCode((uint32)result);
			}else{
				t.setPontCodeCtx((uint48)result);
			}
		}break;
		case OK_JIT_STATE:
		default:{
			uint16 ctx=(uint16)(result>>32);
			if(ctx==0){
				t.setPontCode((uint32)result);
			}else{
				t.setPontCodeCtx((uint48)result);
			}
		}break;
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

		uint64 result= fn(t.mem.getPointerMem(),t.workspace,t,0);

		uint16 flags=result>>48;
		switch(flags){
		case ERROR_JMP_ENTER_JIT_STATE:{
			t.error_flags|=INVALID_JMP_JIT_;
			uint16 ctx=(uint16)(result>>32);
			if(ctx==0){
				t.setPontCode((uint32)result);
			}else{
				t.setPontCodeCtx((uint48)result);
			}
		}break;
		case OK_JIT_STATE:
		default:{
			uint16 ctx=(uint16)(result>>32);
			if(ctx==0){
				t.setPontCode((uint32)result);
			}else{
				t.setPontCodeCtx((uint48)result);
			}
		}break;
		}
		if(t.checkUseCode(2))return;
	}

	void end_jit(Thread &t){

		std::cout << "Executou o fim: " << t.getPontCode() << std::endl;
		if(t.checkUseCode(2))return;
	}

	void laco_jit(Thread &t,CodeHolder *code){
		JitContentsAuxiliar jcontent;
		AssemblerJIT a(code);


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
		a.mov(workspace,rdx); // RSI - WORKSPACE THREAD
		for(uint16 x=1;x<256/8;x++)a.prefetcht0(ptr(workspace,8*x));	//Move a workspace para perto do processador nos caches.
		a.mov(memory,qword_ptr(rcx)); //RDI - MEMORIA CONTEXTO
		a.push(r8);	// THREAD - ARMAZENADA
		a.mov(rax,r9); // PRAMETRO goTo
		for(uint16 x=0;x<8;x++)a.mov(qreg[x],qword_ptr(workspace,x*8));
		a.cld();

		Label auxiLabel=a.newLabel();
		Label end=a.newLabel();


		a.cmp(rax,0);			//RAX = posição que tem q entrar no código.
		a.jz(auxiLabel);		//RBX = Verificador se ele tem q soltar um erro ou não.
		uint32 startCode=t.getPontCode();
		a.xor_(rbx,rbx);
		Label reentrada=a.newLabel();
		a.bind(reentrada);

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

		Label cond=a.newLabel();
		a.cmp(rbx,1);
		a.jne(cond);
		a.sub(rax,6);
		a.jmp(end);
		a.bind(cond);
		a.mov(rax,ERROR_JMP_ENTER_JIT_STATE);  //Caso não tenha encontrado nenhuma opção para entrar no programa, sai da função e retorna um erro.
		a.shl(rax,48);
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
				if(jmp_cmp(jcontent,t,a,end,v,startCode,reentrada))break;
				if(cmov(jcontent,t,a,end,v))break;
				t.error_flags|=INVALID_OPCODE_JIT_;
				std::cout<< "[ERROR] - Opcode JIT não encontrado. (Erro interno do sistema) " << std::endl;
				return;
			}
			jcontent.opcode=t.getNext16();
		}

		{
			uint32 aux=t.getPontCode()-2;
			for(uint32 x=0;x<v.size();x++){
				if(v[x].getSecond()==aux){
					a.bind(v[x].getFirst());
					break;
				}
			}
		}


		a.mov(eax,t.getPontCode()); // return values

		a.bind(end);

		for(uint16 x=0;x<8;x++)a.mov(qword_ptr(workspace,x*8),qreg[x]);

		//recover registers

		a.add(rsp,0x8);

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

	void pushRegisters(AssemblerJIT &a){
		//a.prefetcht0(ptr(workspace));
		//a.push(rdi);
		//a.push(rsi);
		//for(uint16 x=0;x<8;x++)a.mov(qword_ptr(workspace,x*8),qreg[x]);
		a.push(r8);
		a.push(r9);
		a.push(r10);
		a.push(r11);
		a.sub(rsp,0x18);
	}
	void popRegisters(AssemblerJIT &a){
		a.add(rsp,0x18);
		//for(uint16 x=0;x<8;x++)a.mov(qreg[x],qword_ptr(workspace,x*8));
		a.pop(r11);
		a.pop(r10);
		a.pop(r9);
		a.pop(r8);
		//a.pop(rsi);
		//a.pop(rdi);
	}

#endif /* SRC_OPCODES_JIT_H_ */
