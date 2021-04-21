/*
 * aritimetic
 *
 *  Created on: 11 de mar de 2019
 *      Author: lhlag
 */


#include "../../../class/Thread.h"

/*
 +
 -
 *
 /
 %

 /+%

	| opcode 16 | mem para onde ira ocorrer 48 | constante ? |
*/

void soma_m_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int64 x=t.getNext48().toInt();
	register int8 y=t.getNext8();
	t.mem[x]+=y;
}
void soma_m_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(10);
#endif
	register int16 *x=(int16*)&t.mem[t.getNext48().toInt()];
	*x+=t.getNext16();
}
void soma_m_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif
	register int32 *x=(int32*)&t.mem[t.getNext48().toInt()];
	*x+=t.getNext32();
}
void soma_m_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	register int48 *x=(int48*)&t.mem[t.getNext48().toInt()];
	*x+=t.getNext48();
}
void soma_m_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(16);
#endif
	register int64 *x=(int64*)&t.mem[t.getNext48().toInt()];
	*x+=t.getNext64();
}

void sub_m_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int64 x=t.getNext48().toInt();
	register int8 y=t.getNext8();
	t.mem[x]-=y;
}
void sub_m_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(10);
#endif
	register int16 *x=(int16*)&t.mem[t.getNext48().toInt()];
	*x-=t.getNext16();
}
void sub_m_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif
	register int32 *x=(int32*)&t.mem[t.getNext48().toInt()];
	*x-=t.getNext32();
}
void sub_m_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	register int48 *x=(int48*)&t.mem[t.getNext48().toInt()];
	*x-=t.getNext48();
}
void sub_m_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(16);
#endif
	register int64 *x=(int64*)&t.mem[t.getNext48().toInt()];
	*x-=t.getNext64();
}

void mul_m_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int64 x=t.getNext48().toInt();
	register int8 y=t.getNext8();
	t.mem[x]*=y;
}
void mul_m_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(10);
#endif
	register int16 *x=(int16*)&t.mem[t.getNext48().toInt()];
	*x*=t.getNext16();
}
void mul_m_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif
	register int32 *x=(int32*)&t.mem[t.getNext48().toInt()];
	*x*=t.getNext32();
}
void mul_m_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	register int48 *x=(int48*)&t.mem[t.getNext48().toInt()];
	*x*=t.getNext48();
}
void mul_m_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(16);
#endif
	register int64 *x=(int64*)&t.mem[t.getNext48().toInt()];
	*x*=t.getNext64();
}

void div_m_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int64 x=t.getNext48().toInt();
	register int8 y=t.getNext8();
	t.mem[x]/=y;
}
void div_m_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(10);
#endif
	register int16 *x=(int16*)&t.mem[t.getNext48().toInt()];
	*x/=t.getNext16();
}
void div_m_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif
	register int32 *x=(int32*)&t.mem[t.getNext48().toInt()];
	*x/=t.getNext32();
}
void div_m_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	register int48 *x=(int48*)&t.mem[t.getNext48().toInt()];
	*x/=t.getNext48();
}
void div_m_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(16);
#endif
	register int64 *x=(int64*)&t.mem[t.getNext48().toInt()];
	*x/=t.getNext64();
}

void mod_m_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int64 x=t.getNext48().toInt();
	register int8 y=t.getNext8();
	t.mem[x]%=y;
}
void mod_m_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(10);
#endif
	register int16 *x=(int16*)&t.mem[t.getNext48().toInt()];
	*x%=t.getNext16();
}
void mod_m_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(12);
#endif
	register int32 *x=(int32*)&t.mem[t.getNext48().toInt()];
	*x%=t.getNext32();
}
void mod_m_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(14);
#endif
	register int48 *x=(int48*)&t.mem[t.getNext48().toInt()];
	*x%=t.getNext48();
}
void mod_m_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(16);
#endif
	register int64 *x=(int64*)&t.mem[t.getNext48().toInt()];
	*x%=t.getNext64();
}







//| opcode 16 | workspace para onde vair ocorrer o resultado final | constante ? |


void soma_w_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x+=t.getNext8();
}
void soma_w_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x+=t.getNext16();
}
void soma_w_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(7);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x+=t.getNext32();
}
void soma_w_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x+=t.getNext48();
}
void soma_w_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(11);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]+=t.getNext64();
}

void sub_w_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x-=t.getNext8();
}
void sub_w_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x-=t.getNext16();
}
void sub_w_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(7);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x-=t.getNext32();
}
void sub_w_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x-=t.getNext48();
}
void sub_w_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(11);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]-=t.getNext64();
}

void mul_w_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x*=t.getNext8();
}
void mul_w_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x*=t.getNext16();
}
void mul_w_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(7);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x*=t.getNext32();
}
void mul_w_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x*=t.getNext48();
}
void mul_w_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(11);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]*=t.getNext64();
}

void div_w_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x/=t.getNext8();
}
void div_w_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x/=t.getNext16();
}
void div_w_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(7);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x/=t.getNext32();
}
void div_w_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x/=t.getNext48();
}
void div_w_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(11);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]/=t.getNext64();
}

void mod_w_c_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x%=t.getNext8();
}
void mod_w_c_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x%=t.getNext16();
}
void mod_w_c_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(7);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x%=t.getNext32();
}
void mod_w_c_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x%=t.getNext48();
}
void mod_w_c_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(11);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]%=t.getNext64();
}










void soma_w_m_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x+=t.mem[t.getNext48().toInt()];
}
void soma_w_m_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x+=*((int16*)&t.mem[t.getNext48().toInt()]);
}
void soma_w_m_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x+=*((int32*)&t.mem[t.getNext48().toInt()]);
}
void soma_w_m_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x+=*((int48*)&t.mem[t.getNext48().toInt()]);
}
void soma_w_m_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]+=*((int64*)&t.mem[t.getNext48().toInt()]);
}

void sub_w_m_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x-=t.mem[t.getNext48().toInt()];
}
void sub_w_m_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x-=*((int16*)&t.mem[t.getNext48().toInt()]);
}
void sub_w_m_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x-=*((int32*)&t.mem[t.getNext48().toInt()]);
}
void sub_w_m_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x-=*((int48*)&t.mem[t.getNext48().toInt()]);
}
void sub_w_m_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]-=*((int64*)&t.mem[t.getNext48().toInt()]);
}

void mul_w_m_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x*=t.mem[t.getNext48().toInt()];
}
void mul_w_m_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x*=*((int16*)&t.mem[t.getNext48().toInt()]);
}
void mul_w_m_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x*=*((int32*)&t.mem[t.getNext48().toInt()]);
}
void mul_w_m_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x*=*((int48*)&t.mem[t.getNext48().toInt()]);
}
void mul_w_m_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]*=*((int64*)&t.mem[t.getNext48().toInt()]);
}

void div_w_m_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x/=t.mem[t.getNext48().toInt()];
}
void div_w_m_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x/=*((int16*)&t.mem[t.getNext48().toInt()]);
}
void div_w_m_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x/=*((int32*)&t.mem[t.getNext48().toInt()]);
}
void div_w_m_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x/=*((int48*)&t.mem[t.getNext48().toInt()]);
}
void div_w_m_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]/=*((int64*)&t.mem[t.getNext48().toInt()]);
}

void mod_w_m_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x%=t.mem[t.getNext48().toInt()];
}
void mod_w_m_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x%=*((int16*)&t.mem[t.getNext48().toInt()]);
}
void mod_w_m_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x%=*((int32*)&t.mem[t.getNext48().toInt()]);
}
void mod_w_m_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x%=*((int48*)&t.mem[t.getNext48().toInt()]);
}
void mod_w_m_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(9);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]%=*((int64*)&t.mem[t.getNext48().toInt()]);
}









void soma_w_w_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x+=t.workspace[t.getNext8()];
}
void soma_w_w_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x+=*((int16*)&t.workspace[t.getNext8()]);
}
void soma_w_w_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x+=*((int32*)&t.workspace[t.getNext8()]);
}
void soma_w_w_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x+=*((int48*)&t.workspace[t.getNext8()]);
}
void soma_w_w_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]+=t.workspace[t.getNext8()];
}

void sub_w_w_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x-=t.workspace[t.getNext8()];
}
void sub_w_w_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x-=*((int16*)&t.workspace[t.getNext8()]);
}
void sub_w_w_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x-=*((int32*)&t.workspace[t.getNext8()]);
}
void sub_w_w_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x-=*((int48*)&t.workspace[t.getNext8()]);
}
void sub_w_w_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]-=t.workspace[t.getNext8()];
}

void mul_w_w_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x*=t.workspace[t.getNext8()];
}
void mul_w_w_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x*=*((int16*)&t.workspace[t.getNext8()]);
}
void mul_w_w_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x*=*((int32*)&t.workspace[t.getNext8()]);
}
void mul_w_w_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x*=*((int48*)&t.workspace[t.getNext8()]);
}
void mul_w_w_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]*=t.workspace[t.getNext8()];
}

void div_w_w_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x/=t.workspace[t.getNext8()];
}
void div_w_w_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x/=*((int16*)&t.workspace[t.getNext8()]);
}
void div_w_w_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x/=*((int32*)&t.workspace[t.getNext8()]);
}
void div_w_w_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x/=*((int48*)&t.workspace[t.getNext8()]);
}
void div_w_w_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]/=t.workspace[t.getNext8()];
}

void mod_w_w_i8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int8 *x=(int8*)&t.workspace[t.getNext8()];
	*x%=t.workspace[t.getNext8()];
}
void mod_w_w_i16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int16 *x=(int16*)&t.workspace[t.getNext8()];
	*x%=*((int16*)&t.workspace[t.getNext8()]);
}
void mod_w_w_i32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int32 *x=(int32*)&t.workspace[t.getNext8()];
	*x%=*((int32*)&t.workspace[t.getNext8()]);
}
void mod_w_w_i48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register int48 *x=(int48*)&t.workspace[t.getNext8()];
	*x%=*((int48*)&t.workspace[t.getNext8()]);
}
void mod_w_w_i64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register uint8 x=t.getNext8();
	t.workspace[(uint16)x]%=t.workspace[t.getNext8()];
}


