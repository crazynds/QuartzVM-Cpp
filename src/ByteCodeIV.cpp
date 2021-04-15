//============================================================================
// Name        : ByteCodeIV.cpp
// Author      : Luiz Henrique Broch Lago
// Version     : 0.02.020
// Copyright   : Nextline
// Description :
//============================================================================

#include "lib/Types.h"
#include "class/Context.h"
#include "class/CodeLoader.h"
#include "class/VirtualMachine/VirtualMachine.h"

#include <ctime>
#include <iostream>
#include <algorithm>

#define DEBUG 3

using namespace std;



typedef int (*Function)(void);


int main(int argc, char **argv) {
	VirtualMachine *vm;
	uint8 debug=3;
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
		uint16 context=vm->loadContext(c->getCode(),c->getTam());
		vm->createThread(context,0);
	}
	delete c;
	{
		clock_t max=clock();
		uint64 flag=0;
		flag=vm->run();
		cout<<"[INFO] - Duração total: "<< ( clock() - max )/(double)CLOCKS_PER_SEC << endl;
	}


	delete vm;
	return 0;

	/*
	JitRuntime rt;
	Function fn1,fn2;
	uint64_t position;

	{
		//First function X
		CodeHolder code;
		code.init(rt.environment());
		Assembler a(&code);
		Label label = a.newLabel();
		a.xor_(rax,rax);
		a.bind(label);
		a.inc(rax);
		a.ret();
		Error err = rt.add(&fn1, &code);
		position = fn1+code.labelOffset(label); //Function address + offset position
		if (err) return 1;
	}

	{
		//Second function Y
		CodeHolder code;
		code.init(rt.environment());
		Assembler a(&code);
		a.mov(rax,2);
		a.jmp(position);
		Error err = rt.add(&fn2, &code);
		if (err) return 1;
	}


	int result = fn2();
	printf("%d\n", result);

	rt.release(fn1);
	rt.release(fn2);
	 */

}
