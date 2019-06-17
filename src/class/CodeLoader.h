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
		FileLoader(char *a){
			FILE *arq;
			uint8 *vet;
			printf("[INFO] - Iniciando a busca do arquivo!\n");
			vet=new uint8[TAM_READ];
			uint32 max=0;
			uint32 res;
			arq = fopen(a, "rb");
			if (arq == NULL){
				printf("[ERROR] - Arquivo '%s' não encontrado!\n",a);
				tam=0;
				code=NULL;
				return;
			}
			printf("[SUCESS] - Arquivo '%s' encontrado!\n",a);
			res = fread (vet, sizeof(uint8), TAM_READ, arq);
			max+=res;
			while(res==TAM_READ){
				uint8 *p=new uint8[max+TAM_READ];
				for(uint32 x=0;x<max;x++){
					p[x]=vet[x];
				}
				delete[] vet;
				vet=p;
				res = fread (&vet[max], sizeof(uint8), TAM_READ, arq);
				max+=res;
			}
			fclose(arq);

			tam=max;
			code=vet;
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
