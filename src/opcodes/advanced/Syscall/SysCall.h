/*
 * SysCall.h
 *
 *  Created on: 21 de abr de 2019
 *      Author: lhlag
 */

#ifndef SRC_OPCODES_SYSCALL_H_
#define SRC_OPCODES_SYSCALL_H_

	void print_out_char_w(Thread&);
	void print_out_num_w(Thread&);
	void print_out_string_mmw(Thread&);
	void print_out_string_m(Thread&);
	void load_context_w_mw(Thread&);
	void get_context_id_w(Thread&);
	void check_context_id_w(Thread&);



	void test_func(Thread &t);
	void no_opcode(Thread &t);
	void sleep(Thread &t);
	void do_nothing(Thread &t);
	void end_running(Thread &t);


#endif /* SRC_OPCODES_SYSCALL_H_ */
