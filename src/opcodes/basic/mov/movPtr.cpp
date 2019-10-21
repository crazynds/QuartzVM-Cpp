/*
 * movPtr.cpp
 *
 *  Created on: 16 de jun de 2019
 *      Author: lhlag
 */
#include "../../../class/Thread.h"


void mov_mmww_mmww8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint32 inc2=t.getNext32();
	uint8 base2=t.getNext8();
	uint8 index2=t.getNext8();
	uint8 shift2=t.getNext8();


	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	uint64 orig=t.workspace[base2]+t.workspace[index2]<<shift2+inc2;
	dst&=0x0000FFFFFFFFFFFF;
	orig&=0x0000FFFFFFFFFFFF;
	t.mem[dst]=t.mem[orig];
}
void mov_mmww_mmww16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint32 inc2=t.getNext32();
	uint8 base2=t.getNext8();
	uint8 index2=t.getNext8();
	uint8 shift2=t.getNext8();


	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	uint64 orig=t.workspace[base2]+t.workspace[index2]<<shift2+inc2;
	dst&=0x0000FFFFFFFFFFFF;
	orig&=0x0000FFFFFFFFFFFF;
	*(uint16*)&t.mem[dst]=*(uint16*)&t.mem[orig];
}
void mov_mmww_mmww32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint32 inc2=t.getNext32();
	uint8 base2=t.getNext8();
	uint8 index2=t.getNext8();
	uint8 shift2=t.getNext8();


	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	uint64 orig=t.workspace[base2]+t.workspace[index2]<<shift2+inc2;
	dst&=0x0000FFFFFFFFFFFF;
	orig&=0x0000FFFFFFFFFFFF;
	*(uint32*)&t.mem[dst]=*(uint32*)&t.mem[orig];
}
void mov_mmww_mmww48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint32 inc2=t.getNext32();
	uint8 base2=t.getNext8();
	uint8 index2=t.getNext8();
	uint8 shift2=t.getNext8();


	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	uint64 orig=t.workspace[base2]+t.workspace[index2]<<shift2+inc2;
	dst&=0x0000FFFFFFFFFFFF;
	orig&=0x0000FFFFFFFFFFFF;
	*(uint48*)&t.mem[dst]=*(uint48*)&t.mem[orig];
}
void mov_mmww_mmww64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint32 inc2=t.getNext32();
	uint8 base2=t.getNext8();
	uint8 index2=t.getNext8();
	uint8 shift2=t.getNext8();


	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	uint64 orig=t.workspace[base2]+t.workspace[index2]<<shift2+inc2;
	dst&=0x0000FFFFFFFFFFFF;
	orig&=0x0000FFFFFFFFFFFF;
	*(uint64*)&t.mem[dst]=*(uint64*)&t.mem[orig];
}

void mov_mmww_w8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint8 base2=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	t.mem[dst]=*(uint8*)&t.workspace[base2];
}
void mov_mmww_w16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint8 base2=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint16*)&t.mem[dst]=*(uint32*)&t.workspace[base2];
}
void mov_mmww_w32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint8 base2=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint32*)&t.mem[dst]=*(uint32*)&t.workspace[base2];
}
void mov_mmww_w48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint8 base2=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint48*)&t.mem[dst]=*(uint48*)&t.workspace[base2];
}
void mov_mmww_w64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint8 base2=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint64*)&t.mem[dst]=t.workspace[base2];
}
void mov_w_mmww8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint8 base2=t.getNext8();

	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint8*)&t.workspace[base2]=t.mem[dst];
}
void mov_w_mmww16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint8 base2=t.getNext8();

	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint16*)&t.workspace[base2]=*(uint16*)&t.mem[dst];
}
void mov_w_mmww32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint8 base2=t.getNext8();

	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint32*)&t.workspace[base2]=*(uint32*)&t.mem[dst];
}
void mov_w_mmww48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint8 base2=t.getNext8();

	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint48*)&t.workspace[base2]=*(uint48*)&t.mem[dst];
}
void mov_w_mmww64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint8 base2=t.getNext8();

	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	t.workspace[base2]=*(uint64*)&t.mem[dst];
}

void mov_mmww_c8(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint8 val=t.getNext8();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	t.mem[dst]=val;
}
void mov_mmww_c16(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint16 val=t.getNext16();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint16*)&t.mem[dst]=val;
}
void mov_mmww_c32(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint32 val=t.getNext32();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint32*)&t.mem[dst]=val;
}
void mov_mmww_c48(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(15))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint48 val=t.getNext48();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint48*)&t.mem[dst]=val;
}
void mov_mmww_c64(Thread& t){
#ifndef _FAST_MODE
	if(t.checkUseCode(17))return;
#endif
	uint32 inc1=t.getNext32();
	uint8 base1=t.getNext8();
	uint8 index1=t.getNext8();
	uint8 shift1=t.getNext8();

	uint64 val=t.getNext64();

	uint64 dst=t.workspace[base1]+(t.workspace[index1]<<shift1)+inc1;
	dst&=0x0000FFFFFFFFFFFF;
	*(uint64*)&t.mem[dst]=val;
}
/*
void mov_m_mmww8(Thread& t);
void mov_m_mmww16(Thread& t);
void mov_m_mmww32(Thread& t);
void mov_m_mmww48(Thread& t);
void mov_m_mmww64(Thread& t);

void mov_mmww_m8(Thread& t);
void mov_mmww_m16(Thread& t);
void mov_mmww_m32(Thread& t);
void mov_mmww_m48(Thread& t);
void mov_mmww_m64(Thread& t);

void mov_mmww_mmw8(Thread& t);
void mov_mmww_mmw16(Thread& t);
void mov_mmww_mmw32(Thread& t);
void mov_mmww_mmw48(Thread& t);
void mov_mmww_mmw64(Thread& t);

void mov_mmw_mmww8(Thread& t);
void mov_mmw_mmww16(Thread& t);
void mov_mmw_mmww32(Thread& t);
void mov_mmw_mmww48(Thread& t);
void mov_mmw_mmww64(Thread& t);
*/

