/*
 * jmp
 *
 *  Created on: 6 de mar de 2019
 *      Author: lhlag
 */


#include "../../../class/Thread.h"


#define IGUAL 1<<0
#define MAIOR 1<<1
#define MENOR 1<<2

//| opcode 16 | local do jmp 32 |


void jmp_ctx_c(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 ctx=uint16(t.workspace[t.getNext8()]);
	uint32 pon=t.getNext32();
#ifndef _FAST_MODE
	if(t.getVirtualMachine().checkContext(ctx)==0){
		t.error_flags|=INVALID_CHANGE_CONTEXT_;
		std::cout << "[ERROR] - Erro ao entrar em um Context inexistente. (ID= " << ctx << ")" << std::endl;
		return;
	}
#endif
	Context &ct=t.getVirtualMachine().getContext(ctx);
	t.changeContext(&ct);
	t.setPontCode(pon);
	t.checkUseCode(2);
}
void jmp_ctx_w(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(2))return;
#endif
	uint16 ctx=uint16(t.workspace[t.getNext8()]);
	uint32 pon=uint32(t.workspace[t.getNext8()]);
#ifndef _FAST_MODE
	if(t.getVirtualMachine().checkContext(ctx)==0){
		t.error_flags|=INVALID_CHANGE_CONTEXT_;
		std::cout << "[ERROR] - Erro ao entrar em um Context inexistente. (ID= " << ctx << ")" << std::endl;
		return;
	}
#endif
	Context &ct=t.getVirtualMachine().getContext(ctx);
	t.changeContext(&ct);
	t.setPontCode(pon);
	t.checkUseCode(2);
}

void jmp_c(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	t.setPontCode(t.getNext32());
#ifndef _FAST_MODE
	if(t.checkUseCode(2))return;
#endif
}

//| opcode 16 | memoria para jmp 48 |

void jmp_m(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(6))return;
#endif
	t.setPontCode(*((uint32*)&t.mem[t.getNext48().toInt()]));
#ifndef _FAST_MODE
	if(t.checkUseCode(2))return;
#endif
}

//| opcode 16 | workspace para jmp 8 |

void jmp_w(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	t.setPontCode(*((uint32*)&t.workspace[t.getNext8()]));
#ifndef _FAST_MODE
	if(t.checkUseCode(2))return;
#endif
}


/*
000 =
100 >
010 <
110 !=
001 >=
101 <=
011 &
111 |
*/

//| opcode 16 | local do jmp 32 | cmp memoria 48 | cmp constante ? |


void cmp_m_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint8 x=t.mem[t.getNext48().toInt()];
	register uint8 p=t.getNext8();
	t.compare_flags=0;

	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	register uint16 x=*((uint16*)&t.mem[t.getNext48().toInt()]);
	register uint16 p=t.getNext16();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
#endif
	register uint32 x=*((uint32*)&t.mem[t.getNext48().toInt()]);
	register uint32 p=t.getNext32();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register uint64 x=((uint48*)&t.mem[t.getNext48().toInt()])->toInt();
	register uint64 p=t.getNext48().toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	register uint64 x=*((uint64*)&t.mem[t.getNext48().toInt()]);
	register uint64 p=t.getNext64();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void cmp_m_m_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register uint8 x=t.mem[t.getNext48().toInt()];
	register uint8 p=t.mem[t.getNext48().toInt()];
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_m_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register uint16 x=*((uint16*)&t.mem[t.getNext48().toInt()]);
	register uint16 p=*((uint16*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_m_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register uint32 x=*((uint32*)&t.mem[t.getNext48().toInt()]);
	register uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_m_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register uint64 x=((uint48*)&t.mem[t.getNext48().toInt()])->toInt();
	register uint64 p=((uint48*)&t.mem[t.getNext48().toInt()])->toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_m_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register uint64 x=*((uint64*)&t.mem[t.getNext48().toInt()]);
	register uint64 p=*((uint64*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void cmp_m_w_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint8 x=t.mem[t.getNext48().toInt()];
	register uint8 p=t.workspace[t.getNext8()];
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_w_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint16 x=*((uint16*)&t.mem[t.getNext48().toInt()]);
	register uint16 p=*((uint16*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_w_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint32 x=*((uint32*)&t.mem[t.getNext48().toInt()]);
	register uint32 p=*((uint32*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_w_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint64 x=((uint48*)&t.mem[t.getNext48().toInt()])->toInt();
	register uint64 p=((uint48*)&t.workspace[t.getNext8()])->toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_w_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint64 x=*((uint64*)&t.mem[t.getNext48().toInt()]);
	register uint64 p=*((uint64*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}


void cmp_w_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint8 x=t.workspace[t.getNext8()];
	register uint8 p=t.getNext8();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	register uint16 x=*((uint16*)&t.workspace[t.getNext8()]);
	register uint16 p=t.getNext16();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	register uint32 x=*((uint32*)&t.workspace[t.getNext8()]);
	register uint32 p=t.getNext32();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint64 x=((uint48*)&t.workspace[t.getNext8()])->toInt();
	register uint64 p=t.getNext48().toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	register uint64 x=*((uint64*)&t.workspace[t.getNext8()]);
	register uint64 p=t.getNext64();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void cmp_w_m_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint8 x=t.workspace[t.getNext8()];
	register uint8 p=t.mem[t.getNext48().toInt()];
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_m_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint16 x=*((uint16*)&t.workspace[t.getNext8()]);
	register uint16 p=*((uint16*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_m_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint32 x=*((uint32*)&t.workspace[t.getNext8()]);
	register uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_m_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint64 x=((uint48*)&t.workspace[t.getNext8()])->toInt();
	register uint64 p=((uint48*)&t.mem[t.getNext48().toInt()])->toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_m_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register uint64 x=*((uint64*)&t.workspace[t.getNext8()]);
	register uint64 p=*((uint64*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void cmp_w_w_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint8 x=t.workspace[t.getNext8()];
	register uint8 p=t.workspace[t.getNext8()];
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_w_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint16 x=*((uint16*)&t.workspace[t.getNext8()]);
	register uint16 p=*((uint16*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_w_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint32 x=*((uint32*)&t.workspace[t.getNext8()]);
	register uint32 p=*((uint32*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_w_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint64 x=((uint48*)&t.workspace[t.getNext8()])->toInt();
	register uint64 p=((uint48*)&t.workspace[t.getNext8()])->toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_w_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint64 x=*((uint64*)&t.workspace[t.getNext8()]);
	register uint64 p=*((uint64*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}


void cmp_m_c_i8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int8 x=t.mem[t.getNext48().toInt()];
	register int8 p=t.getNext8();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_c_i16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	register int16 x=*((int16*)&t.mem[t.getNext48().toInt()]);
	register int16 p=t.getNext16();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_c_i32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
#endif
	register int32 x=*((int32*)&t.mem[t.getNext48().toInt()]);
	register int32 p=t.getNext32();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_c_i48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register int64 x=((int48*)&t.mem[t.getNext48().toInt()])->toInt();
	register int64 p=t.getNext48().toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_c_i64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	register int64 x=*((int64*)&t.mem[t.getNext48().toInt()]);
	register int64 p=t.getNext64();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void cmp_m_m_i8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register int8 x=t.mem[t.getNext48().toInt()];
	register int8 p=t.mem[t.getNext48().toInt()];
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_m_i16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register int16 x=*((int16*)&t.mem[t.getNext48().toInt()]);
	register int16 p=*((int16*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_m_i32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register int32 x=*((int32*)&t.mem[t.getNext48().toInt()]);
	register int32 p=*((int32*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_m_i48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register int64 x=((int48*)&t.mem[t.getNext48().toInt()])->toInt();
	register int64 p=((int48*)&t.mem[t.getNext48().toInt()])->toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_m_i64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	register int64 x=*((int64*)&t.mem[t.getNext48().toInt()]);
	register int64 p=*((int64*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void cmp_m_w_i8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int8 x=t.mem[t.getNext48().toInt()];
	register int8 p=t.workspace[t.getNext8()];
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_w_i16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int16 x=*((int16*)&t.mem[t.getNext48().toInt()]);
	register int16 p=*((int16*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_w_i32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int32 x=*((int32*)&t.mem[t.getNext48().toInt()]);
	register int32 p=*((int32*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_w_i48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int64 x=((int48*)&t.mem[t.getNext48().toInt()])->toInt();
	register int64 p=((int48*)&t.workspace[t.getNext8()])->toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_m_w_i64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int64 x=*((int64*)&t.mem[t.getNext48().toInt()]);
	register int64 p=*((int64*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}


void cmp_w_c_i8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	std::cout<< "Chegou aqui";

	register int8 x=t.workspace[t.getNext8()];
	register int8 p=t.getNext8();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_c_i16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	register int16 x=*((int16*)&t.workspace[t.getNext8()]);
	register int16 p=t.getNext16();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_c_i32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	register int32 x=*((int32*)&t.workspace[t.getNext8()]);
	register int32 p=t.getNext32();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_c_i48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int64 x=((int48*)&t.workspace[t.getNext8()])->toInt();
	register int64 p=t.getNext48().toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_c_i64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	register int64 x=*((int64*)&t.workspace[t.getNext8()]);
	register int64 p=t.getNext64();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void cmp_w_m_i8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int8 x=t.workspace[t.getNext8()];
	register int8 p=t.mem[t.getNext48().toInt()];
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_m_i16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int16 x=*((int16*)&t.workspace[t.getNext8()]);
	register int16 p=*((int16*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_m_i32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int32 x=*((int32*)&t.workspace[t.getNext8()]);
	register int32 p=*((int32*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_m_i48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int64 x=((int48*)&t.workspace[t.getNext8()])->toInt();
	register int64 p=((int48*)&t.mem[t.getNext48().toInt()])->toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_m_i64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	register int64 x=*((int64*)&t.workspace[t.getNext8()]);
	register int64 p=*((int64*)&t.mem[t.getNext48().toInt()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void cmp_w_w_i8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register int8 x=t.workspace[t.getNext8()];
	register int8 p=t.workspace[t.getNext8()];
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_w_i16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register int16 x=*((int16*)&t.workspace[t.getNext8()]);
	register int16 p=*((int16*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_w_i32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register int32 x=*((int32*)&t.workspace[t.getNext8()]);
	register int32 p=*((int32*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_w_i48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register int64 x=((int48*)&t.workspace[t.getNext8()])->toInt();
	register int64 p=((int48*)&t.workspace[t.getNext8()])->toInt();
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}
void cmp_w_w_i64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register int64 x=*((int64*)&t.workspace[t.getNext8()]);
	register int64 p=*((int64*)&t.workspace[t.getNext8()]);
	t.compare_flags=0;
	if(x<p)t.compare_flags|=MENOR;
	else if(x>p)t.compare_flags|=MAIOR;
	else t.compare_flags|=IGUAL;
}

void jmp_c_ma(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint32 p=t.getNext32();
	if(t.compare_flags&MAIOR)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_c_me(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint32 p=t.getNext32();
	if(t.compare_flags&MENOR)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_c_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint32 p=t.getNext32();
	if(t.compare_flags&IGUAL)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_c_di(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	register uint32 p=t.getNext32();
	if(!(t.compare_flags&IGUAL))t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_c_ma_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=t.getNext32();
	if(t.compare_flags&(IGUAL|MAIOR))t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_c_me_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=t.getNext32();
	if(t.compare_flags&(IGUAL|MENOR) ){
		t.setPontCode(p);
	}
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}


void jmp_m_ma(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(6))return;
#endif
	register uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	if(t.compare_flags&MAIOR)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_m_me(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(6))return;
#endif
	register uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	if(t.compare_flags&MENOR)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_m_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(6))return;
#endif
	register uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	if(t.compare_flags&IGUAL)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_m_di(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(6))return;
#endif
	register uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	if(!(t.compare_flags&IGUAL))t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_m_ma_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	if(t.compare_flags&(IGUAL|MAIOR))t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_m_me_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=*((uint32*)&t.mem[t.getNext48().toInt()]);
	if(t.compare_flags&(IGUAL|MENOR) )t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}


void jmp_w_ma(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=*((uint32*)&t.workspace[t.getNext8()]);
	if(t.compare_flags&MAIOR)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_w_me(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=*((uint32*)&t.workspace[t.getNext8()]);
	if(t.compare_flags&MENOR)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_w_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=*((uint32*)&t.workspace[t.getNext8()]);
	if(t.compare_flags&IGUAL)t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_w_di(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(6))return;
#endif
	register uint32 p=*((uint32*)&t.workspace[t.getNext48().toInt()]);
	if(!(t.compare_flags&IGUAL))t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_w_ma_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=*((uint32*)&t.workspace[t.getNext8()]);
	if(t.compare_flags&(IGUAL|MAIOR))t.setPontCode(p);
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}
void jmp_w_me_ig(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(1))return;
#endif
	register uint32 p=*((uint32*)&t.workspace[t.getNext8()]);
	if(t.compare_flags&(IGUAL|MENOR)){
		t.setPontCode(p);
	}
#ifndef _FAST_MODE
	t.checkUseCode(2);
#endif

}

