/*
* Wordcoder.cpp
*
*  Created on: 17 de jun de 2019
*      Author: lhlag
*/

#include "Wordcoder.h"


void Wordcoder::mov(GeralMemory *g1,GeralMemory *g2){
	switch(g1->getType()){
	case 'I':{
		std::cout << "WordCoder: Não é possivel usar valor estatico como destino de comando!" << std::endl;
	}break;
	case 'm':{
		Memoria *m1=(Memoria*)g1;
		switch(g2->getType()){
			case 'I':{
				ImediateData *im=(ImediateData*)g2;
				mov_m_c(m1->getPos(),im->getValue());
			}break;
			case 'm':{
				Memoria *m2=(Memoria*)g2;
				mov_m_m(m1->getPos(),m2->getPos());
			}break;
			case 'M':{
				std::cout << "WordCoder: Ainda não disponivel o uso do comando  'mov m <- mmww'" << std::endl;
			}break;
			case 'P':{
				MemoriaPtr *m2=(MemoriaPtr*)g2;
				mov_m_mmw(m1->getPos(),m2->getPosBase(),m2->getIncrement());
			}break;
			case 'W':{
				Workspace *w2=(Workspace*)g2;
				mov_m_w(m1->getPos(),w2->getPos());
			}break;
		}
	}break;
	case 'M':{
		MemoriaPtr*mp1=(MemoriaPtr*)g1;
		switch(g2->getType()){
			case 'I':{
				ImediateData *im2=(ImediateData*)g2;
				mov_mmww_c(mp1->getPosBase(),mp1->getPosIndex(),mp1->getShift(),mp1->getIncrement(),im2->getValue());
			}break;
			case 'm':{
				std::cout << "WordCoder: Ainda não disponivel o uso do comando  'mov mmww <- m'" << std::endl;
			}break;
			case 'M':{
				MemoriaPtr *m2=(MemoriaPtr*)g2;
				mov_mmww_mmww(mp1->getPosBase(),mp1->getPosIndex(),mp1->getShift(),mp1->getIncrement(),m2->getPosBase(),m2->getPosIndex(),m2->getShift(),m2->getIncrement());
			}break;
			case 'P':{
				std::cout << "WordCoder: Ainda não disponivel o uso do comando  'mov mmww <- mmw' (Nem vai estar)" << std::endl;
			}break;
			case 'W':{
				Workspace *w2=(Workspace*)g2;
				mov_mmww_w(mp1->getPosBase(),mp1->getPosIndex(),mp1->getShift(),mp1->getIncrement(),w2->getPos());
			}break;
		}
	}break;
	case 'P':{
		MemoriaPtr*mp1=(MemoriaPtr*)g1;
		switch(g2->getType()){
			case 'I':{
				ImediateData *im2=(ImediateData*)g2;
				mov_mmw_c(mp1->getPosBase(),mp1->getIncrement(),im2->getValue());
			}break;
			case 'm':{
				Memoria *m2=(Memoria*)g2;
				mov_mmw_m(mp1->getPosBase(),mp1->getIncrement(),m2->getPos());
			}break;
			case 'M':{
				std::cout << "WordCoder: Ainda não disponivel o uso do comando  'mov mmw <- mmww' (Nem vai estar)" << std::endl;
			}break;
			case 'P':{
				MemoriaPtr *m2=(MemoriaPtr*)g2;
				mov_mmw_mmw(mp1->getPosBase(),mp1->getIncrement(),m2->getPosBase(),m2->getIncrement());
			}break;
			case 'W':{
				Workspace *w2=(Workspace*)g2;
				mov_mmw_w(mp1->getPosBase(),mp1->getIncrement(),w2->getPos());
			}break;
		}
	}break;
	case 'W':{
		Workspace *w1=(Workspace*)g1;
		switch(g2->getType()){
			case 'I':{
				ImediateData *im2=(ImediateData*)g2;
				mov_w_c(w1->getPos(),im2->getValue());
			}break;
			case 'm':{
				Memoria *m2=(Memoria*)g2;
				mov_w_m(w1->getPos(),m2->getPos());
			}break;
			case 'M':{
				MemoriaPtr *m2=(MemoriaPtr*)g2;
				mov_w_mmww(w1->getPos(),m2->getPosBase(),m2->getPosIndex(),m2->getShift(),m2->getIncrement());
			}break;
			case 'P':{
				MemoriaPtr *m2=(MemoriaPtr*)g2;
				mov_w_mmw(w1->getPos(),m2->getPosBase(),m2->getIncrement());
			}break;
			case 'W':{
				Workspace *w2=(Workspace*)g2;
				mov_w_w(w1->getPos(),w2->getPos());
			}break;
		}
	}break;
	}
	delete g1;
	delete g2;
}

void Wordcoder::inc(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':{
		std::cout << "WordCoder: Não é possivel usar valor estatico como destino de comando!" << std::endl;
	}break;
	case 'm':{
		Memoria *m=(Memoria*)g1;
		inc_m(m->getPos());
	}break;
	case 'P':{
	}break;
	case 'M':{
	}break;
	case 'W':{
		Workspace *w=(Workspace*)g1;
		inc_w(w->getPos());
	}break;
	}
	delete g1;
}

void Wordcoder::setDevVersion(uint64 x){
	incrementTamCabecalho();
	addCabecalho16(COD_DEV_VERSION);
	addCabecalho64(x);
}
void Wordcoder::setGeralName(const char *a){
	incrementTamCabecalho();
	addCabecalho16(COD_NOME_GERAL);
	uint32 x=0;
	addCabecalho8(a[x]);
	while(a[x++]!='\0')addCabecalho8(a[x]);
}
