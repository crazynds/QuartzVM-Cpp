
#include "../../../class/Thread.h"


void copy_m_m_c8(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(18);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint32 val=t.getNext32();

	for(uint32 x=0;x<val;x++)t.mem[l++]=t.mem[p++];
}
void copy_m_m_w8(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(15);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint32 val=t.getNext8();

	for(uint32 x=0;x<t.workspace[val];x++)t.mem[l++]=t.mem[p++];
}
void copy_m_m_c16(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(18);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint32 val=t.getNext32();

	for(uint32 x=0;x<val*2;x++)t.mem[l++]=t.mem[p++];
}
void copy_m_m_w16(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(15);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint8 val=t.getNext8();

	for(uint32 x=0;x<t.workspace[val]*2;x++)t.mem[l++]=t.mem[p++];
}

void copy_m_m_c32(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(18);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint32 val=t.getNext32();

	for(uint32 x=0;x<val*4;x++)t.mem[l++]=t.mem[p++];
}
void copy_m_m_w32(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(15);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint8 val=t.getNext8();

	for(uint32 x=0;x<t.workspace[val]*4;x++)t.mem[l++]=t.mem[p++];
}

void copy_m_m_c48(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(18);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint32 val=t.getNext32();

	for(uint32 x=0;x<val*6;x++)t.mem[l++]=t.mem[p++];
}
void copy_m_m_w48(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(15);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint8 val=t.getNext8();

	for(uint32 x=0;x<t.workspace[val]*6;x++)t.mem[l++]=t.mem[p++];
}

void copy_m_m_c64(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(18);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint32 val=t.getNext32();

	for(uint32 x=0;x<val*8;x++)t.mem[l++]=t.mem[p++];
}
void copy_m_m_w64(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(15);
#endif
	uint64 l=t.getNext48().toInt();
	uint64 p=t.getNext48().toInt();
	uint8 val=t.getNext8();

	for(uint32 x=0;x<t.workspace[val]*8;x++)t.mem[l++]=t.mem[p++];
}
void copy_mw_mw_c8(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=t.getNext32();
	for(uint32 x=0;x<val;x++){
		t.mem[l++]=t.mem[p++];
	}
}
void copy_mw_mw_w8(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=(uint32)t.workspace[t.getNext8()];
	for(uint32 x=0;x<val;x++){
		t.mem[l++]=t.mem[p++];
	}
}
void copy_mw_mw_c16(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=t.getNext32();
	for(uint32 x=0;x<val*2;x++){
		t.mem[l++]=t.mem[p++];
	}
}
void copy_mw_mw_w16(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=(uint32)t.workspace[t.getNext8()];
	for(uint32 x=0;x<val*2;x++){
		t.mem[l++]=t.mem[p++];
	}
}

void copy_mw_mw_c32(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=t.getNext32();
	for(uint32 x=0;x<val*4;x++){
		t.mem[l++]=t.mem[p++];
	}
}
void copy_mw_mw_w32(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=(uint32)t.workspace[t.getNext8()];
	for(uint32 x=0;x<val*4;x++){
		t.mem[l++]=t.mem[p++];
	}
}

void copy_mw_mw_c48(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=t.getNext32();
	for(uint32 x=0;x<val*8;x++){
		t.mem[l++]=t.mem[p++];
	}
}
void copy_mw_mw_w48(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=(uint32)t.workspace[t.getNext8()];
	for(uint32 x=0;x<val*6;x++){
		t.mem[l++]=t.mem[p++];
	}
}

void copy_mw_mw_c64(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(8);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=t.getNext32();

	for(uint32 x=0;x<val*8;x++){
		t.mem[l++]=t.mem[p++];
	}
}
void copy_mw_mw_w64(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(5);
#endif
	uint64 l=uint48(t.workspace[t.getNext8()]).toInt();
	uint64 p=uint48(t.workspace[t.getNext8()]).toInt();
	uint32 val=(uint32)t.workspace[t.getNext8()];
	for(uint32 x=0;x<val*8;x++){
		t.mem[l++]=t.mem[p++];
	}
}


// | opcode 16 | constante 32 | register -- 8 | 

void loop_c_w(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(7);
#endif
	register uint32 l=t.getNext32();
	register uint8 p=t.getNext8();
	if(--t.workspace[p]>0){
		t.setPontCode(l);
	}
}

// | opcode 16 | register 8 | register -- 8 | 


void loop_w_w(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(4);
#endif
	register uint8 l=t.getNext8();
	register uint8 p=t.getNext8();
	if(--t.workspace[p]>0){
		t.setPontCode((uint32)t.workspace[l]);
	}
}


void inc_w(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(3);
#endif
	t.workspace[t.getNext8()]++;
}

void dec_w(Thread& t){
#ifndef _FAST_MODE
	t.checkUseCode(3);
#endif
	t.workspace[t.getNext8()]--;
}





void lea_w__w_w_c(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(13);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	register uint64 c=t.getNext64();
	
	b*=c;
	a+=b;
	t.workspace[send]=a;
}

void lea_w__w_w_w(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(6);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	register uint64 c=t.workspace[t.getNext8()];
	
	b*=c;
	a+=b;
	t.workspace[send]=a;
}

void lea_w__w_w_1(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(5);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	
	a+=b;
	t.workspace[send]=a;
}

void lea_w__w_w_2(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(5);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	
	b<<=1;
	a+=b;
	t.workspace[send]=a;
}

void lea_w__w_w_4(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(5);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	
	b<<=2;
	a+=b;
	t.workspace[send]=a;
}

void lea_w__w_w_8(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(5);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	
	b<<=3;
	a+=b;
	t.workspace[send]=a;
}

void lea_w__w_w_16(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(5);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	
	b<<=4;
	a+=b;
	t.workspace[send]=a;
}

void lea_w__w_w_32(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(5);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	
	b<<=5;
	a+=b;
	t.workspace[send]=a;
}

void lea_w__w_w_64(Thread& t){
	#ifndef _FAST_MODE
		t.checkUseCode(5);
	#endif
	uint8 send=t.getNext8();
	
	register uint64 a=t.workspace[t.getNext8()];
	register uint64 b=t.workspace[t.getNext8()];
	
	b<<=6;
	a+=b;
	t.workspace[send]=a;
}


	//lea rdx,m[rax+rbx*n];
	//mova para rdx o endereço relativo de m[rax+rbx*n];

	// n pode ser 1,2,4,6,8,16


	//lea rdx,m[rax+rbx*4]






