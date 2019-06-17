/*
 * mov
 *
 *  Created on: 6 de mar de 2019
 *      Author: lhlag
 */


#include "../../../class/Thread.h"

// | opcode 16 | 48 memory to go |  8 - 64 value |

#include "../../advanced/Jit/Jit.h"


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
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x=(uint8)t.workspace[t.getNext8()];
}
void mov_w_w16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x=(uint16)t.workspace[t.getNext8()];
}
void mov_w_w32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x=(uint32)t.workspace[t.getNext8()];
}
void mov_w_w48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x=(uint48)t.workspace[t.getNext8()];
}
void mov_w_w64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]=t.workspace[t.getNext8()];
}




void mov_m_c8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]=y;
}
void mov_m_c16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x=t.getNext16();
}
void mov_m_c32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
#endif
	uint64 te=t.getNext48().toInt();
	uint32 *x=(uint32*)&t.mem[te];
	*x=t.getNext32();
}
void mov_m_c48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x=t.getNext48();
}
void mov_m_c64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x=t.getNext64();
}


// | opcode 16 | 48 memory to go |  48 memory to get |

void mov_m_m8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint64 x=t.getNext48().toInt();
	uint64 y=t.getNext48().toInt();
	t.mem[x]=t.mem[y];
}
void mov_m_m16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void mov_m_m32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void mov_m_m48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void mov_m_m64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void mov_m_w8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]=(uint8)t.workspace[y];
}
void mov_m_w16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x=(uint16)t.workspace[t.getNext8()];
}
void mov_m_w32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x=(uint32)t.workspace[t.getNext8()];
}
void mov_m_w48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x=(uint48)t.workspace[t.getNext8()];
}
void mov_m_w64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x=t.workspace[t.getNext8()];
}
void mov_w_m8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x=t.mem[t.getNext48().toInt()];
}
void mov_w_m16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void mov_w_m32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void mov_w_m48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void mov_w_m64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void mov_w_c8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x=t.getNext8();
}
void mov_w_c16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x=t.getNext16();
}
void mov_w_c32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x=t.getNext32();
}
void mov_w_c48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x=t.getNext48();
}
void mov_w_c64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	t.workspace[t.getNext8()]=t.getNext64();
}

void mov_mmw_c8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(8))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	t.mem[z]=t.getNext8();
}
void mov_mmw_c16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint16 *x=(uint16*)&t.mem[z];
	*x=t.getNext16();
}
void mov_mmw_c32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint32 *x=(uint32*)&t.mem[z];
	*x=t.getNext32();
}
void mov_mmw_c48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint48 *x=(uint48*)&t.mem[z];
	*x=t.getNext48();
}
void mov_mmw_c64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(15))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint64 *x=(uint64*)&t.mem[z];
	*x=t.getNext64();
}

void mov_mmw_m8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	t.mem[z]=t.mem[t.getNext48().toInt()];
}
void mov_mmw_m16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint16 *x=(uint16*)&t.mem[z];
	*x=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void mov_mmw_m32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint32 *x=(uint32*)&t.mem[z];
	*x=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void mov_mmw_m48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint48 *x=(uint48*)&t.mem[z];
	*x=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void mov_mmw_m64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif
	uint32 inc=t.getNext32();
	register uint64 z=t.workspace[t.getNext8()]+inc;
	z&=0x0000FFFFFFFFFFFF;
	uint64 *x=(uint64*)&t.mem[z];
	*x=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void mov_m_mmw8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif

	register uint64 x=t.getNext48().toInt();

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	t.mem[x]=t.mem[y];
}
void mov_m_mmw16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif

	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint16*)&t.mem[y]);
}
void mov_m_mmw32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif

	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint32*)&t.mem[y]);
}
void mov_m_mmw48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif

	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint48*)&t.mem[y]);
}
void mov_m_mmw64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif

	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];

	uint32 inc=t.getNext32();
	register uint64 y=t.workspace[t.getNext8()]+inc;
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint64*)&t.mem[y]);
}
void mov_w_mmw8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif

	uint8 *x=(uint8*)&t.workspace[t.getNext8()];

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	*x=t.mem[y];
}
void mov_w_mmw16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif

	uint16 *x=(uint16*)&t.workspace[t.getNext8()];

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint16*)&t.mem[y]);
}
void mov_w_mmw32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif

	uint32 *x=(uint32*)&t.workspace[t.getNext8()];

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint32*)&t.mem[y]);
}
void mov_w_mmw48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif

	uint48 *x=(uint48*)&t.workspace[t.getNext8()];

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	*x=*((uint48*)&t.mem[y]);
}
void mov_w_mmw64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(13))return;
#endif

	register uint8 v=t.getNext8();

	register uint64 y=t.getNext32();
	y+=t.workspace[t.getNext8()];
	y&=0x0000FFFFFFFFFFFF;

	t.workspace[v]=*((uint64*)&t.mem[y]);
}
void mov_mmw_w8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(8))return;
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	t.mem[z]=(uint8)t.workspace[t.getNext8()];
}
void mov_mmw_w16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(8))return;
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	uint16 *x=(uint16*)&t.mem[z];
	*x=*((uint16*)&t.workspace[t.getNext8()]);
}
void mov_mmw_w32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(8))return;
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	uint32 *x=(uint32*)&t.mem[z];
	*x=*((uint32*)&t.workspace[t.getNext8()]);
}
void mov_mmw_w48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(8))return;
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	uint48 *x=(uint48*)&t.mem[z];
	*x=*((uint48*)&t.workspace[t.getNext8()]);
}
void mov_mmw_w64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(8))return;
#endif
	register uint64 z=t.getNext32();
	z+=t.workspace[t.getNext8()];
	z&=0x0000FFFFFFFFFFFF;
	uint64 *x=(uint64*)&t.mem[z];
	*x=t.workspace[t.getNext8()];
}
void mov_mmw_mmw8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
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
	if(t.checkUseCode(12))return;
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
	if(t.checkUseCode(12))return;
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
	if(t.checkUseCode(12))return;
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
	if(t.checkUseCode(12))return;
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

