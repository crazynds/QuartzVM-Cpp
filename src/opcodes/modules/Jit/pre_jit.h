#include "../LibraryModuleOpcode.h"
#include "Jit.h"

std::vector<Dupla<Label,uint32>>* pre_check_jig(Thread &t,Assembler &a){
	uint32 save_point=t.getPontCode();
	std::vector<Dupla<Label,uint32>> *vt=new std::vector<Dupla<Label,uint32>>;
	std::vector<Dupla<Label,uint32>> &v=*vt;
	register uint16 p=t.getNext16();
	uint32 auxi=t.getPontCode();
	try{
		while(p!=JIT_FLAG_END){
			LibraryModuleOpcode** lmo = t.getVirtualMachine().getManagerOpcodes().getModules();
			bool verif=false;
			uint16 x=0;

			while(!verif && x<t.getVirtualMachine().getManagerOpcodes().sizeModules()){
				verif=lmo[x]->check_jit(t,a,v,p);
				x++;
			}
			if(t.isFinalized())break;
			if(!verif){
				std::cout << "[ERROR] - Não foi a instrução: " << std::hex << p << std::endl;
				throw CodeException(t.getPontCode(),"JIT_PRE_CHECK_COMAND: "+std::to_string(p),_ERROR_JIT_CREATE_PRE_JIT_NOT_FOUND);
			}
			if(t.checkUseCode(2))break;
			p=t.getNext16();
			auxi=t.getPontCode();
		}
	}catch(VMException &e){
		for(uint32 x=0;x<v.size();x++){
			delete &v[x].getFirst();
		}
		delete vt;
		e.addToPath("JIT_PRE_CHECK_LOOP");
		throw;
	}
	if(t.isFinalized()){
		for(uint32 x=0;x<v.size();x++){
			delete &v[x].getFirst();
		}
		delete vt;
		return 0;
	}
	{
		uint32 x=0;
		while(x<v.size()){
			if(v[x].getSecond()>=t.getPontCode() || v[x].getSecond()<save_point){
				delete &v[x].getFirst();
				v.erase(v.begin()+x);
			}else x++;
		}

	}

	uint32 aux=v.size();
	v.resize(aux+1);
	v[aux].setSecond(t.getPontCode());
	t.setPontCode(save_point);
	return vt;
}
