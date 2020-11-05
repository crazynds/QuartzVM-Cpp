/*
 * Memory.cpp
 *
 *  Created on: 17 de ago de 2020
 *      Author: lhlag
 */
#include "Memory.h"



void start(){
	std::set_new_handler(_new_handler_memory_fault);
}
void _new_handler_memory_fault(){
	std::string s="Erro ao tentar reservar espaço em RAM!";
	VMException mem=VMException(s);
	throw mem;
}

