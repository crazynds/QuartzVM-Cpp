/*
 * SysCall.h
 *
 *  Created on: 21 de abr de 2019
 *      Author: lhlag
 */

#ifndef SRC_OPCODES_SYSCALL_H_
#define SRC_OPCODES_SYSCALL_H_

void alloc_res(Thread &t);
void alloc_dinamic_res(Thread &t);
void free_res(Thread &t);
void realloc_res(Thread &t);
void ralloc_dinamic_res(Thread &t);


#endif /* SRC_OPCODES_SYSCALL_H_ */
