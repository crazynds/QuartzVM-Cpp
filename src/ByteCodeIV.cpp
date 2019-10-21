//============================================================================
// Name        : ByteCodeIV.cpp
// Author      : Luiz Henrique Broch Lago
// Version     : 0.02.020
// Copyright   : Nextline
// Description :
//============================================================================

#include "class/VirtualMachine.h"
#include "lib/Types.h"
#include "class/Contexto.h"
#include "class/CodeLoader.h"
#include <ctime>
#include <iostream>
#include <algorithm>

#define DEBUG 0

using namespace std;


int main(int argc, char **argv) {
	VirtualMachine *vm;
	uint8 debug=0;
	FileLoader *c;
	cout << "$$$$$ INICIANDO $$$$$" << endl;
	{
		if(argc>1)c=new FileLoader(argv[1],DEBUG);
		else c=new FileLoader((char*)"../codes/code.bt",DEBUG);
		if(c->getTam()==0){
			cout << "[ERROR] - Não foi possivel carregar o código, máquina virtual desligando!";
			getchar();
			return 0;
		}
	}
	{
		if(argc>2)for(int x=0;argv[2][x]!='\0';x++){
			if(argv[2][x]=='g' || argv[2][x]=='G'){
				debug=1;
			}
		}
	}
	{
		vm=new VirtualMachine(DEBUG);
		uint16 context=vm->loadContexto(c->getCode(),c->getTam());
		vm->createThread(context,0);
	}
	delete c;
	{
		clock_t max=clock();
		uint8 flag;
		if(debug){
			while(!flag)flag=vm->runCommand();
		}else flag=vm->run();
		cout<<"[INFO] - Duração total: "<< ( clock() - max )/(double)CLOCKS_PER_SEC << endl;
	}


	delete vm;
	getchar();
	return 0;
}
