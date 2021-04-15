/*
 * VMException.h
 *
 *  Created on: 17 de ago de 2020
 *      Author: lhlag
 */

#ifndef LIB_EXCEPTION_VMEXCEPTION_H_
#define LIB_EXCEPTION_VMEXCEPTION_H_

#include <bits/exception.h>
#include <string>
#include <iostream>
#include "ExceptionsStrings.h"




class VMException: public std::exception {
private:
	std::string msg;
	std::string path;
public:
	VMException(std::string mensagem=""){
		msg = mensagem;
		path = "";
	}
	virtual ~VMException(){

	}

	void addToPath(std::string str){
		if(path.length()==0)path += str;
		else path += " << "+str;
	}

	std::string getMensage(){
		return msg;
	}
	std::string getPath(){
		return path;
	}

	virtual void printError(){
		std::cout << std::endl
		<< "--------------------------------------------------" << std::endl
		<< "Path: " << getPath() << std::endl
		<< "VMException: " << getMensage() << std::endl
		<< "--------------------------------------------------" << std::endl;
	}
};


class CodeException: public VMException{
private:
	unsigned int posCode;
	std::string local;

public:
	CodeException(unsigned int posCode,std::string local,std::string mensage=""):
		VMException(mensage){
		this->posCode=posCode;
		this->local = local;
	}

	void printError(){
		std::cout << std::endl
		<< "--------------------------------------------------" << std::endl
		<< "Location: " << local << std::endl
		<< "PosCode: 0x" << posCode << std::endl
		<< "Path: " << getPath() << std::endl
		<< "CodeException: " << getMensage() << std::endl
		<< "--------------------------------------------------" << std::endl;
	}
};



#endif /* LIB_EXCEPTION_VMEXCEPTION_H_ */
