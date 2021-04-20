/*
 * IOMessages.cpp
 *
 *  Created on: 16 de abr. de 2021
 *      Author: lhlag
 */
#include "IOMessages.h"
#include "Types.h"
#include <stdlib.h>


void printMessage(uint8 debug,uint8 type,char *str){
	std::string s(str);
	switch(type){
	case OUT_INFO:
		std::cout << "[INFO] - "<<s  << std::endl;
		break;
	case OUT_LOG:
		std::cout << "[LOG] - "<<s  << std::endl;
		break;
	case OUT_ERROR:
		std::cout << "[ERROR] - "<<s  << std::endl;
		break;
	case OUT_WARNING:
		if(debug<1)return;
		std::cout << "[WARNING] - "<<s << std::endl;
		break;
	case OUT_SUCESS:
		if(debug<1)return;
		std::cout << "[SUCESS] - "<<s << std::endl;
		break;
	case OUT_INFO_EXTRA:
		if(debug<2)return;
		std::cout << "[INFO] - "<<s << std::endl;
		break;
	case OUT_LOG_EXTRA:
		if(debug<2)return;
		std::cout << "[LOG] - "<<s << std::endl;
		break;
	case OUT_DEBUG:
		if(debug<3)return;
		std::cout << "[DEBUG] - "<<s << std::endl;
		break;
	}
}

void printMessage(uint8 debug,uint8 type,std::stringstream& os){
	std::string s = os.str();
	switch(type){
	case OUT_INFO:
		std::cout << "[INFO] - "<<s  << std::endl;
		break; // Awails show
	case OUT_LOG:
		std::cout << "[LOG] - "<<s  << std::endl;
		break;
	case OUT_ERROR:
		std::cout << "[ERROR] - "<<s  << std::endl;
		break;
	case OUT_WARNING:
		if(debug<1)return;
		std::cout << "[WARNING] - "<<s << std::endl;
		break;
	case OUT_SUCESS:
		if(debug<1)return;
		std::cout << "[SUCESS] - "<<s << std::endl;
		break;
	case OUT_INFO_EXTRA:
		if(debug<2)return;
		std::cout << "[INFO] - "<<s << std::endl;
		break;
	case OUT_LOG_EXTRA:
		if(debug<2)return;
		std::cout << "[LOG] - "<<s << std::endl;
		break;
	case OUT_DEBUG:
		if(debug<3)return;
		std::cout << "[DEBUG] - "<<s << std::endl;
		break;
	}
}
