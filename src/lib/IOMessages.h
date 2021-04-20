/*
 * IOMessages.h
 *
 *  Created on: 16 de abr. de 2021
 *      Author: lhlag
 */

#ifndef LIB_IOMESSAGES_H_
#define LIB_IOMESSAGES_H_


	#include <sstream>
	#include "Types.h"



	#define OUT_LOG 1
	#define OUT_ERROR 2
	#define OUT_INFO 3
	//Debug definido em 1
	#define OUT_SUCESS 4
	#define OUT_WARNING 5
	//Debug definido em 2
	#define OUT_INFO_EXTRA 6
	#define OUT_LOG_EXTRA 7
	//Debug definido em 3
	#define OUT_DEBUG 8


	void printMessage(uint8 debug,uint8 type,char *str);
	void printMessage(uint8 debug,uint8 type,std::stringstream& os);


#endif /* LIB_IOMESSAGES_H_ */
