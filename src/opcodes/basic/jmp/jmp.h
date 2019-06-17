/*
 * jmp.h
 *
 *  Created on: 6 de mar de 2019
 *      Author: lhlag
 */

#ifndef OPCODES_JMP_H_
#define OPCODES_JMP_H_

	// c/w | m/w | m/c/w

	void jmp_c(Thread &t);
	void jmp_m(Thread &t);
	void jmp_w(Thread &t);

	void jmp_ctx_c(Thread &t);
	void jmp_ctx_w(Thread &t);

	void cmp_m_c_ui8(Thread &t);
	void cmp_m_c_ui16(Thread &t);
	void cmp_m_c_ui32(Thread &t);
	void cmp_m_c_ui48(Thread &t);
	void cmp_m_c_ui64(Thread &t);

	void cmp_m_m_ui8(Thread &t);
	void cmp_m_m_ui16(Thread &t);
	void cmp_m_m_ui32(Thread &t);
	void cmp_m_m_ui48(Thread &t);
	void cmp_m_m_ui64(Thread &t);

	void cmp_m_w_ui8(Thread &t);
	void cmp_m_w_ui16(Thread &t);
	void cmp_m_w_ui32(Thread &t);
	void cmp_m_w_ui48(Thread &t);
	void cmp_m_w_ui64(Thread &t);

	void cmp_w_c_ui8(Thread &t);
	void cmp_w_c_ui16(Thread &t);
	void cmp_w_c_ui32(Thread &t);
	void cmp_w_c_ui48(Thread &t);
	void cmp_w_c_ui64(Thread &t);

	void cmp_w_m_ui8(Thread &t);
	void cmp_w_m_ui16(Thread &t);
	void cmp_w_m_ui32(Thread &t);
	void cmp_w_m_ui48(Thread &t);
	void cmp_w_m_ui64(Thread &t);

	void cmp_w_w_ui8(Thread &t);
	void cmp_w_w_ui16(Thread &t);
	void cmp_w_w_ui32(Thread &t);
	void cmp_w_w_ui48(Thread &t);
	void cmp_w_w_ui64(Thread &t);


	void cmp_m_c_i8(Thread &t);
	void cmp_m_c_i16(Thread &t);
	void cmp_m_c_i32(Thread &t);
	void cmp_m_c_i48(Thread &t);
	void cmp_m_c_i64(Thread &t);

	void cmp_m_m_i8(Thread &t);
	void cmp_m_m_i16(Thread &t);
	void cmp_m_m_i32(Thread &t);
	void cmp_m_m_i48(Thread &t);
	void cmp_m_m_i64(Thread &t);

	void cmp_m_w_i8(Thread &t);
	void cmp_m_w_i16(Thread &t);
	void cmp_m_w_i32(Thread &t);
	void cmp_m_w_i48(Thread &t);
	void cmp_m_w_i64(Thread &t);

	void cmp_w_c_i8(Thread &t);
	void cmp_w_c_i16(Thread &t);
	void cmp_w_c_i32(Thread &t);
	void cmp_w_c_i48(Thread &t);
	void cmp_w_c_i64(Thread &t);

	void cmp_w_m_i8(Thread &t);
	void cmp_w_m_i16(Thread &t);
	void cmp_w_m_i32(Thread &t);
	void cmp_w_m_i48(Thread &t);
	void cmp_w_m_i64(Thread &t);

	void cmp_w_w_i8(Thread &t);
	void cmp_w_w_i16(Thread &t);
	void cmp_w_w_i32(Thread &t);
	void cmp_w_w_i48(Thread &t);
	void cmp_w_w_i64(Thread &t);

	void jmp_c_ma(Thread &t);
	void jmp_c_me(Thread &t);
	void jmp_c_ig(Thread &t);
	void jmp_c_di(Thread &t);
	void jmp_c_ma_ig(Thread &t);
	void jmp_c_me_ig(Thread &t);

	void jmp_m_ma(Thread &t);
	void jmp_m_me(Thread &t);
	void jmp_m_ig(Thread &t);
	void jmp_m_di(Thread &t);
	void jmp_m_ma_ig(Thread &t);
	void jmp_m_me_ig(Thread &t);

	void jmp_w_ma(Thread &t);
	void jmp_w_me(Thread &t);
	void jmp_w_ig(Thread &t);
	void jmp_w_di(Thread &t);
	void jmp_w_ma_ig(Thread &t);
	void jmp_w_me_ig(Thread &t);


#endif /* OPCODES_JMP_H_ */
