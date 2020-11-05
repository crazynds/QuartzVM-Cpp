/*
 * Memory.h
 *
 *  Created on: 17 de ago de 2020
 *      Author: lhlag
 */

#ifndef SRC_MEMORY_H_
#define SRC_MEMORY_H_

#define DATABASE_MEMORY_HANDLER
#include "exception/VMException.h"
#include <stdio.h>
#include <string>

void _new_handler_memory_fault();

void start();

#ifdef DATABASE_MEMORY_HANDLER


	#ifndef _MEMORYMANAGEMENT_MEMORYHANDLER_H_
	#define _MEMORYMANAGEMENT_MEMORYHANDLER_H_

	inline void* mrealloc(void* p,unsigned long long int t){
		void *ptr;
		while((ptr=std::realloc(p,t))==NULL)
			_new_handler_memory_fault();
		return ptr;
	}


	inline void* mcalloc(unsigned long long int t,unsigned long long int t2){
		void *ptr;
		while((ptr=std::calloc(t,t2))==NULL)
			_new_handler_memory_fault();
		return ptr;
	}
	inline void* mmalloc(unsigned long long int t){
		void *ptr;
		while((ptr=std::malloc(t))==NULL)
			_new_handler_memory_fault();
		return ptr;
	}
	#endif


#else

	#define mmalloc(A) malloc(A)
	#define mcalloc(A) calloc(A,1)
	#define mrealloc(A,B) realloc(A,B)

#endif



#endif /* SRC_CLASS_MEMORY_H_ */
