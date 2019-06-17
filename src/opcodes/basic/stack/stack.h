/*
 * caller.h
 *
 *  Created on: 16 de mar de 2019
 *      Author: lhlag
 */

#ifndef OPCODES_CALLER_H_
#define OPCODES_CALLER_H_

	void call_c(Thread &t);
	void call_m(Thread &t);
	void call_w(Thread &t);

	void ret(Thread &t);


	void call_ctx_c(Thread &t);
	void call_ctx_w(Thread &t);


	void push_w(Thread &t);
	void push_c(Thread &t);


	void pop_w(Thread &t);



#endif /* OPCODES_CALLER_H_ */
