/*
 * Opcode.h
 *
 *  Created on: 14 de mar de 2019
 *      Author: Luiz Henrique
 */

#ifndef OPCODES_OPCODE_H_
#define OPCODES_OPCODE_H_

#define OP_TYPE 11 // Opcode tipo | Referente a como está sendo manipulado as variaveis (float,int,etc...)

	#define P_UINT8 (1<<OP_TYPE)
	#define P_UINT16 (2<<OP_TYPE)
	#define P_UINT32 (3<<OP_TYPE)
	#define P_UINT48 (4<<OP_TYPE)
	#define P_UINT64 (5<<OP_TYPE)
	#define P_UINT128 (6<<OP_TYPE)


	#define P_INT8 (7<<OP_TYPE)
	#define P_INT16 (8<<OP_TYPE)
	#define P_INT32 (9<<OP_TYPE)
	#define P_INT48 (10<<OP_TYPE)
	#define P_INT64 (11<<OP_TYPE)
	#define P_INT128 (12<<OP_TYPE)

	#define GERAL_TYPE (20<<OP_TYPE) // Tipo geral | Para comandos que não necessitam necessáriamente um tipo da variavel para manipular
	#define SYSTEM_CALL (21<<OP_TYPE)



#define OP_CAT 7 // Opcode categoria | Divide os comandos entre categorias de comandos para melhor organização


#define MOVIMENTACAO (00<<OP_CAT)

	#define MOV_M_C (MOVIMENTACAO+0)
	#define MOV_W_C (MOVIMENTACAO+1)
	#define MOV_M_M (MOVIMENTACAO+2)
	#define MOV_M_W (MOVIMENTACAO+3)
	#define MOV_W_W (MOVIMENTACAO+4)
	#define MOV_W_M (MOVIMENTACAO+5)

	#define MOV_MMW_C (MOVIMENTACAO+6)
	#define MOV_MMW_M (MOVIMENTACAO+7)
	#define MOV_M_MMW (MOVIMENTACAO+8)
	#define MOV_MMW_MMW (MOVIMENTACAO+9)
	#define MOV_MMW_W (MOVIMENTACAO+10)
	#define MOV_W_MMW (MOVIMENTACAO+11)

	#define CMOV_IG_W_C (MOVIMENTACAO+12)
	#define CMOV_IG_W_W (MOVIMENTACAO+13)
	#define CMOV_DI_W_C (MOVIMENTACAO+14)
	#define CMOV_DI_W_W (MOVIMENTACAO+15)
	#define CMOV_MA_W_C (MOVIMENTACAO+16)
	#define CMOV_MA_W_W (MOVIMENTACAO+17)
	#define CMOV_ME_W_C (MOVIMENTACAO+18)
	#define CMOV_ME_W_W (MOVIMENTACAO+19)
	#define CMOV_MA_IG_W_C (MOVIMENTACAO+20)
	#define CMOV_MA_IG_W_W (MOVIMENTACAO+21)
	#define CMOV_ME_IG_W_C (MOVIMENTACAO+22)
	#define CMOV_ME_IG_W_W (MOVIMENTACAO+23)

	#define MOV_MMWW_MMWW (MOVIMENTACAO+23)
	#define MOV_MMWW_C (MOVIMENTACAO+24)
	#define MOV_MMWW_W (MOVIMENTACAO+25)
	#define MOV_W_MMWW (MOVIMENTACAO+26)
	#define MOV_MMWW_M (MOVIMENTACAO+27)
	#define MOV_M_MMWW (MOVIMENTACAO+28)
	#define MOV_MMWW_MMW (MOVIMENTACAO+29)
	#define MOV_MMW_MMWW (MOVIMENTACAO+30)

	#define MOV_RRW_C (MOVIMENTACAO+31)
	#define MOV_RRW_W (MOVIMENTACAO+32)
	#define MOV_W_RRW (MOVIMENTACAO+33)
	#define MOV_RRW_RRW (MOVIMENTACAO+34)

	#define MOV_MMWW_RRW
	#define MOV_RRW_MMWW



#define ARITIMETICA (1<<OP_CAT)

	#define SOMA_M_C (ARITIMETICA+1)
	#define SOMA_W_C (ARITIMETICA+2)
	#define SOMA_W_M (ARITIMETICA+3)
	#define SOMA_W_W (ARITIMETICA+4)

	#define SUB_M_C (ARITIMETICA+5)
	#define SUB_W_C (ARITIMETICA+6)
	#define SUB_W_M (ARITIMETICA+7)
	#define SUB_W_W (ARITIMETICA+8)

	#define MUL_M_C (ARITIMETICA+9)
	#define MUL_W_C (ARITIMETICA+10)
	#define MUL_W_M (ARITIMETICA+11)
	#define MUL_W_W (ARITIMETICA+12)

	#define DIV_M_C (ARITIMETICA+13)
	#define DIV_W_C (ARITIMETICA+14)
	#define DIV_W_M (ARITIMETICA+15)
	#define DIV_W_W (ARITIMETICA+16)

	#define MOD_M_C (ARITIMETICA+17)
	#define MOD_W_C (ARITIMETICA+18)
	#define MOD_W_M (ARITIMETICA+19)
	#define MOD_W_W (ARITIMETICA+20)

	#define DD_W_C (ARITIMETICA+21)
	#define DD_W_W (ARITIMETICA+22)
	#define DE_W_C (ARITIMETICA+23)
	#define DE_W_W (ARITIMETICA+24)


	// not yet

	#define OR_W_C (ARITIMETICA+25)
	#define OR_W_M (ARITIMETICA+26)
	#define OR_W_W (ARITIMETICA+27)

	#define AND_W_C (ARITIMETICA+28)
	#define AND_W_M (ARITIMETICA+29)
	#define AND_W_W (ARITIMETICA+30)

	#define XOR_W_C (ARITIMETICA+31)
	#define XOR_W_M (ARITIMETICA+32)
	#define XOR_W_W (ARITIMETICA+33)

	#define NOT_M (ARITIMETICA+34)
	#define NOT_W (ARITIMETICA+35)



#define CONDICIONAIS_JUMPS (2<<OP_CAT)

	#define CMP_M_C (CONDICIONAIS_JUMPS+0)
	#define CMP_M_M (CONDICIONAIS_JUMPS+1)
	#define CMP_M_W (CONDICIONAIS_JUMPS+2)
	#define CMP_W_C (CONDICIONAIS_JUMPS+3)
	#define CMP_W_M (CONDICIONAIS_JUMPS+4)
	#define CMP_W_W (CONDICIONAIS_JUMPS+5)


	//JMPS GERAIS | Não necessitam um tipo especifico para estabelcer o jmp
	#define JMP_C GERAL_TYPE+(CONDICIONAIS_JUMPS+0)
	#define JMP_M GERAL_TYPE+(CONDICIONAIS_JUMPS+1)
	#define JMP_W GERAL_TYPE+(CONDICIONAIS_JUMPS+2)
	#define JMP_C_MA GERAL_TYPE+(CONDICIONAIS_JUMPS+3)
	#define JMP_C_ME GERAL_TYPE+(CONDICIONAIS_JUMPS+4)
	#define JMP_C_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+5)
	#define JMP_C_DI GERAL_TYPE+(CONDICIONAIS_JUMPS+6)
	#define JMP_C_MA_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+7)
	#define JMP_C_ME_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+8)
	#define JMP_M_MA GERAL_TYPE+(CONDICIONAIS_JUMPS+9)
	#define JMP_M_ME GERAL_TYPE+(CONDICIONAIS_JUMPS+10)
	#define JMP_M_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+11)
	#define JMP_M_DI GERAL_TYPE+(CONDICIONAIS_JUMPS+12)
	#define JMP_M_MA_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+13)
	#define JMP_M_ME_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+14)
	#define JMP_W_MA GERAL_TYPE+(CONDICIONAIS_JUMPS+15)
	#define JMP_W_ME GERAL_TYPE+(CONDICIONAIS_JUMPS+16)
	#define JMP_W_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+17)
	#define JMP_W_DI GERAL_TYPE+(CONDICIONAIS_JUMPS+18)
	#define JMP_W_MA_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+19)
	#define JMP_W_ME_IG GERAL_TYPE+(CONDICIONAIS_JUMPS+20)
	/*
	 *  MA = Caso o 1º parametro seja maior que o 2º
	 *  1>2
	 *  ME = Caso o 1º parametro seja menor que o 2º
	 *  1<2
	 *  IG = Caso o 1º parametro seja igual ao 2º
	 *  1==2
	 *  DI = Caso o 1º parametro seja diferente ao 2º
	 *  1!=2
	 *  MA_IG = Caso o 1º parametro seja maior ou igual ao 2º
	 *  1>=2
	 *  ME_IG = Caso o 1º parametro seja menor ou igual ao 2º
	 *  1<=2
	 */



#define OPTMIZACAO (3<<OP_CAT)
	//optimizações de todos os tipos
	#define COPY_M_M_C (OPTMIZACAO+0)
	#define COPY_M_M_W (OPTMIZACAO+1)
	#define COPY_MW_MW_C (OPTMIZACAO+2)
	#define COPY_MW_MW_W (OPTMIZACAO+3)

	//optimizações especificas


	//Optimização geral
	#define LOOP_C_W GERAL_TYPE+(OPTMIZACAO+0)
	#define LOOP_W_W GERAL_TYPE+(OPTMIZACAO+1)
	#define INC_W GERAL_TYPE+(OPTMIZACAO+2)
	#define DEC_W GERAL_TYPE+(OPTMIZACAO+3)
	#define INC_M GERAL_TYPE+(OPTMIZACAO+4)
	#define DEC_M GERAL_TYPE+(OPTMIZACAO+5)
	#define LEA_W__W_W_C GERAL_TYPE+(OPTMIZACAO+6)
	#define LEA_W__W_W_W GERAL_TYPE+(OPTMIZACAO+7)
	#define LEA_W__W_W_1 GERAL_TYPE+(OPTMIZACAO+8)
	#define LEA_W__W_W_2 GERAL_TYPE+(OPTMIZACAO+9)
	#define LEA_W__W_W_4 GERAL_TYPE+(OPTMIZACAO+10)
	#define LEA_W__W_W_8 GERAL_TYPE+(OPTMIZACAO+11)
	#define LEA_W__W_W_16 GERAL_TYPE+(OPTMIZACAO+12)
	#define LEA_W__W_W_32 GERAL_TYPE+(OPTMIZACAO+13)
	#define LEA_W__W_W_64 GERAL_TYPE+(OPTMIZACAO+14)

	#define JIT_FLAG_START GERAL_TYPE+(OPTMIZACAO+15)
	#define JIT_FLAG_END GERAL_TYPE+(OPTMIZACAO+16)
	#define JIT_FLAG_EXECUTE GERAL_TYPE+(OPTMIZACAO+17)
	#define JIT_FLAG_ENTER_CODE GERAL_TYPE+(OPTMIZACAO+18)



#define STACK (4<<OP_CAT)

	#define CALL_C GERAL_TYPE+(STACK+0) //Chama uma função a partir de um local de memoria de codigo contstante
	#define CALL_W GERAL_TYPE+(STACK+1)//Chama uma função a partir de um local de memoria de codigo de acordo com um slot da workspace
	#define CALL_M GERAL_TYPE+(STACK+2)//Chama uma função a partir de um local de memoria de codigo de acordo com um local da memoria
	#define RETURN GERAL_TYPE+(STACK+3)//Retorna; caso tenha sido executado o call ele retorna para a proxima instrução depois do call. Erro ao usar sem ser chamado o call.

	#define PUSH_W GERAL_TYPE+(STACK+4)//Envia um valor de acordo com um slot da workspace para a stack
	#define PUSH_C GERAL_TYPE+(STACK+5)//Envia um valor de acordo com uma constante para a stack
	#define POP_W GERAL_TYPE+(STACK+6)//Pega o valor no topo da stack e armazena na workspace

	#define CALL_CTX_C GERAL_TYPE+(STACK+7)//Chama uma função a partir de um local de memoria de codigo constante de outro contexto
	#define CALL_CTX_W GERAL_TYPE+(STACK+8)//Chama uma função a partir de um local de memoria de codigo de acordo com um slot da workspace de outro contexto


//System Call commands
	#define PRINT_OUT_CHAR SYSTEM_CALL+1 //Printa o char da workspace
	#define PRINT_OUT_NUM SYSTEM_CALL+2  //Printa o num da workspace
	#define PRINT_OUT_STRING_MMW SYSTEM_CALL+3 //Printa a string do ponteiro da workspace
	#define PRINT_OUT_STRING_M SYSTEM_CALL+4 //Printa a string do ponteiro da workspace
	#define LOAD_CONTEXT SYSTEM_CALL+5 //Carrega contexto
	#define GET_CONTEXT_ID SYSTEM_CALL+6 //Retorna o id do contexto
	#define CHECK_CONTEXT_ID SYSTEM_CALL+7 //Confere o id do contexto, caso falso, zera a variavel passada como parametro
	#define HLT_COMAND SYSTEM_CALL+8


	#define ALLOC_RES SYSTEM_CALL+128
	#define FREE_RES SYSTEM_CALL+129

#endif /* OPCODES_OPCODE_H_ */

