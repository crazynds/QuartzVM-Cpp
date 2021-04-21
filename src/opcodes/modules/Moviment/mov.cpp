/*
 * mov
 *
 *  Created on: 6 de mar de 2019
 *      Author: lhlag
 */


#include "../../../class/Thread.h"

#include "../Jit/Jit.h"

// | opcode 16 | 48 memory to go |  8 - 64 value |



void c_mov_w_w8(CodeHolder *ch){
	Assembler a(ch);
	Label end=a.newLabel();
	Thread t;
	a.push(rbx);
	a.push(rsi);
	a.sub(rsp,0x8);

#ifndef _FAST_MODE
	a.mov(rdx,4);
	a.call(uint64((void*)Thread::checkUseCode));
	a.cmp(rax,0);
	a.jne(end);
#endif
	a.mov(rbx,rcx);
	a.call(uint64((void*)Thread::getNextTwo8));
	a.movzx(ecx,ah);
	a.movzx(eax,al);
	a.lea(rsi,ptr(rbx,eax,3,getWorkspace()));
	a.mov(al,ptr(rbx,ecx,3,getWorkspace()));
	a.mov(ptr(rsi),al);

	a.bind(end);
	a.add(rsp,0x8);
	a.pop(rsi);
	a.pop(rbx);
	a.ret();
}

void mov_w_c8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x=t.getNext8();
}
void mov_w_c16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x=t.getNext16();
}
void mov_w_c32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(7);
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x=t.getNext32();
}
void mov_w_c48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x=t.getNext48();
}
void mov_w_c64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(11);
#endif
	t.workspace[t.getNext8()]=t.getNext64();
}
void c_mov_w_w16(CodeHolder *ch){
	Assembler a(ch);
	Label end=a.newLabel();
	Thread t;

	a.push(rbx);
	a.push(rsi);
	a.sub(rsp,0x8);

#ifndef _FAST_MODE
	a.mov(rdx,4);
	a.call(uint64((void*)Thread::checkUseCode));
	a.cmp(rax,0);
	a.jne(end);
#endif
	a.mov(rbx,rcx);
	a.call(uint64((void*)Thread::getNextTwo8));
	a.movzx(ecx,ah);
	a.movzx(eax,al);
	a.lea(rsi,ptr(rbx,eax,3,getWorkspace()));
	a.mov(ax,ptr(rbx,ecx,3,getWorkspace()));
	a.mov(ptr(rsi),ax);

	a.bind(end);
	a.add(rsp,0x8);
	a.pop(rsi);
	a.pop(rbx);
	a.ret();
}
void c_mov_w_w32(CodeHolder *ch){
	Assembler a(ch);
	Label end=a.newLabel();
	Thread t;

	a.push(rbx);
	a.push(rsi);
	a.sub(rsp,0x8);

#ifndef _FAST_MODE
	a.mov(rdx,4);
	a.call(uint64((void*)Thread::checkUseCode));
	a.cmp(rax,0);
	a.jne(end);
#endif
	a.mov(rbx,rcx);
	a.call(uint64((void*)Thread::getNextTwo8));
	a.movzx(ecx,ah);
	a.movzx(eax,al);
	a.lea(rsi,ptr(rbx,eax,3,getWorkspace()));
	a.mov(eax,ptr(rbx,ecx,3,getWorkspace()));
	a.mov(ptr(rsi),eax);

	a.bind(end);
	a.add(rsp,0x8);
	a.pop(rsi);
	a.pop(rbx);
	a.ret();
}
void c_mov_w_w48(CodeHolder *ch){
	Assembler a(ch);
	Label end=a.newLabel();
	Thread t;

	a.push(rbx);
	a.push(rsi);
	a.sub(rsp,0x8);

#ifndef _FAST_MODE
	a.mov(rdx,4);
	a.call(uint64((void*)Thread::checkUseCode));
	a.cmp(rax,0);
	a.jne(end);
#endif
	a.mov(rbx,rcx);
	a.call(uint64((void*)Thread::getNextTwo8));
	a.movzx(ecx,ah);
	a.movzx(eax,al);
	a.lea(rsi,ptr(rbx,eax,3,getWorkspace()));
	a.mov(rax,ptr(rbx,ecx,3,getWorkspace()));
	a.mov(ptr(rsi),eax);
	a.shr(rax,32);
	a.mov(ptr(rsi,4),ax);

	a.bind(end);
	a.add(rsp,0x8);
	a.pop(rsi);
	a.pop(rbx);
	a.ret();
}
void c_mov_w_w64(CodeHolder *ch){
	Assembler a(ch);
	Label end=a.newLabel();
	Thread t;

	a.push(rbx);
	a.push(rsi);
	a.sub(rsp,0x8);

#ifndef _FAST_MODE
	a.mov(rdx,4);
	a.call(uint64((void*)Thread::checkUseCode));
	a.cmp(rax,0);
	a.jne(end);
#endif
	a.mov(rbx,rcx);
	a.call(uint64((void*)Thread::getNextTwo8));
	a.movzx(ecx,ah);
	a.movzx(eax,al);
	a.lea(rsi,ptr(rbx,eax,3,getWorkspace()));
	a.mov(rax,ptr(rbx,ecx,3,getWorkspace()));
	a.mov(ptr(rsi),rax);

	a.bind(end);
	a.add(rsp,0x8);
	a.pop(rsi);
	a.pop(rbx);
	a.ret();
}

void mov_w_w8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x=(uint8)t.workspace[t.getNext8()];
}
void mov_w_w16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x=(uint16)t.workspace[t.getNext8()];
}
void mov_w_w32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x=(uint32)t.workspace[t.getNext8()];
}
void mov_w_w48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x=(uint48)t.workspace[t.getNext8()];
}
void mov_w_w64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint8 x=t.getNext8();
	t.workspace[x]=t.workspace[t.getNext8()];
}


void mov_m_c8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]=y;
}
void mov_m_c16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(10);
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x=t.getNext16();
}
void mov_m_c32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif
	uint64 te=t.getNext48().toInt();
	uint32 *x=(uint32*)&t.mem[te];
	*x=t.getNext32();
}
void mov_m_c48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x=t.getNext48();
}
void mov_m_c64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(16);
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x=t.getNext64();
}


// | opcode 16 | 48 memory to go |  48 memory to get |

void mov_m_m8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	uint64 x=t.getNext48().toInt();
	uint64 y=t.getNext48().toInt();
	t.mem[x]=t.mem[y];
}
void mov_m_m16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void mov_m_m32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void mov_m_m48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void mov_m_m64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void mov_m_w8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]=(uint8)t.workspace[y];
}
void mov_m_w16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x=(uint16)t.workspace[t.getNext8()];
}
void mov_m_w32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x=(uint32)t.workspace[t.getNext8()];
}
void mov_m_w48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x=(uint48)t.workspace[t.getNext8()];
}
void mov_m_w64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x=t.workspace[t.getNext8()];
}
void mov_w_m8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x=t.mem[t.getNext48().toInt()];
}
void mov_w_m16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void mov_w_m32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void mov_w_m48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void mov_w_m64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint8 x=t.getNext8();
	t.workspace[x]=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void mov_mmw_c8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	t.mem[z]=t.getNext8();
}
void mov_mmw_c16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint16 *x=(uint16*)&t.mem[z];
	*x=t.getNext16();
}
void mov_mmw_c32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(11);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint32 *x=(uint32*)&t.mem[z];
	*x=t.getNext32();
}
void mov_mmw_c48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(13);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint48 *x=(uint48*)&t.mem[z];
	*x=t.getNext48();
}
void mov_mmw_c64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(15);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint64 *x=(uint64*)&t.mem[z];
	*x=t.getNext64();
}

void mov_mmw_m8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(13);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	t.mem[z]=t.mem[t.getNext48().toInt()];
}
void mov_mmw_m16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(13);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint16 *x=(uint16*)&t.mem[z];
	*x=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void mov_mmw_m32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(13);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint32 *x=(uint32*)&t.mem[z];
	*x=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void mov_mmw_m48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(13);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint48 *x=(uint48*)&t.mem[z];
	*x=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void mov_mmw_m64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(13);
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint64 *x=(uint64*)&t.mem[z];
	*x=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void mov_m_mmw8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif

	register uint64 x=t.getNext48().toInt();

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	t.mem[x]=t.mem[y];
}
void mov_m_mmw16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif

	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint16*)&t.mem[y]);
}
void mov_m_mmw32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif

	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint32*)&t.mem[y]);
}
void mov_m_mmw48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif

	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint48*)&t.mem[y]);
}
void mov_m_mmw64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif

	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint64*)&t.mem[y]);
}
void mov_w_mmw8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif

	uint8 *x=(uint8*)&t.workspace[t.getNext8()];

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	*x=t.mem[y];
}
void mov_w_mmw16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif

	uint16 *x=(uint16*)&t.workspace[t.getNext8()];

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint16*)&t.mem[y]);
}
void mov_w_mmw32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif

	uint32 *x=(uint32*)&t.workspace[t.getNext8()];

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint32*)&t.mem[y]);
}
void mov_w_mmw48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif

	uint48 *x=(uint48*)&t.workspace[t.getNext8()];

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint48*)&t.mem[y]);
}
void mov_w_mmw64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif

	register uint8 v=t.getNext8();

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	t.workspace[v]=*((uint64*)&t.mem[y]);
}
void mov_mmw_w8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	t.mem[z]=(uint8)t.workspace[t.getNext8()];
}
void mov_mmw_w16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	uint16 *x=(uint16*)&t.mem[z];
	*x=*((uint16*)&t.workspace[t.getNext8()]);
}
void mov_mmw_w32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	uint32 *x=(uint32*)&t.mem[z];
	*x=*((uint32*)&t.workspace[t.getNext8()]);
}
void mov_mmw_w48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	uint48 *x=(uint48*)&t.mem[z];
	*x=*((uint48*)&t.workspace[t.getNext8()]);
}
void mov_mmw_w64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	uint64 *x=(uint64*)&t.mem[z];
	*x=t.workspace[t.getNext8()];
}
void mov_mmw_mmw8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	t.mem[z]=t.mem[y];
}
void mov_mmw_mmw16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif

	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	uint16 *x=(uint16*)&t.mem[z];
	*x=*((uint16*)&t.mem[y]);
}
void mov_mmw_mmw32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif

	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	uint32 *x=(uint32*)&t.mem[z];
	*x=*((uint32*)&t.mem[y]);
}
void mov_mmw_mmw48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif

	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	uint48 *x=(uint48*)&t.mem[z];
	*x=*((uint48*)&t.mem[y]);
}
void mov_mmw_mmw64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif

	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	uint64 *x=(uint64*)&t.mem[z];
	*x=*((uint64*)&t.mem[y]);
}



#define createFuncUINT(B) B(uint8,8);\
		B(uint16,16);\
		B(uint32,32);\
		B(uint48,48);\
		B(uint64,64);

#ifndef _FAST_MODE
#define func_mov_rrw_w(B,C) void mov_rrw_w##C(Thread& t){	\
		t.checkUseCode(10);			\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 index = t.getNext8();					\
	uint8 shift = t.getNext8();					\
	uint8 ori = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+(t.workspace[index]<<shift)+inc);\
	B *ptr2=(B*)&t.workspace[ori];\
	*ptr=*ptr2;}
#else
#define func_mov_rrw_w(B,C) void mov_rrw_w##C(Thread& t){	\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 index = t.getNext8();					\
	uint8 shift = t.getNext8();					\
	uint8 ori = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+(t.workspace[index]<<shift)+inc);\
	B *ptr2=(B*)&t.workspace[ori];\
	*ptr=*ptr2;}
#endif

#ifndef _FAST_MODE
#define func_mov_w_rrw(B,C) void mov_w_rrw##C(Thread& t){	\
		t.checkUseCode(10);			\
	uint8 ori = t.getNext8();					\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 index = t.getNext8();					\
	uint8 shift = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+(t.workspace[index]<<shift)+inc);\
	B *ptr2=(B*)&t.workspace[ori];\
	*ptr2=*ptr;}
#else
#define func_mov_w_rrw(B,C) void mov_w_rrw##C(Thread& t){	\
	uint8 ori = t.getNext8();					\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 index = t.getNext8();					\
	uint8 shift = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+(t.workspace[index]<<shift)+inc);\
	B *ptr2=(B*)&t.workspace[ori];\
	*ptr2=*ptr;}
#endif

#ifndef _FAST_MODE
#define func_mov_rrw_rrw(B,C) void mov_rrw_rrw##C(Thread& t){	\
	t.checkUseCode(16);			\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 index = t.getNext8();					\
	uint8 shift = t.getNext8();					\
	uint32 inc2 = t.getNext32();				\
	uint8 base2 = t.getNext8();					\
	uint8 index2 = t.getNext8();				\
	uint8 shift2 = t.getNext8();				\
	B *ptr=(B*)(t.workspace[base]+(t.workspace[index]<<shift)+inc);\
	B *ptr2=(B*)(t.workspace[base2]+(t.workspace[index2]<<shift2)+inc2);\
	*ptr=*ptr2;}
#else
#define func_mov_rrw_rrw(B,C) void mov_rrw_rrw##C(Thread& t){	\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 index = t.getNext8();					\
	uint8 shift = t.getNext8();					\
	uint32 inc2 = t.getNext32();				\
	uint8 base2 = t.getNext8();					\
	uint8 index2 = t.getNext8();				\
	uint8 shift2 = t.getNext8();				\
	B *ptr=(B*)(t.workspace[base]+(t.workspace[index]<<shift)+inc);\
	B *ptr2=(B*)(t.workspace[base2]+(t.workspace[index2]<<shift2)+inc2);\
	*ptr=*ptr2;}
#endif

#ifndef _FAST_MODE
#define func_mov_rrw_c(B,C) void mov_rrw_c##C(Thread& t){	\
	if(t.checkUseCode(9 + ( C / 8 )))return;				\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 index = t.getNext8();					\
	uint8 shift = t.getNext8();					\
	B val = t.getNext##C();						\
	B *ptr=(B*)(t.workspace[base]+(t.workspace[index]<<shift)+inc);\
	*ptr=val;}
#else
#define func_mov_rrw_c(B,C) void mov_rrw_c##C(Thread& t){	\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 index = t.getNext8();					\
	uint8 shift = t.getNext8();					\
	B val = t.getNext##C();						\
	B *ptr=(B*)(t.workspace[base]+(t.workspace[index]<<shift)+inc);\
	*ptr=val;}
#endif


#ifndef _FAST_MODE
#define func_mov_r_c(B,C) void mov_r_c##C(Thread& t){	\
	if(t.checkUseCode(7 + ( C / 8 )))return;				\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	B val = t.getNext##C();						\
	B *ptr=(B*)(t.workspace[base]+inc);\
	*ptr=val;}
#else
#define func_mov_r_c(B,C) void mov_r_c##C(Thread& t){	\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	B val = t.getNext##C();						\
	B *ptr=(B*)(t.workspace[base]+inc);\
	*ptr=val;}
#endif
#ifndef _FAST_MODE
#define func_mov_r_w(B,C) void mov_r_w##C(Thread& t){	\
	t.checkUseCode(8);				\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 ori = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+inc);\
	B *ptr2=(B*)&t.workspace[ori];\
	*ptr=*ptr2;}
#else
#define func_mov_r_w(B,C) void mov_r_w##C(Thread& t){	\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint8 ori = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+inc);\
	B *ptr2=(B*)&t.workspace[ori];\
	*ptr=*ptr2;}
#endif
#ifndef _FAST_MODE
#define func_mov_w_r(B,C) void mov_w_r##C(Thread& t){	\
	t.checkUseCode(8);				\
	uint8 ori = t.getNext8();					\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+inc);\
	B *ptr2=(B*)&t.workspace[ori];\
	*ptr2=*ptr;}
#else
#define func_mov_w_r(B,C) void mov_w_r##C(Thread& t){	\
	uint8 ori = t.getNext8();					\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+inc);\
	B *ptr2=(B*)&t.workspace[ori];\
	*ptr2=*ptr;}
#endif
#ifndef _FAST_MODE
#define func_mov_r_r(B,C) void mov_r_r##C(Thread& t){	\
	t.checkUseCode(12);				\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint32 inc2 = t.getNext32();				\
	uint8 base2 = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+inc);\
	B *ptr2=(B*)(t.workspace[base2]+inc2);\
	*ptr=*ptr2;}
#else
#define func_mov_r_r(B,C) void mov_r_r##C(Thread& t){	\
	uint32 inc = t.getNext32();					\
	uint8 base = t.getNext8();					\
	uint32 inc2 = t.getNext32();				\
	uint8 base2 = t.getNext8();					\
	B *ptr=(B*)(t.workspace[base]+inc);\
	B *ptr2=(B*)(t.workspace[base2]+inc2);\
	*ptr=*ptr2;}
#endif

createFuncUINT(func_mov_rrw_w);
createFuncUINT(func_mov_w_rrw);
createFuncUINT(func_mov_rrw_rrw);
createFuncUINT(func_mov_rrw_c);

createFuncUINT(func_mov_r_c);
createFuncUINT(func_mov_w_r);
createFuncUINT(func_mov_r_w);
createFuncUINT(func_mov_r_r);




