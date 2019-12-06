/*
 * OpcodesFuncs.cpp
 *
 *  Created on: 2 de mar de 2019
 *      Author: lhlag
 */

#include "../../../class/Thread.h"
#include <iostream>
#include <ctime>

void end_running(Thread &t){
	//Define a flag running como off;
	t.error_flags|=RUNNING_;
}

void do_nothing(Thread &t){
	__asm("nop\n\
		   nop\n\
		   nop\n\
		   nop");
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif
}

void sleep(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint64 p=t.recoverInStack();
	if(p&((uint64)1<<63)){
		p^=(uint64)1<<63;
		if(( clock() - p )/(double)(CLOCKS_PER_SEC/1000)>t.getNext32())return;
		t.saveInStack(p|(uint64)1<<63);
		t.setPontCode(t.getPontCode()-6);
	}else{
		t.setPontCode(t.getPontCode()-2);
		t.saveInStack(p|(uint64)1<<63);
	}
}

void no_opcode(Thread &t){
	t.error_flags|=NO_OPCODE_COMMAND_;
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif
}

void test_func(Thread &t){
	std::cout << "[DEBUG] - MEMORY {" << (int16)t.mem[0];
	for(int p=1;p<35;p++)std::cout << "," << (int16)t.mem[p] ;
	std::cout << "}" << std::endl;
	//for(int p=0;p<20;p++)std::cout << std::bitset<8>(t.workspace[p]) << " \n";

	std::cout << "[DEBUG] - WORKSP {"<< (uint64)t.workspace[0];
	for(int p=1;p<20;p++)std::cout<< "," << (uint64)t.workspace[p];
	std::cout << "}" << std::endl;

#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif
}

/*
 * PARA FUNÇÕES PADRÕES, CHECAR ANTES DE INICIAR O CODIGO SE EXISTE MEMORIA VALIDA SUFICIENTE PARA EXECUTAR O MOVIMENTO
 *
 * ex: getNext32(4) + getNext48(6)
 *    final: 4+6+2
 *
 *
 */



