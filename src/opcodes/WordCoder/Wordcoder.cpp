/*
* Wordcoder.cpp
*
*  Created on: 17 de jun de 2019
*      Author: lhlag
*/

#include "Wordcoder.h"
#include <string>

using namespace std;

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}


string getPropriety(GeralMemory *g1, GeralMemory *g2){
	string str = "";

	switch(g1->getType()){
		case 'I':{
			str+= "i-";
		}break;
		case 'm':{
			str+= "m-";
		}break;
		case 'M':{
			str+= "mmww-";
		}break;
		case 'P':{
			str+= "mmw-";
		}break;
		case 'W':{
			str+= "w-";
		}break;
		case 'R':{
			str+= "rrw-";
		}break;
		case 'r':{
			str+= "r-";
		}break;
	}
	switch(g2->getType()){
		case 'I':{
			str+= "i";
		}break;
		case 'm':{
			str+= "m";
		}break;
		case 'M':{
			str+= "mmww";
		}break;
		case 'P':{
			str+= "mmw";
		}break;
		case 'W':{
			str+= "w";
		}break;
		case 'R':{
			str+= "rrw";
		}break;
		case 'r':{
			str+= "r";
		}break;
	}
	return str;
}

void Wordcoder::mov(GeralMemory *g1,GeralMemory *g2){
	string str=getPropriety(g1,g2);
	if (str=="m-i"){
		Memoria *m1=(Memoria*)g1;
		ImediateData *im=(ImediateData*)g2;
		mov_m_c(m1->getPos(),im->getValue());
	}else if(str=="m-m"){
			Memoria *m1=(Memoria*)g1;
			Memoria *m2=(Memoria*)g2;
			mov_m_m(m1->getPos(),m2->getPos());
	}else if(str=="r-i"){
			RecursoPtr *m1=(RecursoPtr*)g1;
			ImediateData *m2=(ImediateData*)g2;
			mov_r_c(m1->getPosBase(),m1->getIncrement(),m2->getValue());
	}else if(str=="w-r"){
			Workspace *m1=(Workspace*)g1;
			RecursoPtr *m2=(RecursoPtr*)g2;
			mov_w_r(m1->getPos(),m2->getPosBase(),m2->getIncrement());
	}else if(str=="r-w"){
			RecursoPtr *m1=(RecursoPtr*)g1;
			Workspace *m2=(Workspace*)g2;
			mov_r_w(m1->getPosBase(),m1->getIncrement(),m2->getPos());
	}else if(str=="r-r"){
			RecursoPtr *m1=(RecursoPtr*)g1;
			RecursoPtr *m2=(RecursoPtr*)g2;
			mov_r_r(m1->getPosBase(),m1->getIncrement(),m2->getPosBase(),m2->getIncrement());
	}else if(str=="rrw-i"){
			RecursoPtr *m1=(RecursoPtr*)g1;
			ImediateData *m2=(ImediateData*)g2;
			mov_rrw_c(m1->getPosBase(),m1->getPosIndex(),m1->getShift(),m1->getIncrement(),m2->getValue());
	}else if(str=="w-rrw"){
			Workspace *m2=(Workspace*)g1;
			RecursoPtr *m1=(RecursoPtr*)g2;
			mov_w_rrw(m2->getPos(),m1->getPosBase(),m1->getPosIndex(),m1->getShift(),m1->getIncrement());
	}else if(str=="rrw-w"){
			RecursoPtr *m1=(RecursoPtr*)g1;
			Workspace *m2=(Workspace*)g2;
			mov_rrw_w(m1->getPosBase(),m1->getPosIndex(),m1->getShift(),m1->getIncrement(),m2->getPos());
	}else if(str=="rrw-rrw"){
			RecursoPtr *m1=(RecursoPtr*)g1;
			RecursoPtr *m2=(RecursoPtr*)g2;
			mov_rrw_rrw(m1->getPosBase(),m1->getPosIndex(),m1->getShift(),m1->getIncrement(),m2->getPosBase(),m2->getPosIndex(),m2->getShift(),m2->getIncrement());
	}else if(str=="m-mmw"){
			Memoria *m1=(Memoria*)g1;
			MemoriaPtr *m2=(MemoriaPtr*)g2;
			mov_m_mmw(m1->getPos(),m2->getPosBase(),m2->getIncrement());
	}else if(str=="m-w"){
			Memoria *m1=(Memoria*)g1;
			Workspace *w2=(Workspace*)g2;
			mov_m_w(m1->getPos(),w2->getPos());
	}else if(str=="mmww-i"){
			MemoriaPtr*mp1=(MemoriaPtr*)g1;
			ImediateData *im2=(ImediateData*)g2;
			mov_mmww_c(mp1->getPosBase(),mp1->getPosIndex(),mp1->getShift(),mp1->getIncrement(),im2->getValue());
	}else if(str=="mmww-mmww"){
			MemoriaPtr*mp1=(MemoriaPtr*)g1;
			MemoriaPtr *m2=(MemoriaPtr*)g2;
			mov_mmww_mmww(mp1->getPosBase(),mp1->getPosIndex(),mp1->getShift(),mp1->getIncrement(),m2->getPosBase(),m2->getPosIndex(),m2->getShift(),m2->getIncrement());
	}else if(str=="mmww-w"){
			MemoriaPtr*mp1=(MemoriaPtr*)g1;
			Workspace *w2=(Workspace*)g2;
			mov_mmww_w(mp1->getPosBase(),mp1->getPosIndex(),mp1->getShift(),mp1->getIncrement(),w2->getPos());
	}else if(str=="mmw-i"){
			MemoriaPtr*mp1=(MemoriaPtr*)g1;
			ImediateData *im2=(ImediateData*)g2;
			mov_mmw_c(mp1->getPosBase(),mp1->getIncrement(),im2->getValue());
	}else if(str=="mmw-m"){
			MemoriaPtr*mp1=(MemoriaPtr*)g1;
			Memoria *m2=(Memoria*)g2;
			mov_mmw_m(mp1->getPosBase(),mp1->getIncrement(),m2->getPos());
	}else if(str=="mmw-mmw"){
			MemoriaPtr*mp1=(MemoriaPtr*)g1;
			MemoriaPtr *m2=(MemoriaPtr*)g2;
			mov_mmw_mmw(mp1->getPosBase(),mp1->getIncrement(),m2->getPosBase(),m2->getIncrement());
	}else if(str=="mmw-w"){
			MemoriaPtr*mp1=(MemoriaPtr*)g1;
			Workspace *w2=(Workspace*)g2;
			mov_mmw_w(mp1->getPosBase(),mp1->getIncrement(),w2->getPos());
	}else if(str=="w-i"){
			Workspace *w1=(Workspace*)g1;
			ImediateData *im2=(ImediateData*)g2;
			mov_w_c(w1->getPos(),im2->getValue());
	}else if(str=="w-m"){
			Workspace *w1=(Workspace*)g1;
			Memoria *m2=(Memoria*)g2;
			mov_w_m(w1->getPos(),m2->getPos());
	}else if(str=="w-mmww"){
			Workspace *w1=(Workspace*)g1;
			MemoriaPtr *m2=(MemoriaPtr*)g2;
			mov_w_mmww(w1->getPos(),m2->getPosBase(),m2->getPosIndex(),m2->getShift(),m2->getIncrement());
	}else if(str=="w-mmw"){
			Workspace *w1=(Workspace*)g1;
			MemoriaPtr *m2=(MemoriaPtr*)g2;
			mov_w_mmw(w1->getPos(),m2->getPosBase(),m2->getIncrement());
	}else if(str=="w-w"){
			Workspace *w1=(Workspace*)g1;
			Workspace *w2=(Workspace*)g2;
			mov_w_w(w1->getPos(),w2->getPos());
	}else{
			std::cout << "WordCoder: Ainda não disponivel o uso do comando  mov " << str << std::endl;
	}
	delete g1;
	delete g2;
}
void Wordcoder::mul(GeralMemory *g1,GeralMemory *g2){

	string str=getPropriety(g1,g2);
	if(str=="m-i"){
		Memoria *m1=(Memoria*)g1;
		ImediateData *im=(ImediateData*)g2;
		mul_m_c(m1->getPos(),im->getValue());
	}else if(str=="w-i"){
		Workspace *w1=(Workspace*)g1;
		ImediateData *im2=(ImediateData*)g2;
		mul_w_c(w1->getPos(),im2->getValue());

	}else if(str=="w-m"){
		Workspace *w1=(Workspace*)g1;
		Memoria *m2=(Memoria*)g2;
		mul_w_m(w1->getPos(),m2->getPos());

	}else if(str=="w-w"){
		Workspace *w1=(Workspace*)g1;
		Workspace *w2=(Workspace*)g2;
		mul_w_w(w1->getPos(),w2->getPos());
	}else{
		std::cout << "WordCoder: Ainda não disponivel o uso do comando  mul " << str << std::endl;
	}
	delete g1;
	delete g2;
}
void Wordcoder::div(GeralMemory *g1,GeralMemory *g2){

	string str=getPropriety(g1,g2);
	if(str=="m-i"){
		Memoria *m1=(Memoria*)g1;
		ImediateData *im=(ImediateData*)g2;
		div_m_c(m1->getPos(),im->getValue());
	}else if(str=="w-i"){
		Workspace *w1=(Workspace*)g1;
		ImediateData *im2=(ImediateData*)g2;
		div_w_c(w1->getPos(),im2->getValue());

	}else if(str=="w-m"){
		Workspace *w1=(Workspace*)g1;
		Memoria *m2=(Memoria*)g2;
		div_w_m(w1->getPos(),m2->getPos());

	}else if(str=="w-w"){
		Workspace *w1=(Workspace*)g1;
		Workspace *w2=(Workspace*)g2;
		div_w_w(w1->getPos(),w2->getPos());
	}else{
		std::cout << "WordCoder: Ainda não disponivel o uso do comando  mul " << str << std::endl;
	}
	delete g1;
	delete g2;
}
void Wordcoder::add(GeralMemory *g1,GeralMemory *g2){

	string str=getPropriety(g1,g2);
	if(str=="m-i"){
		Memoria *m1=(Memoria*)g1;
		ImediateData *im=(ImediateData*)g2;
		soma_m_c(m1->getPos(),im->getValue());
	}else if(str=="w-i"){
		Workspace *w1=(Workspace*)g1;
		ImediateData *im2=(ImediateData*)g2;
		soma_w_c(w1->getPos(),im2->getValue());

	}else if(str=="w-m"){
		Workspace *w1=(Workspace*)g1;
		Memoria *m2=(Memoria*)g2;
		soma_w_m(w1->getPos(),m2->getPos());

	}else if(str=="w-w"){
		Workspace *w1=(Workspace*)g1;
		Workspace *w2=(Workspace*)g2;
		soma_w_w(w1->getPos(),w2->getPos());
	}else{
		std::cout << "WordCoder: Ainda não disponivel o uso do comando  mul " << str << std::endl;
	}
	delete g1;
	delete g2;
}
void Wordcoder::sub(GeralMemory *g1,GeralMemory *g2){

	string str=getPropriety(g1,g2);
	if(str=="m-i"){
		Memoria *m1=(Memoria*)g1;
		ImediateData *im=(ImediateData*)g2;
		sub_m_c(m1->getPos(),im->getValue());
	}else if(str=="w-i"){
		Workspace *w1=(Workspace*)g1;
		ImediateData *im2=(ImediateData*)g2;
		sub_w_c(w1->getPos(),im2->getValue());

	}else if(str=="w-m"){
		Workspace *w1=(Workspace*)g1;
		Memoria *m2=(Memoria*)g2;
		sub_w_m(w1->getPos(),m2->getPos());

	}else if(str=="w-w"){
		Workspace *w1=(Workspace*)g1;
		Workspace *w2=(Workspace*)g2;
		sub_w_w(w1->getPos(),w2->getPos());
	}else{
		std::cout << "WordCoder: Ainda não disponivel o uso do comando  mul " << str << std::endl;
	}
	delete g1;
	delete g2;
}


void Wordcoder::inc(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':{
		std::cout << "WordCoder: Não é possivel incrementar um valor estatico!" << std::endl;
	}break;
	case 'm':{
		Memoria *m=(Memoria*)g1;
		inc_m(m->getPos());
	}break;
	case 'P':
	case 'M':
		std::cout << "WordCoder: Não é possivel incrementar um valor dinamico baseado em registradores!" << std::endl;
	break;
	case 'W':{
		Workspace *w=(Workspace*)g1;
		inc_w(w->getPos());
	}break;
	}
	delete g1;
}

void Wordcoder::dec(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':{
		std::cout << "WordCoder: Não é possivel decrementar um valor estatico!" << std::endl;
	}break;
	case 'm':{
		Memoria *m=(Memoria*)g1;
		dec_m(m->getPos());
	}break;
	case 'P':
	case 'M':
		std::cout << "WordCoder: Não é possivel decrementar um valor dinamico baseado em registradores!" << std::endl;
	break;
	case 'W':{
		Workspace *w=(Workspace*)g1;
		dec_w(w->getPos());
	}break;
	}
	delete g1;
}

void Wordcoder::call(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':{
		ImediateData *im2=(ImediateData*)g1;
		call_c(im2->getValue());
	}break;
	case 'm':{
		Memoria *m=(Memoria*)g1;
		call_m(m->getPos());
	}break;
	case 'P':
	case 'M':
		std::cout << "WordCoder: Não é possivel pular para um valor dinamico baseado em registradores!" << std::endl;
	break;
	case 'W':{
		Workspace *w=(Workspace*)g1;
		call_w(w->getPos());
	}break;
	}
	delete g1;
}
void Wordcoder::call(Label &l){
	call_c(0);
	l.addLocation(getTam()-4);
}

void Wordcoder::push(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':{
		ImediateData *im2=(ImediateData*)g1;
		push_c(im2->getValue());
	}break;
	case 'm':
		std::cout << "WordCoder: Não é possivel salvar na stack um valor direto da memoria!" << std::endl;
	break;
	case 'P':
	case 'M':
		std::cout << "WordCoder: Não é possivel salvar na stack um valor dinamico baseado em registradores!!" << std::endl;
	break;
	case 'W':{
		Workspace *w=(Workspace*)g1;
		push_w(w->getPos());
	}break;
	}
	delete g1;
}


void Wordcoder::pop(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':{
		std::cout << "WordCoder: Não é possivel salvar num valor constante o valor no topo da stack" << std::endl;
	}break;
	case 'm':
		std::cout << "WordCoder: Não é possivel salvar na memoria o valor no topo da stack!" << std::endl;
	break;
	case 'P':
	case 'M':
		std::cout << "WordCoder: Não é possivel salvar num valor dinamico baseado em registradores o valor no topo da stack!" << std::endl;
	break;
	case 'W':{
		Workspace *w=(Workspace*)g1;
		pop_w(w->getPos());
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
void Wordcoder::setString(GeralMemory *g1, char *str){
	switch(g1->getType()){
	case 'I':{
		std::cout << "WordCoder: Não é possivel setar a string em um valor estatico!" << std::endl;
	}break;
	case 'm':{
		Memoria *m=(Memoria*)g1;
		set_string_m(str,m->getPos().toInt());
	}break;
	case 'P':
	case 'M':
	case 'W':
		std::cout << "WordCoder: Não é possivel setar uma string baseado em um valor dinamico baseado em registradores!" << std::endl;
	break;
	}
	delete g1;
}

void Wordcoder::printNum(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':
		std::cout << "WordCoder: Não é possivel printar um numero com esse método!" << std::endl;
		break;
	case 'm':
		std::cout << "WordCoder: Não é possivel printar um numero com esse método!" << std::endl;
		break;
	case 'P':
		std::cout << "WordCoder: Não é possivel printar um numero com esse método!" << std::endl;
		break;
	case 'M':
		std::cout << "WordCoder: Não é possivel printar um numero com esse método!" << std::endl;
		break;
	case 'W':{
		Workspace *w=(Workspace*)g1;
		print_out_num_w(w->getPos());
	}break;
	}
	delete g1;
}
void Wordcoder::printChar(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':
		std::cout << "WordCoder: Não é possivel printar um caracter com esse método!" << std::endl;
		break;
	case 'm':
		std::cout << "WordCoder: Não é possivel printar um caracter com esse método!" << std::endl;
		break;
	case 'P':
		std::cout << "WordCoder: Não é possivel printar um caracter com esse método!" << std::endl;
		break;
	case 'M':
		std::cout << "WordCoder: Não é possivel printar um caracter com esse método!" << std::endl;
		break;
	case 'W':{
		Workspace *w=(Workspace*)g1;
		print_out_char_w(w->getPos());
	}break;
	}
	delete g1;
}
void Wordcoder::printString(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':
		std::cout << "WordCoder: Não é possivel printar uma string com esse método!" << std::endl;
		break;
	case 'P':{
		MemoriaPtr *m=(MemoriaPtr*)g1;
		print_out_string_mmw(m->getPosIndex(),m->getIncrement());
	}break;
	case 'm':{
		Memoria *m=(Memoria*)g1;
		print_out_string_m(m->getPos());
	}break;
	case 'M':
		std::cout << "WordCoder: Não é possivel printar uma string com esse método!" << std::endl;
		break;
	case 'W':
		std::cout << "WordCoder: Não é possivel printar uma string com esse método!" << std::endl;
		break;
	}
	delete g1;
}

void Wordcoder::jmp(GeralMemory *g1){
	switch(g1->getType()){
	case 'I':{
		ImediateData *id=(ImediateData*)g1;
		jmp_c(id->getValue());
	}break;
	case 'P':{
		std::cout << "WordCoder: Não é possivel executar chamada de função de acordo com o valor em ponteiros!" << std::endl;
	}break;
	case 'm':{
		Memoria *m=(Memoria*)g1;
		jmp_m(m->getPos());
	}break;
	case 'M':
		std::cout << "WordCoder: Não é possivel executar chamada de função de acordo com o valor em ponteiros!" << std::endl;
		break;
	case 'W':
		Workspace *m=(Workspace*)g1;
		jmp_w(m->getPos());
		break;
	}
	delete g1;
}
void Wordcoder::jmp(GeralMemory *g1,char cmp){
	switch(g1->getType()){
	case 'I':{
		ImediateData *id=(ImediateData*)g1;
		switch(cmp){
		case '!':
			jmp_c_di(id->getValue());
			break;
		case '=':
			jmp_c_ig(id->getValue());
			break;
		case '>':
			jmp_c_ma(id->getValue());
			break;
		case '<':
			jmp_c_me(id->getValue());
			break;
		case '+':
			jmp_c_ma_ig(id->getValue());
			break;
		case '-':
			jmp_c_me_ig(id->getValue());
			break;
		}
	}break;
	case 'P':{
		std::cout << "WordCoder: Não é possivel executar chamada de função de acordo com o valor em ponteiros!" << std::endl;
	}break;
	case 'm':{
		Memoria *m=(Memoria*)g1;
		switch(cmp){
		case '!':
			jmp_m_di(m->getPos());
			break;
		case '=':
			jmp_m_ig(m->getPos());
			break;
		case '>':
			jmp_m_ma(m->getPos());
			break;
		case '<':
			jmp_m_me(m->getPos());
			break;
		case '+':
			jmp_m_ma_ig(m->getPos());
			break;
		case '-':
			jmp_m_me_ig(m->getPos());
			break;
		}
	}break;
	case 'M':
		std::cout << "WordCoder: Não é possivel executar chamada de função de acordo com o valor em ponteiros!" << std::endl;
		break;
	case 'W':
		Workspace *m=(Workspace*)g1;
		switch(cmp){
		case '!':
			jmp_w_di(m->getPos());
			break;
		case '=':
			jmp_w_ig(m->getPos());
			break;
		case '>':
			jmp_w_ma(m->getPos());
			break;
		case '<':
			jmp_w_me(m->getPos());
			break;
		case '+':
			jmp_w_ma_ig(m->getPos());
			break;
		case '-':
			jmp_w_me_ig(m->getPos());
			break;
		}
		break;
	}
	delete g1;
}
void Wordcoder::jmp(Label &l,char cmp){
	jmp(c_(0),cmp);
	l.addLocation(getTam()-4);
}
void Wordcoder::jmp(Label &l){
	jmp(c_(0));
	l.addLocation(getTam()-4);
}
void Wordcoder::bind(Label &l){
	l.setPosition(getPos());
}
GeralMemory* w_(uint8 pos){
	Workspace *w=new Workspace(pos);
	return (GeralMemory*)w;
}
GeralMemory* m_(uint48 pos){
	Memoria *w=new Memoria(pos);
	return (GeralMemory*)w;
}
GeralMemory* ptr_(GeralMemory *r,uint32 inc=0){
	if(r->getType()=='W'){
		MemoriaPtr *w=new MemoriaPtr((Workspace*)r,inc);
		return (GeralMemory*)w;
	}else{
		std::cout << "Wordcoder: Esperado um registrador onde foi recebido outro tipo de variavel";
		return NULL;
	}
}
GeralMemory* ptr_(GeralMemory *reg,GeralMemory *regIndex,uint8 shift=0,uint32 inc=0){
	if(reg->getType()=='W' && regIndex->getType()=='W'){
		MemoriaPtr *w=new MemoriaPtr((Workspace*)reg,(Workspace*)regIndex,shift,inc);
		return (GeralMemory*)w;
	}else{
		std::cout << "Wordcoder: Esperado um registrador onde foi recebido outro tipo de variavel";
		return NULL;
	}
}

GeralMemory* ptr_R(GeralMemory *r,uint32 inc=0){
	if(r->getType()=='W'){
		RecursoPtr *w=new RecursoPtr((Workspace*)r,inc);
		return (GeralMemory*)w;
	}else{
		std::cout << "Wordcoder: Esperado um registrador onde foi recebido outro tipo de variavel";
		return NULL;
	}
}
GeralMemory* ptr_R(GeralMemory *reg,GeralMemory *regIndex,uint8 shift=0,uint32 inc=0){
	if(reg->getType()=='W' && regIndex->getType()=='W'){
		RecursoPtr *w=new RecursoPtr((Workspace*)reg,(Workspace*)regIndex,shift,inc);
		return (GeralMemory*)w;
	}else{
		std::cout << "Wordcoder: Esperado um registrador onde foi recebido outro tipo de variavel";
		return NULL;
	}
}
GeralMemory* c_(uint64 dado){
	ImediateData *id=new ImediateData(dado);
	return (GeralMemory*)id;
}


