/*
 * Context.cpp
 *
 *  Created on: 10 de abr de 2019
 *      Author: lhlag
 */
#include "../lib/IOMessages.h"
#include "Context.h"
#include "../opcodes/WordCoder/VERSION.h"

#define PRINT_MESSAGE(type,str) {std::stringstream os;os << "[" << visibleName() << "] - " << str;printMessage(vm->getDebugLevel(),type,os);}


Context::Context(VirtualMachine* vm,uint16 id,uint8* binaryCode,uint32 len){
	mem=NULL;
	max_mem=0;

	this->id=id;
	this->vm=vm;

	cod=NULL;
	cod_len=0;
	versao=0;
	correcao=0;
	devVersion=0;
	nome_visivel=NULL;
	nome_geral=NULL;
	try{
		prepare(binaryCode,len);
	}catch(VMException &e){
		e.addToPath("CONTEXT_CONTRUCTOR");
		throw;
	}

	PRINT_MESSAGE(OUT_LOG,"Context carregado completamente");
}
Context::Context(){
	mem=NULL;
	max_mem=0;
	id=0;

	this->vm=NULL;
	cod=NULL;
	cod_len=0;
	versao=0;
	correcao=0;
	devVersion=0;
	nome_visivel=NULL;
	nome_geral=NULL;
}

uint16 Context::getCodContext(){
	return id;
}

FuncJit& Context::createFunction(uint32 posMem){
	functions[posMem] = FuncJit();
	return functions[posMem];
}

FuncJit Context::getFunction(uint32 mem){
	std::map<uint32,FuncJit>::iterator it = functions.find(mem);
	if(it!=functions.end())
		return it->second;
	else return 0;
}

void Context::clearFunctions(){
	JitRuntime& rm = vm->getManagerOpcodes().getJitRuntime();
	for (auto it=functions.begin(); it!=functions.end(); ++it){
		rm.release(it->second);
	}
	functions.clear();

}
std::string Context::visibleName(){
	if(nome_visivel!=NULL)return std::string(nome_visivel);
	else if(nome_geral!=NULL)return std::string(nome_geral);
	return std::string("CTX:")+std::to_string(id);
}

void Context::prepare(uint8 *binaryCode,uint32 len){
	mem=new uint8[MEMORY_BASE_CONTEXT+128];
	max_mem=MEMORY_BASE_CONTEXT;
	memset(mem,0,max_mem);
	if(*((uint16*)binaryCode)==0){
		uint8 *bck=binaryCode;
		uint32 tam_header;
		binaryCode+=2;
		versao=*((uint16*)binaryCode);
		binaryCode+=2;
		correcao=*((uint8*)binaryCode);
		binaryCode++;
		tam_header=*((uint32*)binaryCode);
		binaryCode+=4;
		if(tam_header>=len-9){
			PRINT_MESSAGE(OUT_ERROR,"Tamanho de cabeçalho invalido para o que foi passado no Context");
		}else if(versao>VERSION_VM){
			PRINT_MESSAGE(OUT_ERROR,"Carregado sorcecode de versão maior que a VM atual. Por questões de segurança informações de cabeçalho não serão adicionadas");
			PRINT_MESSAGE(OUT_ERROR,"VM Version: " << VERSION_VM << " | Sorce Code Version: " << versao);
			len-=tam_header+9;
		}else{
			PRINT_MESSAGE(OUT_INFO,"Compatibilidade: " << versao << "V(" << uint32(correcao) << ")");
			uint16 dados=*((uint16*)binaryCode);
			binaryCode+=2;
			while(dados-->0){
				uint16 l=*((uint16*)binaryCode);
				binaryCode+=2;
				switch(l){
				case COD_DEV_VERSION:
					devVersion=*((uint64*)binaryCode);
					binaryCode+=8;
					PRINT_MESSAGE(OUT_INFO,"Versão Software: " << devVersion);
					break;
				case COD_NOME_GERAL:{
					char *c=(char*)binaryCode;
					uint32 auxt=strlen(c);
					binaryCode+=auxt+1;
					PRINT_MESSAGE(OUT_INFO,"Nome completo: " << c);
					nome_geral=new char[auxt+1];
					strcpy(nome_geral,c);
					}break;
				case COD_NOME_VISIVEL:{
					char *c=(char*)binaryCode;
					uint32 auxt=strlen(c);
					binaryCode+=auxt+1;
					PRINT_MESSAGE(OUT_INFO,"Nome visivel: " << c);
					nome_visivel=new char[auxt+1];
					strcpy(nome_visivel,c);
					}break;
				default:
					PRINT_MESSAGE(OUT_INFO,"Código de cabeçalho não encontrado: " << l);
				}

			};
			len-=uint32(uint64(binaryCode)-uint64(bck));
		}
		binaryCode=bck;
		cod=new uint8[len];
		while(cod_len<len){
			cod[cod_len]=binaryCode[9+tam_header+cod_len];
			cod_len++;
		}
	}else{
		throw VMException(_LOAD_CONTEXT_NOT_VALID_STR);
	}
}


void Context::set16InCode(uint32 pont,uint16 val){
	if(pont>=cod_len)return;
	register uint16* x=((uint16*)(&cod[pont]));
	*x=val;
}

void Context::set32InCode(uint32 pont,uint32 val){
	if(pont>=cod_len)return;
	register uint32* x=((uint32*)(&cod[pont]));
	*x=val;
}

uint8* Context::getMemoryDataDataPointer(){
	return mem;
}
uint48 Context::getMemoryDataSize(){
	return max_mem;
}

const uint8* Context::getCodeDataPointer(){
	return cod;
}
uint32 Context::getCodeDataSize(){
	return cod_len;
}

Context::~Context(){
	clearFunctions();
	delete[] cod;
	delete[] mem;
	if(nome_visivel!=NULL)delete[] nome_visivel;
	if(nome_geral!=NULL)delete[] nome_geral;
}
