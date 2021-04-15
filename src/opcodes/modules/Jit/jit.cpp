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
	void init_jit(Thread &t);
	uint64 create_jit(Thread &t,uint32 enter);
	void enter_jit(Thread &t);

	void init_jit(Thread &t){
		uint64 result;
		try{
			result=create_jit(t,0);
		}catch(VMException &e){
			e.addToPath("JIT_INIT");
			throw;
		}
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
		FuncJit fn=t.getContext().getFunction(pos);
		uint64 result;

		try{
			if(fn==0){
				t.setPontCode(pos);
				result=create_jit(t,enter);
			}else{
				result=fn(t.mem.getPointerMem(),t.workspace,t,enter);
			}
		}catch(VMException &e){
			e.addToPath("JIT_ENTER");
			throw;
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

//Opcodes
	uint64 create_jit(Thread &t,uint32 enter){
		if(t.checkUseCode(2))return 0;
		uint32 posInit=t.getPontCode();

		t.getContext().set16InCode(posInit-2,JIT_FLAG_EXECUTE);

		//Necessaries libs
		JitRuntime& rt=t.getJitRuntime();
		CodeHolder code;
		code.init(rt.environment());
		//Create code

		try{
			laco_jit(t,&code);
		}catch(VMException &e){
			e.addToPath("JIT_CREATE");
			throw;
		}

		if(t.isFinalized())return 0;
		//Save code
		FuncJit& fn=t.getContext().createFunction(posInit);
		//Generate executable code
		Error err = rt.add(&fn, &code);
		if (err){
			throw CodeException(t.getPontCode(),"JIT_CREATE",_ERROR_JIT_CREATE_ASMJIT_RETURN_ERROR);
		}
		return fn(t.mem.getPointerMem(),t.workspace,t,enter);
	}

	void execute_jit(Thread &t){
		FuncJit fn=t.getContext().getFunction(t.getPontCode());
		if(fn==0){
			throw CodeException(t.getPontCode(),"JIT_EXECUTE","Não foi possivel encontrar a função JIT já criada anteriormente.");
		}
		uint64 result;
		try{
			result= fn(t.mem.getPointerMem(),t.workspace,t,0);
		}catch(VMException &e){
			e.addToPath("JIT_EXECUTE");
			throw;
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

	void end_jit(Thread &t){
		std::cout << "[WARING] - Executou o fim: " << t.getPontCode() << std::endl;
		std::cout << "[WARING] - Esse comando tem propósitos apenas informativo, nunca deve ser executado. Reavaliar código!!" << std::endl;
		if(t.checkUseCode(2))return;
	}
//End Opcodes

	void laco_jit(Thread &t,CodeHolder *code){
		JitContentsAuxiliar jcontent;
		AssemblerJIT a(code);
		ManagerOpcodes &mangOp=t.getVirtualMachine().getManagerOpcodes();
		LibraryModuleOpcode** lmo = mangOp.getModules();
		Label auxiLabel=a.newLabel();
		Label end=a.newLabel();

		a.cmp(rax,0);			//RAX = posição que tem q entrar no código.
		a.jz(auxiLabel);		//RBX = Verificador se ele tem q soltar um erro ou não.

		uint32 startCode=t.getPontCode();
		a.xor_(rbx,rbx);
		Label reentrada=a.newLabel();
		a.bind(reentrada);
		std::map<uint32,Label> *vt;
		try{
			vt=pre_check_jit(t,a,&jcontent.maxCode);
		}catch(VMException &e){
			e.addToPath("JIT_PRE_CHECK");
			throw;
		}
		if(vt==0){ // Caso o pre_jit retornou zero, significa erro
			//t.error_flags|=OVERLOAD_COD_ERROR_;
			if(t.isFinalized())return;
			throw VMException(_INTERNAL_ERRO_INVALID_FUNCIONALITY);
		}else{
			jcontent.minCode=t.getPontCode();
		}
		a.cmp(rbx,1);	//Estava dentro do JIT, entrou pela reentrada e deveria retornar para dentro do programa,
		a.je(end);		//mas não encontrou ponto de retorno. Então vai ser mandado para o código original e buscar o local correto

		a.mov(rax,ERROR_JMP_ENTER_JIT_STATE);  //Caso não tenha encontrado nenhuma opção para entrar no programa, sai da função e retorna um erro.
		a.shl(rax,48);
		a.mov(eax,jcontent.maxCode);
		a.jmp(end);

		a.bind(auxiLabel);
		a.clearRegisters();
		jcontent.opcode=t.getNext16();
		jcontent.sign_operation='u';	//Para fins de auxilio nas comparações

		try{
			while(jcontent.opcode!=JIT_FLAG_END){
				a.nextState();
				{
					uint32 aux=t.getPontCode()-2;
					auto it = vt->find(aux);
					if(it != vt->end()){
						a.clearRegisters();
						a.bind(it->second);
						break;
					}
				}
				bool verif=false;
				uint16 x=0;
				while(!verif && x<t.getVirtualMachine().getManagerOpcodes().sizeModules())
					verif=lmo[x++]->set_opcode_jit(jcontent,t,a,end,*vt);

				if(!verif)
					throw CodeException(t.getPontCode(),"JIT_LOOP_SET_COMAND",_ERROR_JIT_CREATE_ANY_COMAND_FOUND);
				jcontent.opcode=t.getNext16();
			}
		}catch(VMException &e){
			delete vt;
			e.addToPath("JIT_LOOP");
			throw;
		}
		a.clearRegisters();
		{
			uint32 aux=t.getPontCode()-2;
			auto it = vt->find(aux);
			if(it != vt->end()){
				a.clearRegisters();
				a.bind(it->second);
				break;
			}
		}
		a.mov(eax,t.getPontCode()); // return values
		a.bind(end);
		delete vt;
	}

	inline void pushRegisters(AssemblerJIT &a){
		a.push(r8);
		a.push(r9);
		a.push(r10);
		a.push(r11);
		a.sub(rsp,0x18);
	}
	inline void popRegisters(AssemblerJIT &a){
		a.add(rsp,0x18);
		a.pop(r11);
		a.pop(r10);
		a.pop(r9);
		a.pop(r8);
	}

#endif /* SRC_OPCODES_JIT_H_ */
