/*
 * JitAuxiliar.cpp
 *
 *  Created on: 25 de mai de 2019
 *      Author: lhlag
 */

#include "Jit.h"

uint32 WORKSPACE;

void definesPositionsThread(){
	Thread t;
	WORKSPACE=uint64(&t.workspace)-uint64(&t);
}

uint32 getWorkspace(){
	return WORKSPACE;
}
