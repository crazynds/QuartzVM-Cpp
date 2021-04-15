#include "../LibraryModuleOpcode.h"
#include "Jit.h"

inline std::map<uint32,Label>* pre_check_jit(Thread &t,Assembler &a,uint32* maxCode){
	uint32 save_point=t.getPontCode();
	std::map<uint32,Label> *vt=new std::map<uint32,Label>;
	std::map<uint32,Label> &v=*vt;
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
		delete vt;
		e.addToPath("JIT_PRE_CHECK_LOOP");
		throw;
	}
	if(t.isFinalized()){
		delete vt;
		return 0;
	}
	{
		uint32 x=0;
		auto it = v.begin();
		while(it != v.end()){
			if(it->first >=t.getPontCode() || it->first<save_point)
				it = v.erase(it);
			else it++;
		}

	}
	*maxCode = t.getPontCode();
	t.setPontCode(save_point);
	return vt;
}
