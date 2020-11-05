/*
* cmov.cpp
*
*  Created on: 15 de jun de 2019
*      Author: lhlag
*/

#include "../../../class/Thread.h"

#define IGUAL 1<<0
#define MAIOR 1<<1
#define MENOR 1<<2

void cmov_ig_w_c8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=t.getNext8();
}
void cmov_ig_w_c16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=t.getNext16();
}
void cmov_ig_w_c32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=t.getNext32();
}
void cmov_ig_w_c48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=t.getNext48();
}
void cmov_ig_w_c64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=t.getNext64();
}

void cmov_di_w_c8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&(IGUAL)))*x=t.getNext8();
}
void cmov_di_w_c16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&IGUAL))*x=t.getNext16();
}
void cmov_di_w_c32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&IGUAL))*x=t.getNext32();
}
void cmov_di_w_c48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&IGUAL))*x=t.getNext48();
}
void cmov_di_w_c64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&IGUAL))*x=t.getNext64();
}

void cmov_ma_w_c8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=t.getNext8();
}
void cmov_ma_w_c16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=t.getNext16();
}
void cmov_ma_w_c32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=t.getNext32();
}
void cmov_ma_w_c48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=t.getNext48();
}
void cmov_ma_w_c64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=t.getNext64();
}

void cmov_me_w_c8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=t.getNext8();
}
void cmov_me_w_c16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=t.getNext16();
}
void cmov_me_w_c32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=t.getNext32();
}
void cmov_me_w_c48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=t.getNext48();
}
void cmov_me_w_c64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=t.getNext64();
}

void cmov_ma_ig_w_c8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=t.getNext8();
}
void cmov_ma_ig_w_c16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=t.getNext16();
}
void cmov_ma_ig_w_c32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=t.getNext32();
}
void cmov_ma_ig_w_c48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=t.getNext48();
}
void cmov_ma_ig_w_c64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=t.getNext64();
}

void cmov_me_ig_w_c8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MENOR))*x=t.getNext8();
}
void cmov_me_ig_w_c16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MENOR))*x=t.getNext16();
}
void cmov_me_ig_w_c32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MENOR))*x=t.getNext32();
}
void cmov_me_ig_w_c48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MENOR))*x=t.getNext48();
}
void cmov_me_ig_w_c64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR|IGUAL))*x=t.getNext64();
}














void cmov_ig_w_w8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=*(uint8*)&t.workspace[t.getNext8()];
}
void cmov_ig_w_w16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=*(uint16*)&t.workspace[t.getNext8()];
}
void cmov_ig_w_w32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=*(uint32*)&t.workspace[t.getNext8()];
}
void cmov_ig_w_w48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=*(uint48*)&t.workspace[t.getNext8()];
}
void cmov_ig_w_w64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL))*x=*(uint64*)&t.workspace[t.getNext8()];
}

void cmov_di_w_w8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&(IGUAL)))*x=*(uint8*)&t.workspace[t.getNext8()];
}
void cmov_di_w_w16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&IGUAL))*x=*(uint16*)&t.workspace[t.getNext8()];
}
void cmov_di_w_w32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&IGUAL))*x=*(uint32*)&t.workspace[t.getNext8()];
}
void cmov_di_w_w48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&IGUAL))*x=*(uint48*)&t.workspace[t.getNext8()];
}
void cmov_di_w_w64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(!(t.compare_flags&IGUAL))*x=*(uint64*)&t.workspace[t.getNext8()];
}

void cmov_ma_w_w8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=*(uint8*)&t.workspace[t.getNext8()];
}
void cmov_ma_w_w16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=*(uint16*)&t.workspace[t.getNext8()];
}
void cmov_ma_w_w32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=*(uint32*)&t.workspace[t.getNext8()];
}
void cmov_ma_w_w48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=*(uint48*)&t.workspace[t.getNext8()];
}
void cmov_ma_w_w64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MAIOR))*x=*(uint64*)&t.workspace[t.getNext8()];
}

void cmov_me_w_w8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=*(uint8*)&t.workspace[t.getNext8()];
}
void cmov_me_w_w16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=*(uint16*)&t.workspace[t.getNext8()];
}
void cmov_me_w_w32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=*(uint32*)&t.workspace[t.getNext8()];
}
void cmov_me_w_w48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=*(uint48*)&t.workspace[t.getNext8()];
}
void cmov_me_w_w64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR))*x=*(uint64*)&t.workspace[t.getNext8()];
}

void cmov_ma_ig_w_w8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=*(uint8*)&t.workspace[t.getNext8()];
}
void cmov_ma_ig_w_w16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=*(uint16*)&t.workspace[t.getNext8()];
}
void cmov_ma_ig_w_w32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=*(uint32*)&t.workspace[t.getNext8()];
}
void cmov_ma_ig_w_w48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=*(uint48*)&t.workspace[t.getNext8()];
}
void cmov_ma_ig_w_w64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MAIOR))*x=*(uint64*)&t.workspace[t.getNext8()];
}

void cmov_me_ig_w_w8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MENOR))*x=*(uint8*)&t.workspace[t.getNext8()];
}
void cmov_me_ig_w_w16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MENOR))*x=*(uint16*)&t.workspace[t.getNext8()];
}
void cmov_me_ig_w_w32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MENOR))*x=*(uint32*)&t.workspace[t.getNext8()];
}
void cmov_me_ig_w_w48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(IGUAL|MENOR))*x=*(uint48*)&t.workspace[t.getNext8()];
}
void cmov_me_ig_w_w64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	if(t.compare_flags&(MENOR|IGUAL))*x=*(uint64*)&t.workspace[t.getNext8()];
}

