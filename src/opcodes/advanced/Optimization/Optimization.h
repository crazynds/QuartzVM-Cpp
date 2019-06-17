/*
 * Optimization.h
 *
 *  Created on: 20 de mar de 2019
 *      Author: lhlag
 */

#ifndef OPCODES_OPTIMIZATION_H_
#define OPCODES_OPTIMIZATION_H_
	//GERAL OPTIMIZATION

	void loop_c_w(Thread&);
	void loop_w_w(Thread&);

	void inc_w(Thread& t);
	void dec_w(Thread& t);
	void inc_m(Thread& t);
	void dec_m(Thread& t);


	void lea_w__w_w_c(Thread& t);
	void lea_w__w_w_w(Thread& t);
	void lea_w__w_w_1(Thread& t);
	void lea_w__w_w_2(Thread& t);
	void lea_w__w_w_4(Thread& t);
	void lea_w__w_w_8(Thread& t);
	void lea_w__w_w_16(Thread& t);
	void lea_w__w_w_32(Thread& t);
	void lea_w__w_w_64(Thread& t);


	void copy_m_m_c8(Thread&);
	void copy_m_m_w8(Thread&);
	void copy_m_m_c16(Thread&);
	void copy_m_m_w16(Thread&);
	void copy_m_m_c32(Thread&);
	void copy_m_m_w32(Thread&);
	void copy_m_m_c48(Thread&);
	void copy_m_m_w48(Thread&);
	void copy_m_m_c64(Thread&);
	void copy_m_m_w64(Thread&);


	void copy_mw_mw_c8(Thread&);
	void copy_mw_mw_w8(Thread&);
	void copy_mw_mw_c16(Thread&);
	void copy_mw_mw_w16(Thread&);
	void copy_mw_mw_c32(Thread&);
	void copy_mw_mw_w32(Thread&);
	void copy_mw_mw_c48(Thread&);
	void copy_mw_mw_w48(Thread&);
	void copy_mw_mw_c64(Thread&);
	void copy_mw_mw_w64(Thread&);

	//lea rdx,m[rax+rbx*n];
	//mova para rdx o endereço relativo de m[rax+rbx*n];

	// n pode ser 1,2,4,6,8,16


	//lea rdx,m[rax+rbx*4]


#endif /* OPCODES_OPTIMIZATION_H_ */
