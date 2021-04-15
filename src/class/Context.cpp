/*
 * Context.cpp
 *
 *  Created on: 10 de abr de 2019
 *      Author: lhlag
 */
#include "Context.h"
#include "../opcodes/WordCoder/VERSION.h"


Context::Context(VirtualMachine* vm,uint16 codi,uint8* binaryCode,uint32 len){
	mem=new uint8[MEMORY_BASE_CONTEXT*2];
	max_mem=MEMORY_BASE_CONTEXT*2;
	for(uint64 x=0;x<max_mem;x++){
		mem[x]=0;
	}
	cod=NULL;
	cod_len=0;
	id=0;
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

void Context::clearFunctions(JitRuntime& rm){
	for (auto it=functions.begin(); it!=functions.end(); ++it){
		rm.release(it->second);
	}
	functions.clear();

}
char Context::printVisibleName(){
	if(nome_visivel!=NULL)std::cout << "[" << nome_visivel;
	else if(nome_geral!=NULL)std::cout << "[" << nome_geral;
	else std::cout << "[CTX:"<< id;
	return ']';
}

void Context::prepare(uint16 codi,uint8 *binaryCode,uint32 len){
	id=codi;
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
			std::cout << "[ERROR] -" << printVisibleName()<< "- Tamanho de cabeçalho invalido para o que foi passado no Context;" <<  std::endl;
		}else if(versao>VERSION_VM){
			std::cout << "[ERROR] -" << printVisibleName()<< "- Carregado sorcecode de versão maior que a VM atual. Informações de cabeçalho não puderam ser adicionadas." << std::endl;
			std::cout << "[ERROR] -" << printVisibleName()<< "- VM Version: " << VERSION_VM << " | Sorce Code Version: " << versao << std::endl;
			len-=tam_header+9;
		}else{
			std::cout << "[INFO] -" << printVisibleName()<< "- Compatibilidade: " << versao << "V(" << uint32(correcao) << ")" << std::endl;
			uint16 dados=*((uint16*)binaryCode);
			binaryCode+=2;
			while(dados-->0){
				uint16 l=*((uint16*)binaryCode);
				binaryCode+=2;
				switch(l){
				case COD_DEV_VERSION:
					devVersion=*((uint64*)binaryCode);
					binaryCode+=8;
					std::cout << "[INFO] -" << printVisibleName() << "- Versão Software: " << devVersion << std::endl;
					break;
				case COD_NOME_GERAL:{
					char *c=(char*)binaryCode;
					uint32 auxt=strlen(c);
					binaryCode+=auxt+1;
					std::cout << "[INFO] -" << printVisibleName() << "- Nome completo: " << c << std::endl;
					nome_geral=new char[auxt+1];
					strcpy(nome_geral,c);
					}break;
				case COD_NOME_VISIVEL:{
					char *c=(char*)binaryCode;
					uint32 auxt=strlen(c);
					binaryCode+=auxt+1;
					std::cout << "[INFO] -" << printVisibleName() << "- Nome visivel: " << c << std::endl;
					nome_visivel=new char[auxt+1];
					strcpy(nome_visivel,c);
					}break;
				default:
					std::cout << "[ERROR] -" << printVisibleName()<< "- Código de cabeçalho não encontrado: " << l << std::endl;
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


inline void Context::set16InCode(uint32 pont,uint16 val){
	if(pont>=cod_len)return;
	register uint16* x=((uint16*)(&cod[pont]));
	*x=val;
}

inline void Context::set32InCode(uint32 pont,uint32 val){
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
	functions.clear();
	delete[] cod;
	delete[] mem;
	if(nome_visivel!=NULL)delete[] nome_visivel;
	if(nome_geral!=NULL)delete[] nome_geral;
}
