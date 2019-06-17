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

void soma_m_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]+=y;
}
void soma_m_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x+=t.getNext16();
}
void soma_m_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x+=t.getNext32();
}
void soma_m_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x+=t.getNext48();
}
void soma_m_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x+=t.getNext64();
}

void sub_m_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]-=y;
}
void sub_m_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x-=t.getNext16();
}
void sub_m_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x-=t.getNext32();
}
void sub_m_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x-=t.getNext48();
}
void sub_m_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x-=t.getNext64();
}

void mul_m_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]*=y;
}
void mul_m_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x*=t.getNext16();
}
void mul_m_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x*=t.getNext32();
}
void mul_m_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x*=t.getNext48();
}
void mul_m_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x*=t.getNext64();
}

void div_m_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]/=y;
}
void div_m_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x/=t.getNext16();
}
void div_m_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x/=t.getNext32();
}
void div_m_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x/=t.getNext48();
}
void div_m_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x/=t.getNext64();
}

void mod_m_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint64 x=t.getNext48().toInt();
	uint8 y=t.getNext8();
	t.mem[x]%=y;
}
void mod_m_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(10))return;
#endif
	uint16 *x=(uint16*)&t.mem[t.getNext48().toInt()];
	*x%=t.getNext16();
}
void mod_m_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(12))return;
#endif
	uint32 *x=(uint32*)&t.mem[t.getNext48().toInt()];
	*x%=t.getNext32();
}
void mod_m_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(14))return;
#endif
	uint48 *x=(uint48*)&t.mem[t.getNext48().toInt()];
	*x%=t.getNext48();
}
void mod_m_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(16))return;
#endif
	uint64 *x=(uint64*)&t.mem[t.getNext48().toInt()];
	*x%=t.getNext64();
}







//| opcode 16 | workspace para onde vair ocorrer o resultado final | constante ? |


void soma_w_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x+=t.getNext8();
}
void soma_w_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x+=t.getNext16();
}
void soma_w_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x+=t.getNext32();
}
void soma_w_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x+=t.getNext48();
}
void soma_w_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]+=t.getNext64();
}

void sub_w_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x-=t.getNext8();
}
void sub_w_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x-=t.getNext16();
}
void sub_w_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x-=t.getNext32();
}
void sub_w_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x-=t.getNext48();
}
void sub_w_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]-=t.getNext64();
}

void mul_w_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x*=t.getNext8();
}
void mul_w_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x*=t.getNext16();
}
void mul_w_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x*=t.getNext32();
}
void mul_w_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x*=t.getNext48();
}
void mul_w_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]*=t.getNext64();
}

void div_w_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x/=t.getNext8();
}
void div_w_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x/=t.getNext16();
}
void div_w_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x/=t.getNext32();
}
void div_w_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x/=t.getNext48();
}
void div_w_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]/=t.getNext64();
}

void mod_w_c_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x%=t.getNext8();
}
void mod_w_c_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(5))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x%=t.getNext16();
}
void mod_w_c_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(7))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x%=t.getNext32();
}
void mod_w_c_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x%=t.getNext48();
}
void mod_w_c_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(11))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]%=t.getNext64();
}










void soma_w_m_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x+=t.mem[t.getNext48().toInt()];
}
void soma_w_m_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x+=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void soma_w_m_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x+=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void soma_w_m_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x+=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void soma_w_m_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]+=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void sub_w_m_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x-=t.mem[t.getNext48().toInt()];
}
void sub_w_m_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x-=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void sub_w_m_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x-=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void sub_w_m_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x-=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void sub_w_m_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]-=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void mul_w_m_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x*=t.mem[t.getNext48().toInt()];
}
void mul_w_m_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x*=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void mul_w_m_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x*=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void mul_w_m_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x*=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void mul_w_m_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]*=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void div_w_m_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x/=t.mem[t.getNext48().toInt()];
}
void div_w_m_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x/=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void div_w_m_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x/=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void div_w_m_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x/=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void div_w_m_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]/=*((uint64*)&t.mem[t.getNext48().toInt()]);
}

void mod_w_m_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x%=t.mem[t.getNext48().toInt()];
}
void mod_w_m_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x%=*((uint16*)&t.mem[t.getNext48().toInt()]);
}
void mod_w_m_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x%=*((uint32*)&t.mem[t.getNext48().toInt()]);
}
void mod_w_m_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x%=*((uint48*)&t.mem[t.getNext48().toInt()]);
}
void mod_w_m_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(9))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]%=*((uint64*)&t.mem[t.getNext48().toInt()]);
}









void soma_w_w_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x+=t.workspace[t.getNext8()];
}
void soma_w_w_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x+=*((uint16*)&t.workspace[t.getNext8()]);
}
void soma_w_w_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x+=*((uint32*)&t.workspace[t.getNext8()]);
}
void soma_w_w_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x+=*((uint48*)&t.workspace[t.getNext8()]);
}
void soma_w_w_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]+=t.workspace[t.getNext8()];
}

void sub_w_w_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x-=t.workspace[t.getNext8()];
}
void sub_w_w_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x-=*((uint16*)&t.workspace[t.getNext8()]);
}
void sub_w_w_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x-=*((uint32*)&t.workspace[t.getNext8()]);
}
void sub_w_w_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x-=*((uint48*)&t.workspace[t.getNext8()]);
}
void sub_w_w_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]-=t.workspace[t.getNext8()];
}

void mul_w_w_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x*=t.workspace[t.getNext8()];
}
void mul_w_w_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x*=*((uint16*)&t.workspace[t.getNext8()]);
}
void mul_w_w_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x*=*((uint32*)&t.workspace[t.getNext8()]);
}
void mul_w_w_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x*=*((uint48*)&t.workspace[t.getNext8()]);
}
void mul_w_w_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]*=t.workspace[t.getNext8()];
}

void div_w_w_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x/=t.workspace[t.getNext8()];
}
void div_w_w_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x/=*((uint16*)&t.workspace[t.getNext8()]);
}
void div_w_w_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x/=*((uint32*)&t.workspace[t.getNext8()]);
}
void div_w_w_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x/=*((uint48*)&t.workspace[t.getNext8()]);
}
void div_w_w_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]/=t.workspace[t.getNext8()];
}

void mod_w_w_ui8(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	*x%=t.workspace[t.getNext8()];
}
void mod_w_w_ui16(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	*x%=*((uint16*)&t.workspace[t.getNext8()]);
}
void mod_w_w_ui32(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	*x%=*((uint32*)&t.workspace[t.getNext8()]);
}
void mod_w_w_ui48(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	*x%=*((uint48*)&t.workspace[t.getNext8()]);
}
void mod_w_w_ui64(Thread &t){
#ifndef _FAST_MODE
	if(t.checkUseCode(4))return;
#endif
	uint8 x=t.getNext8();
	t.workspace[x]%=t.workspace[t.getNext8()];
}


