/*
 * Vectorable.h
 *
 *  Created on: 15 de mar de 2019
 *      Author: lhlag
 */

#ifndef LIB_VECTORABLE_H_
#define LIB_VECTORABLE_H_

	#include <iostream>
	#include "Types.h"


	#define TAM_INCREMENTO_VET 4

	template <class T,class P>
	class Dupla{
		private:
			T *ti;
			P pi;

		public:

			inline void setFirst(T *t){
				ti=t;
			}
			inline void setSecond(P p){
				pi=p;
			}

			inline T& getFirst(){
				return *ti;
			}
			inline P& getSecond(){
				return pi;
			}

	};



#endif /* LIB_VECTORABLE_H_ */
