/*
 * CodeLoader.h
 *
 *  Created on: 1 de abr de 2019
 *      Author: lhlag
 */

#ifndef SRC_CODELOADER_H_
#define SRC_CODELOADER_H_

#include "../lib/Types.h"
#define TAM_READ 2048

class FileLoader {
	private:
		uint8 *code;
		uint32 tam;
	public:
		FileLoader(char *a,uint8 debug){
			FILE *arq;
			if(debug>1)printf("[INFO] - Iniciando a busca do arquivo!\n");
			arq = fopen(a, "rb");
			if (arq == NULL){
				printf("[ERROR] - Arquivo '%s' não encontrado!\n",a);
				tam=0;
				code=NULL;
				return;
			}
			fseek(arq, 0, 2);
			tam = ftell(arq);
			code = new uint8[tam];
			fseek(arq,0,SEEK_END);
			fseek(arq,0,SEEK_SET);
			fread(code,1,tam,arq);
			if(debug>1)printf("[INFO] - Arquivo carregado com sucesso!\n");
		}


		~FileLoader(){
			if(code!=NULL)delete[] code;
		}

		uint8* getCode(){
			return code;
		}

		uint32 getTam(){
			return tam;
		}

};

#endif /* SRC_CODELOADER_H_ */
