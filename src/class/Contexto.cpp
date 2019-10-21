/*
 * Contexto.cpp
 *
 *  Created on: 10 de abr de 2019
 *      Author: lhlag
 */
#include "Contexto.h"
#include "../opcodes/WordCoder/VERSION.h"


Contexto::Contexto(){
	mem=new uint8[MEMORY_BASE_CONTEXT*2];
	max_mem=MEMORY_BASE_CONTEXT*2;
	for(uint64 x=0;x<max_mem;x++){
		mem[x]=0;
	}
	cod=NULL;
	cod_len=0;
	cod_ctx=0;
	funcs.resize(0);
	versao=0;
	correcao=0;
	devVersion=0;
	nome_visivel=NULL;
	nome_geral=NULL;
}

uint16 Contexto::getCodContext(){
	return cod_ctx;
}

FuncJit Contexto::getFunction(uint32 mem){
	uint64 index=(uint64)~0;
	for(uint64 x=0;x<funcs.size();x++){
		if(funcs[x].getSecond()==mem)index=x;
	}
	if(index==(uint64)~0)return (FuncJit)0;
	return funcs[index].getFirst();
}
FuncJit& Contexto::createFunction(uint32 posMem){
	funcs.resize(funcs.size()+1);
	uint64 val=funcs.size()-1;

	funcs[val].setSecond(posMem);
	funcs[val].setFirst(new FuncJit());
	return funcs[val].getFirst();
}

void Contexto::clearFunctions(JitRuntime& rm){
	for(uint64 y=0;y<funcs.size();y++){
		rm.release(funcs[y].getFirst());
		delete &funcs[y].getFirst();
	}
	funcs.clear();
}
char Contexto::printVisibleName(){
	if(nome_visivel!=NULL)std::cout << "[" << nome_visivel;
	else if(nome_geral!=NULL)std::cout << "[" << nome_geral;
	else std::cout << "[CTX:"<< cod_ctx;
	return ']';
}

void Contexto::prepare(uint16 codi,uint8 *rep,uint32 len){
	cod_ctx=codi;
	if(*((uint16*)rep)==0){
		uint8 *bck=rep;
		uint32 tam_header;
		rep+=2;
		versao=*((uint16*)rep);
		rep+=2;
		correcao=*((uint8*)rep);
		rep++;
		tam_header=*((uint32*)rep);
		rep+=4;
		if(tam_header>=len-9){
			std::cout << "[ERROR] -" << printVisibleName()<< "- Tamanho de cabeçalho invalido para o que foi passado no contexto;" <<  std::endl;
		}else if(versao>VERSION_VM){
			std::cout << "[ERROR] -" << printVisibleName()<< "- Carregado sorcecode de versão maior que a VM atual. Informações de cabeçalho não puderam ser adicionadas." << std::endl;
			std::cout << "[ERROR] -" << printVisibleName()<< "- VM Version: " << VERSION_VM << " | Sorce Code Version: " << versao << std::endl;
			len-=tam_header+9;
		}else{
			std::cout << "[INFO] -" << printVisibleName()<< "- Compatibilidade: " << versao << "V(" << uint32(correcao) << ")" << std::endl;
			uint16 dados=*((uint16*)rep);
			rep+=2;
			while(dados-->0){
				uint16 l=*((uint16*)rep);
				rep+=2;
				switch(l){
				case COD_DEV_VERSION:
					devVersion=*((uint64*)rep);
					rep+=8;
					std::cout << "[INFO] -" << printVisibleName() << "- Versão Software: " << devVersion << std::endl;
					break;
				case COD_NOME_GERAL:{
					char *c=(char*)rep;
					uint32 auxt=strlen(c);
					rep+=auxt+1;
					std::cout << "[INFO] -" << printVisibleName() << "- Nome completo: " << c << std::endl;
					nome_geral=new char[auxt+1];
					strcpy(nome_geral,c);
					}break;
				case COD_NOME_VISIVEL:{
					char *c=(char*)rep;
					uint32 auxt=strlen(c);
					rep+=auxt+1;
					std::cout << "[INFO] -" << printVisibleName() << "- Nome visivel: " << c << std::endl;
					nome_visivel=new char[auxt+1];
					strcpy(nome_visivel,c);
					}break;
				default:
					std::cout << "[ERROR] -" << printVisibleName()<< "- Código de cabeçalho não encontrado: " << l << std::endl;
				}

			};
			len-=uint32(uint64(rep)-uint64(bck));
		}
		rep=bck;
		cod=new uint8[len];
		while(cod_len<len){
			cod[cod_len]=rep[9+tam_header+cod_len];
			cod_len++;
		}
	}else{
		std::cout << "[INFO] -" << printVisibleName() << "- Contexto sem cabeçalho." << std::endl;
		cod=new uint8[len];
		while(cod_len<len){
			cod[cod_len]=rep[cod_len];
			cod_len++;
		}
	}
}
void Contexto::incrementMemory(){
	uint8 *aux=new uint8[max_mem+MEMORY_BASE_CONTEXT];
	for(uint64 x=0;x<max_mem;x++)aux[x]=mem[x];
	delete[] mem;
	mem=aux;
	max_mem+=MEMORY_BASE_CONTEXT;
}
void Contexto::freeMemory(uint48 i){
	uint64 a=i.toInt();
	if(a>=max_mem)return;
	uint64 y=(a/MEMORY_BASE_CONTEXT)+1;
	if(y>=max_mem/MEMORY_BASE_CONTEXT)return;
	uint8 *aux=new uint8[y*MEMORY_BASE_CONTEXT];
	max_mem=y*MEMORY_BASE_CONTEXT;
	for(uint64 x=0;x<max_mem;x++)aux[x]=mem[x];
	delete[] mem;
	mem=aux;
}


Contexto::~Contexto(){
	funcs.clear();
	delete[] cod;
	delete[] mem;
	if(nome_visivel!=NULL)delete[] nome_visivel;
	if(nome_geral!=NULL)delete[] nome_geral;
}
