/*
 * mov.h
 *
 *  Created on: 6 de mar de 2019
 *      Author: lhlag
 */

#ifndef OPCODES_MOV_H_
#define OPCODES_MOV_H_


	void mov_mmww_mmww8(Thread&);
	void mov_mmww_mmww16(Thread&);
	void mov_mmww_mmww32(Thread&);
	void mov_mmww_mmww48(Thread&);
	void mov_mmww_mmww64(Thread&);

	void mov_mmww_w8(Thread&);
	void mov_mmww_w16(Thread&);
	void mov_mmww_w32(Thread&);
	void mov_mmww_w48(Thread&);
	void mov_mmww_w64(Thread&);

	void mov_w_mmww8(Thread&);
	void mov_w_mmww16(Thread&);
	void mov_w_mmww32(Thread&);
	void mov_w_mmww48(Thread&);
	void mov_w_mmww64(Thread&);

	void mov_mmww_c8(Thread&);
	void mov_mmww_c16(Thread&);
	void mov_mmww_c32(Thread&);
	void mov_mmww_c48(Thread&);
	void mov_mmww_c64(Thread&);

	void mov_m_mmww8(Thread&);
	void mov_m_mmww16(Thread&);
	void mov_m_mmww32(Thread&);
	void mov_m_mmww48(Thread&);
	void mov_m_mmww64(Thread&);

	void mov_mmww_m8(Thread&);
	void mov_mmww_m16(Thread&);
	void mov_mmww_m32(Thread&);
	void mov_mmww_m48(Thread&);
	void mov_mmww_m64(Thread&);

	void mov_mmww_mmw8(Thread&);
	void mov_mmww_mmw16(Thread&);
	void mov_mmww_mmw32(Thread&);
	void mov_mmww_mmw48(Thread&);
	void mov_mmww_mmw64(Thread&);

	void mov_mmw_mmww8(Thread&);
	void mov_mmw_mmww16(Thread&);
	void mov_mmw_mmww32(Thread&);
	void mov_mmw_mmww48(Thread&);
	void mov_mmw_mmww64(Thread&);



	void cmov_ig_w_c8(Thread&);
	void cmov_ig_w_c16(Thread&);
	void cmov_ig_w_c32(Thread&);
	void cmov_ig_w_c48(Thread&);
	void cmov_ig_w_c64(Thread&);

	void cmov_di_w_c8(Thread&);
	void cmov_di_w_c16(Thread&);
	void cmov_di_w_c32(Thread&);
	void cmov_di_w_c48(Thread&);
	void cmov_di_w_c64(Thread&);

	void cmov_ma_w_c8(Thread&);
	void cmov_ma_w_c16(Thread&);
	void cmov_ma_w_c32(Thread&);
	void cmov_ma_w_c48(Thread&);
	void cmov_ma_w_c64(Thread&);

	void cmov_me_w_c8(Thread&);
	void cmov_me_w_c16(Thread&);
	void cmov_me_w_c32(Thread&);
	void cmov_me_w_c48(Thread&);
	void cmov_me_w_c64(Thread&);

	void cmov_ma_ig_w_c8(Thread&);
	void cmov_ma_ig_w_c16(Thread&);
	void cmov_ma_ig_w_c32(Thread&);
	void cmov_ma_ig_w_c48(Thread&);
	void cmov_ma_ig_w_c64(Thread&);

	void cmov_me_ig_w_c8(Thread&);
	void cmov_me_ig_w_c16(Thread&);
	void cmov_me_ig_w_c32(Thread&);
	void cmov_me_ig_w_c48(Thread&);
	void cmov_me_ig_w_c64(Thread&);

	void cmov_ig_w_w8(Thread&);
	void cmov_ig_w_w16(Thread&);
	void cmov_ig_w_w32(Thread&);
	void cmov_ig_w_w48(Thread&);
	void cmov_ig_w_w64(Thread&);

	void cmov_di_w_w8(Thread&);
	void cmov_di_w_w16(Thread&);
	void cmov_di_w_w32(Thread&);
	void cmov_di_w_w48(Thread&);
	void cmov_di_w_w64(Thread&);

	void cmov_ma_w_w8(Thread&);
	void cmov_ma_w_w16(Thread&);
	void cmov_ma_w_w32(Thread&);
	void cmov_ma_w_w48(Thread&);
	void cmov_ma_w_w64(Thread&);

	void cmov_me_w_w8(Thread&);
	void cmov_me_w_w16(Thread&);
	void cmov_me_w_w32(Thread&);
	void cmov_me_w_w48(Thread&);
	void cmov_me_w_w64(Thread&);

	void cmov_ma_ig_w_w8(Thread&);
	void cmov_ma_ig_w_w16(Thread&);
	void cmov_ma_ig_w_w32(Thread&);
	void cmov_ma_ig_w_w48(Thread&);
	void cmov_ma_ig_w_w64(Thread&);

	void cmov_me_ig_w_w8(Thread&);
	void cmov_me_ig_w_w16(Thread&);
	void cmov_me_ig_w_w32(Thread&);
	void cmov_me_ig_w_w48(Thread&);
	void cmov_me_ig_w_w64(Thread&);



	void mov_m_c8(Thread&);
	void mov_m_c16(Thread&);
	void mov_m_c32(Thread&);
	void mov_m_c48(Thread&);
	void mov_m_c64(Thread&);

	void mov_m_m8(Thread&);
	void mov_m_m16(Thread&);
	void mov_m_m32(Thread&);
	void mov_m_m48(Thread&);
	void mov_m_m64(Thread&);

	void mov_m_w8(Thread&);
	void mov_m_w16(Thread&);
	void mov_m_w32(Thread&);
	void mov_m_w48(Thread&);
	void mov_m_w64(Thread&);

	void mov_w_m8(Thread&);
	void mov_w_m16(Thread&);
	void mov_w_m32(Thread&);
	void mov_w_m48(Thread&);
	void mov_w_m64(Thread&);

	void mov_w_c8(Thread&);
	void mov_w_c16(Thread&);
	void mov_w_c32(Thread&);
	void mov_w_c48(Thread&);
	void mov_w_c64(Thread&);


	void c_mov_w_w8(CodeHolder*);
	void c_mov_w_w16(CodeHolder *ch);
	void c_mov_w_w32(CodeHolder *ch);
	void c_mov_w_w48(CodeHolder *ch);
	void c_mov_w_w64(CodeHolder *ch);


	void mov_w_w8(Thread&);
	void mov_w_w16(Thread&);
	void mov_w_w32(Thread&);
	void mov_w_w48(Thread&);
	void mov_w_w64(Thread&);

//////////-----------------------


	void mov_mmw_c8(Thread&);
	void mov_mmw_c16(Thread&);
	void mov_mmw_c32(Thread&);
	void mov_mmw_c48(Thread&);
	void mov_mmw_c64(Thread&);

	void mov_mmw_m8(Thread&);
	void mov_mmw_m16(Thread&);
	void mov_mmw_m32(Thread&);
	void mov_mmw_m48(Thread&);
	void mov_mmw_m64(Thread&);

	void mov_m_mmw8(Thread&);
	void mov_m_mmw16(Thread&);
	void mov_m_mmw32(Thread&);
	void mov_m_mmw48(Thread&);
	void mov_m_mmw64(Thread&);

	void mov_mmw_mmw8(Thread&);
	void mov_mmw_mmw16(Thread&);
	void mov_mmw_mmw32(Thread&);
	void mov_mmw_mmw48(Thread&);
	void mov_mmw_mmw64(Thread&);

	void mov_mmw_w8(Thread&);
	void mov_mmw_w16(Thread&);
	void mov_mmw_w32(Thread&);
	void mov_mmw_w48(Thread&);
	void mov_mmw_w64(Thread&);

	void mov_w_mmw8(Thread&);
	void mov_w_mmw16(Thread&);
	void mov_w_mmw32(Thread&);
	void mov_w_mmw48(Thread&);
	void mov_w_mmw64(Thread&);


////
	#define createFuncOnlyNumber(B) B(8);\
		B(16);\
		B(32);\
		B(48);\
		B(64);

	#define mov_rrw_w(B) void mov_rrw_w##B(Thread&);
	createFuncOnlyNumber(mov_rrw_w);

	#define mov_w_rrw(B) void mov_w_rrw##B(Thread&);
	createFuncOnlyNumber(mov_w_rrw);

	#define mov_rrw_rrw(B) void mov_rrw_rrw##B(Thread&);
	createFuncOnlyNumber(mov_rrw_rrw);

	#define mov_rrw_c(B) void mov_rrw_c##B(Thread&);
	createFuncOnlyNumber(mov_rrw_c);

#endif /* OPCODES_MOV_H_ */
