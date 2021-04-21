
#include "../../../class/Thread.h"




void dd_w_c_8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x>>=y;
}
void dd_w_c_16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x>>=y;
}
void dd_w_c_32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x>>=y;
}
void dd_w_c_48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x>>=y;
}
void dd_w_c_64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x>>=y;
}
void de_w_c_8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x<<=y;
}
void de_w_c_16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x<<=y;
}
void de_w_c_32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x<<=y;
}
void de_w_c_48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x<<=y;
}
void de_w_c_64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	uint8 y=t.getNext8();
	*x<<=y;
}


void dd_w_w_8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x>>=y;
}
void dd_w_w_16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x>>=y;
}
void dd_w_w_32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x>>=y;
}
void dd_w_w_48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x>>=y;
}
void dd_w_w_64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x>>=y;
}
void de_w_w_8(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint8 *x=(uint8*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x<<=y;
}
void de_w_w_16(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint16 *x=(uint16*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x<<=y;
}
void de_w_w_32(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint32 *x=(uint32*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x<<=y;
}
void de_w_w_48(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint48 *x=(uint48*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x<<=y;
}
void de_w_w_64(Thread &t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	uint64 *x=(uint64*)&t.workspace[t.getNext8()];
	uint8 y=(uint8)t.workspace[t.getNext8()];
	*x<<=y;
}

