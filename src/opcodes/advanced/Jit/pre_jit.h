#include "Jit.h"

std::vector<Dupla<Label,uint32>>* pre_check_jig(Thread &t,Assembler &a){
	uint32 save_point=t.getPontCode();
	std::vector<Dupla<Label,uint32>> *vt=new std::vector<Dupla<Label,uint32>>;
	std::vector<Dupla<Label,uint32>> &v=*vt;
	uint16 p=t.getNext16();
	while(p!=JIT_FLAG_END){
		uint32 auxi=t.getPontCode();
		switch(p){
		case JIT_FLAG_ENTER_CODE:{
			if(t.checkUseCode(4))return 0;
			t.getNext32();
			int b=0;
			uint32 idLabel=t.getPontCode();
			for(int x=0;x<v.size();x++){
				if(v[x].getSecond()==idLabel){
					b=1;
					a.cmp(rax,idLabel);
					a.je(v[x].getFirst());
					break;
				}
			}
			if(b)break;
			Label *jmp=new Label();
			*jmp=a.newLabel();
			uint32 aux=v.size();
			v.resize(aux+1);
			v[aux].setFirst(jmp);
			v[aux].setSecond(idLabel);
			a.cmp(rax,idLabel);
			a.je(*jmp);
			}break;
		case JMP_C:
		case JMP_C_DI:
		case JMP_C_IG:
		case JMP_C_MA:
		case JMP_C_MA_IG:
		case JMP_C_ME:
		case JMP_C_ME_IG:{
			if(t.checkUseCode(4))return 0;
			int b=0;
			uint32 idLabel=t.getNext32();
			for(int x=0;x<v.size();x++){
				if(v[x].getSecond()==idLabel){
					b=1;
					break;
				}
			}
			if(b)break;
			Label *jmp=new Label();
			*jmp=a.newLabel();
			uint32 aux=v.size();
			v.resize(aux+1);
			v[aux].setFirst(jmp);
			v[aux].setSecond(idLabel);
			}break;
		case LOOP_C_W:{
			if(t.checkUseCode(5))return 0;
			int b=0;
			uint32 idLabel=t.getNext32();
			t.getNext8();
			for(int x=0;x<v.size();x++){
				if(v[x].getSecond()==idLabel){
					b=1;
					break;
				}
			}
			if(b)break;
			Label *jmp=new Label();
			*jmp=a.newLabel();
			uint32 aux=v.size();
			v.resize(aux+1);
			v[aux].setFirst(jmp);
			v[aux].setSecond(idLabel);
			}break;
		case INC_W:
		case DEC_W:
			{if(t.checkUseCode(1))return 0;t.setPontCode(t.getPontCode()+1);}break;
		case P_UINT8+MUL_W_C:
		case P_UINT8+SOMA_W_C:
		case P_UINT8+SUB_W_C:
		case P_INT8+MUL_W_C:
		case P_INT8+SOMA_W_C:
		case P_INT8+SUB_W_C:
		case P_UINT8+MUL_W_W:
		case P_UINT16+MUL_W_W:
		case P_UINT32+MUL_W_W:
		case P_UINT48+MUL_W_W:
		case P_UINT64+MUL_W_W:
		case P_INT8+MUL_W_W:
		case P_INT16+MUL_W_W:
		case P_INT32+MUL_W_W:
		case P_INT48+MUL_W_W:
		case P_INT64+MUL_W_W:
		case P_UINT8+SOMA_W_W:
		case P_UINT16+SOMA_W_W:
		case P_UINT32+SOMA_W_W:
		case P_UINT48+SOMA_W_W:
		case P_UINT64+SOMA_W_W:
		case P_INT8+SOMA_W_W:
		case P_INT16+SOMA_W_W:
		case P_INT32+SOMA_W_W:
		case P_INT48+SOMA_W_W:
		case P_INT64+SOMA_W_W:
		case P_UINT8+SUB_W_W:
		case P_UINT16+SUB_W_W:
		case P_UINT32+SUB_W_W:
		case P_UINT48+SUB_W_W:
		case P_UINT64+SUB_W_W:
		case P_INT8+SUB_W_W:
		case P_INT16+SUB_W_W:
		case P_INT32+SUB_W_W:
		case P_INT48+SUB_W_W:
		case P_INT64+SUB_W_W:
		case P_INT8+MOV_W_C:
		case P_UINT8+MOV_W_C:
		case P_INT8+MOV_W_W:
		case P_UINT8+MOV_W_W:
		case P_INT16+MOV_W_W:
		case P_UINT16+MOV_W_W:
		case P_INT32+MOV_W_W:
		case P_UINT32+MOV_W_W:
		case P_INT48+MOV_W_W:
		case P_UINT48+MOV_W_W:
		case P_INT64+MOV_W_W:
		case P_UINT64+MOV_W_W:
		case P_INT8+MOV_MMW_C:
		case P_UINT8+MOV_MMW_C:
		case P_UINT8+CMP_W_W:
		case P_INT8+CMP_W_W:
		case P_UINT16+CMP_W_W:
		case P_INT16+CMP_W_W:
		case P_UINT32+CMP_W_W:
		case P_INT32+CMP_W_W:
		case P_UINT48+CMP_W_W:
		case P_INT48+CMP_W_W:
		case P_UINT64+CMP_W_W:
		case P_INT64+CMP_W_W:
		case P_UINT8+CMP_W_C:
		case P_INT8+CMP_W_C:
		case P_UINT8+DD_W_W:
		case P_UINT8+DD_W_C:
		case P_INT8+DD_W_W:
		case P_INT8+DD_W_C:
		case P_UINT16+DD_W_W:
		case P_UINT16+DD_W_C:
		case P_INT16+DD_W_W:
		case P_INT16+DD_W_C:
		case P_UINT32+DD_W_W:
		case P_UINT32+DD_W_C:
		case P_INT32+DD_W_W:
		case P_INT32+DD_W_C:
		case P_UINT48+DD_W_W:
		case P_UINT48+DD_W_C:
		case P_INT48+DD_W_W:
		case P_INT48+DD_W_C:
		case P_UINT64+DD_W_W:
		case P_UINT64+DD_W_C:
		case P_INT64+DD_W_W:
		case P_INT64+DD_W_C:
		case P_UINT8+DE_W_W:
		case P_UINT8+DE_W_C:
		case P_INT8+DE_W_W:
		case P_INT8+DE_W_C:
		case P_UINT16+DE_W_W:
		case P_UINT16+DE_W_C:
		case P_INT16+DE_W_W:
		case P_INT16+DE_W_C:
		case P_UINT32+DE_W_W:
		case P_UINT32+DE_W_C:
		case P_INT32+DE_W_W:
		case P_INT32+DE_W_C:
		case P_UINT48+DE_W_W:
		case P_UINT48+DE_W_C:
		case P_INT48+DE_W_W:
		case P_INT48+DE_W_C:
		case P_UINT64+DE_W_W:
		case P_UINT64+DE_W_C:
		case P_INT64+DE_W_W:
		case P_INT64+DE_W_C:
		case P_UINT8+DIV_W_C:
		case P_INT8+DIV_W_C:
		case P_UINT8+DIV_W_W:
		case P_INT8+DIV_W_W:
		case P_UINT16+DIV_W_W:
		case P_INT16+DIV_W_W:
		case P_UINT32+DIV_W_W:
		case P_INT32+DIV_W_W:
		case P_UINT48+DIV_W_W:
		case P_INT48+DIV_W_W:
		case P_UINT64+DIV_W_W:
		case P_INT64+DIV_W_W:
			{if(t.checkUseCode(2))return 0;t.setPontCode(t.getPontCode()+2);}break;
		case P_UINT16+MUL_W_C:
		case P_UINT16+SOMA_W_C:
		case P_UINT16+SUB_W_C:
		case P_INT16+MUL_W_C:
		case P_INT16+SOMA_W_C:
		case P_INT16+SUB_W_C:
		case P_INT16+MOV_W_C:
		case P_UINT16+MOV_W_C:
		case LEA_W__W_W_1:
		case LEA_W__W_W_2:
		case LEA_W__W_W_4:
		case LEA_W__W_W_8:
		case LEA_W__W_W_16:
		case LEA_W__W_W_32:
		case LEA_W__W_W_64:
		case P_UINT16+CMP_W_C:
		case P_INT16+CMP_W_C:
		case P_UINT16+DIV_W_C:
		case P_INT16+DIV_W_C:
		case P_UINT64+COPY_MW_MW_W:
		case P_INT64+COPY_MW_MW_W:
		case P_UINT32+COPY_MW_MW_W:
		case P_INT32+COPY_MW_MW_W:
		case P_UINT16+COPY_MW_MW_W:
		case P_INT16+COPY_MW_MW_W:
		case P_UINT8+COPY_MW_MW_W:
		case P_INT8+COPY_MW_MW_W:
		case P_UINT48+COPY_MW_MW_W:
		case P_INT48+COPY_MW_MW_W:
			{if(t.checkUseCode(3))return 0;t.setPontCode(t.getPontCode()+3);}break;
		case LEA_W__W_W_W:
			{if(t.checkUseCode(4))return 0;t.setPontCode(t.getPontCode()+4);}break;
		case P_INT32+MOV_W_C:
		case P_UINT32+MOV_W_C:
		case P_UINT32+MUL_W_C:
		case P_UINT32+SOMA_W_C:
		case P_UINT32+SUB_W_C:
		case P_INT32+MUL_W_C:
		case P_INT32+SOMA_W_C:
		case P_INT32+SUB_W_C:
		case P_UINT32+CMP_W_C:
		case P_INT32+CMP_W_C:
		case P_UINT32+DIV_W_C:
		case P_INT32+DIV_W_C:
		case P_INT16+MOV_MMW_C:
		case P_UINT16+MOV_MMW_C:
			{if(t.checkUseCode(5))return 0;t.setPontCode(t.getPontCode()+5);}break;
		case P_UINT8+MOV_W_MMW:
		case P_INT8+MOV_W_MMW:
		case P_UINT16+MOV_W_MMW:
		case P_INT16+MOV_W_MMW:
		case P_UINT32+MOV_W_MMW:
		case P_INT32+MOV_W_MMW:
		case P_UINT48+MOV_W_MMW:
		case P_INT48+MOV_W_MMW:
		case P_UINT64+MOV_W_MMW:
		case P_INT64+MOV_W_MMW:
		case P_UINT8+MOV_MMW_W:
		case P_INT8+MOV_MMW_W:
		case P_UINT16+MOV_MMW_W:
		case P_INT16+MOV_MMW_W:
		case P_UINT32+MOV_MMW_W:
		case P_INT32+MOV_MMW_W:
		case P_UINT48+MOV_MMW_W:
		case P_INT48+MOV_MMW_W:
		case P_UINT64+MOV_MMW_W:
		case P_INT64+MOV_MMW_W:
			{if(t.checkUseCode(6))return 0;t.setPontCode(t.getPontCode()+6);}break;
		case P_UINT8+CMP_M_C:
		case P_INT8+CMP_M_C:
		case P_UINT8+MUL_M_C:
		case P_UINT8+SOMA_M_C:
		case P_UINT8+SUB_M_C:
		case P_INT8+MUL_M_C:
		case P_INT8+SOMA_M_C:
		case P_INT8+SUB_M_C:
		case P_INT8+MOV_M_C:
		case P_UINT8+MOV_M_C:
		case P_INT48+MOV_W_C:
		case P_UINT48+MOV_W_C:
		case P_UINT8+MOV_W_M:
		case P_INT8+MOV_W_M:
		case P_UINT8+MOV_M_W:
		case P_INT8+MOV_M_W:
		case P_UINT16+MOV_W_M:
		case P_INT16+MOV_W_M:
		case P_UINT16+MOV_M_W:
		case P_INT16+MOV_M_W:
		case P_UINT32+MOV_W_M:
		case P_INT32+MOV_W_M:
		case P_UINT32+MOV_M_W:
		case P_INT32+MOV_M_W:
		case P_UINT48+MOV_W_M:
		case P_INT48+MOV_W_M:
		case P_UINT48+MOV_M_W:
		case P_INT48+MOV_M_W:
		case P_UINT64+MOV_W_M:
		case P_INT64+MOV_W_M:
		case P_UINT64+MOV_M_W:
		case P_INT64+MOV_M_W:
		case P_UINT8+MUL_W_M:
		case P_UINT16+MUL_W_M:
		case P_UINT32+MUL_W_M:
		case P_UINT48+MUL_W_M:
		case P_UINT64+MUL_W_M:
		case P_INT8+MUL_W_M:
		case P_INT16+MUL_W_M:
		case P_INT32+MUL_W_M:
		case P_INT48+MUL_W_M:
		case P_INT64+MUL_W_M:
		case P_UINT8+SOMA_W_M:
		case P_UINT16+SOMA_W_M:
		case P_UINT32+SOMA_W_M:
		case P_UINT48+SOMA_W_M:
		case P_UINT64+SOMA_W_M:
		case P_INT8+SOMA_W_M:
		case P_INT16+SOMA_W_M:
		case P_INT32+SOMA_W_M:
		case P_INT48+SOMA_W_M:
		case P_INT64+SOMA_W_M:
		case P_UINT8+SUB_W_M:
		case P_UINT16+SUB_W_M:
		case P_UINT32+SUB_W_M:
		case P_UINT48+SUB_W_M:
		case P_UINT64+SUB_W_M:
		case P_INT8+SUB_W_M:
		case P_INT16+SUB_W_M:
		case P_INT32+SUB_W_M:
		case P_INT48+SUB_W_M:
		case P_INT64+SUB_W_M:
		case P_UINT48+MUL_W_C:
		case P_UINT48+SOMA_W_C:
		case P_UINT48+SUB_W_C:
		case P_INT48+MUL_W_C:
		case P_INT48+SOMA_W_C:
		case P_INT48+SUB_W_C:
		case P_UINT8+CMP_M_W:
		case P_INT8+CMP_M_W:
		case P_UINT16+CMP_M_W:
		case P_INT16+CMP_M_W:
		case P_UINT32+CMP_M_W:
		case P_INT32+CMP_M_W:
		case P_UINT48+CMP_M_W:
		case P_INT48+CMP_M_W:
		case P_UINT64+CMP_M_W:
		case P_INT64+CMP_M_W:
		case P_UINT8+CMP_W_M:
		case P_INT8+CMP_W_M:
		case P_UINT16+CMP_W_M:
		case P_INT16+CMP_W_M:
		case P_UINT32+CMP_W_M:
		case P_INT32+CMP_W_M:
		case P_UINT48+CMP_W_M:
		case P_INT48+CMP_W_M:
		case P_UINT64+CMP_W_M:
		case P_INT64+CMP_W_M:
		case P_UINT48+CMP_W_C:
		case P_INT48+CMP_W_C:
		case P_UINT48+DIV_W_C:
		case P_INT48+DIV_W_C:
		case P_UINT8+DIV_W_M:
		case P_UINT16+DIV_W_M:
		case P_UINT32+DIV_W_M:
		case P_UINT48+DIV_W_M:
		case P_UINT64+DIV_W_M:
		case P_INT8+DIV_W_M:
		case P_INT16+DIV_W_M:
		case P_INT32+DIV_W_M:
		case P_INT48+DIV_W_M:
		case P_INT64+DIV_W_M:
		case P_UINT8+DIV_M_C:
		case P_INT8+DIV_M_C:
		case P_INT32+MOV_MMW_C:
		case P_UINT32+MOV_MMW_C:
			{if(t.checkUseCode(7))return 0;t.setPontCode(t.getPontCode()+7);}break;
		case P_UINT16+CMP_M_C:
		case P_INT16+CMP_M_C:
		case P_INT16+MOV_M_C:
		case P_UINT16+MOV_M_C:
		case P_UINT16+MUL_M_C:
		case P_UINT16+SOMA_M_C:
		case P_UINT16+SUB_M_C:
		case P_INT16+MUL_M_C:
		case P_INT16+SOMA_M_C:
		case P_INT16+SUB_M_C:
		case P_UINT16+DIV_M_C:
		case P_INT16+DIV_M_C:
			{if(t.checkUseCode(8))return 0;t.setPontCode(t.getPontCode()+8);}break;
		case P_INT64+MOV_W_C:
		case P_UINT64+MOV_W_C:
		case P_UINT64+MUL_W_C:
		case P_UINT64+SOMA_W_C:
		case P_UINT64+SUB_W_C:
		case P_INT64+MUL_W_C:
		case P_INT64+SOMA_W_C:
		case P_INT64+SUB_W_C:
		case P_UINT64+CMP_W_C:
		case P_INT64+CMP_W_C:
		case P_UINT64+DIV_W_C:
		case P_INT64+DIV_W_C:
		case P_INT48+MOV_MMW_C:
		case P_UINT48+MOV_MMW_C:
		case P_INT8+MOV_MMW_M:
		case P_UINT8+MOV_MMW_M:
		case P_INT16+MOV_MMW_M:
		case P_UINT16+MOV_MMW_M:
		case P_INT32+MOV_MMW_M:
		case P_UINT32+MOV_MMW_M:
		case P_INT48+MOV_MMW_M:
		case P_UINT48+MOV_MMW_M:
		case P_INT64+MOV_MMW_M:
		case P_UINT64+MOV_MMW_M:
		case P_INT8+MOV_M_MMW:
		case P_UINT8+MOV_M_MMW:
		case P_INT16+MOV_M_MMW:
		case P_UINT16+MOV_M_MMW:
		case P_INT32+MOV_M_MMW:
		case P_UINT32+MOV_M_MMW:
		case P_INT48+MOV_M_MMW:
		case P_UINT48+MOV_M_MMW:
		case P_INT64+MOV_M_MMW:
		case P_UINT64+MOV_M_MMW:
			{if(t.checkUseCode(9))return 0;t.setPontCode(t.getPontCode()+9);}break;
		case P_UINT32+CMP_M_C:
		case P_INT32+CMP_M_C:
		case P_INT32+MOV_M_C:
		case P_UINT32+MOV_M_C:
		case P_UINT32+MUL_M_C:
		case P_UINT32+SOMA_M_C:
		case P_UINT32+SUB_M_C:
		case P_INT32+MUL_M_C:
		case P_INT32+SOMA_M_C:
		case P_INT32+SUB_M_C:
		case P_UINT32+DIV_M_C:
		case P_INT32+DIV_M_C:
			{if(t.checkUseCode(10))return 0;t.setPontCode(t.getPontCode()+10);}break;
		case LEA_W__W_W_C:
			{if(t.checkUseCode(11))return 0;t.setPontCode(t.getPontCode()+11);}break;
		case P_INT48+MOV_M_C:
		case P_UINT48+MOV_M_C:
		case P_UINT48+MUL_M_C:
		case P_UINT48+SOMA_M_C:
		case P_UINT48+SUB_M_C:
		case P_INT48+MUL_M_C:
		case P_INT48+SOMA_M_C:
		case P_INT48+SUB_M_C:
		case P_INT8+MOV_M_M:
		case P_UINT8+MOV_M_M:
		case P_INT16+MOV_M_M:
		case P_UINT16+MOV_M_M:
		case P_INT32+MOV_M_M:
		case P_UINT32+MOV_M_M:
		case P_INT48+MOV_M_M:
		case P_UINT48+MOV_M_M:
		case P_INT64+MOV_M_M:
		case P_UINT64+MOV_M_M:
		case P_UINT48+CMP_M_C:
		case P_INT48+CMP_M_C:
		case P_UINT8+CMP_M_M:
		case P_INT8+CMP_M_M:
		case P_UINT16+CMP_M_M:
		case P_INT16+CMP_M_M:
		case P_UINT32+CMP_M_M:
		case P_INT32+CMP_M_M:
		case P_UINT48+CMP_M_M:
		case P_INT48+CMP_M_M:
		case P_UINT64+CMP_M_M:
		case P_INT64+CMP_M_M:
		case P_UINT48+DIV_M_C:
		case P_INT48+DIV_M_C:
			{if(t.checkUseCode(12))return 0;t.setPontCode(t.getPontCode()+12);}break;
		case P_UINT8+COPY_M_M_W:
		case P_INT8+COPY_M_M_W:
		case P_UINT16+COPY_M_M_W:
		case P_INT16+COPY_M_M_W:
		case P_UINT32+COPY_M_M_W:
		case P_INT32+COPY_M_M_W:
		case P_UINT48+COPY_M_M_W:
		case P_INT48+COPY_M_M_W:
		case P_UINT64+COPY_M_M_W:
		case P_INT64+COPY_M_M_W:
		case P_INT64+MOV_MMW_C:
		case P_UINT64+MOV_MMW_C:
			{if(t.checkUseCode(13))return 0;t.setPontCode(t.getPontCode()+13);}break;
		case P_INT64+MOV_M_C:
		case P_UINT64+MOV_M_C:
		case P_UINT64+MUL_M_C:
		case P_UINT64+SOMA_M_C:
		case P_UINT64+SUB_M_C:
		case P_INT64+MUL_M_C:
		case P_INT64+SOMA_M_C:
		case P_INT64+SUB_M_C:
		case P_UINT64+CMP_M_C:
		case P_INT64+CMP_M_C:
		case P_UINT64+DIV_M_C:
		case P_INT64+DIV_M_C:
			{if(t.checkUseCode(14))return 0;t.setPontCode(t.getPontCode()+14);}break;
		case P_UINT8+COPY_M_M_C:
		case P_INT8+COPY_M_M_C:
		case P_UINT16+COPY_M_M_C:
		case P_INT16+COPY_M_M_C:
		case P_UINT32+COPY_M_M_C:
		case P_INT32+COPY_M_M_C:
		case P_UINT48+COPY_M_M_C:
		case P_INT48+COPY_M_M_C:
		case P_UINT64+COPY_M_M_C:
		case P_INT64+COPY_M_M_C:
				{if(t.checkUseCode(16))return 0;t.setPontCode(t.getPontCode()+16);}break;
		default:
			std::cout << "[ERROR] - Não foi a instrução: " << p << std::endl;
			t.error_flags|=INVALID_OPCODE_JIT_;
			return 0;
		}
		if(t.checkUseCode(2))return 0;
		p=t.getNext16();
	}
	if(t.isFinalized())return 0;
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
