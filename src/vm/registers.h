#ifndef _SOFT_VM_REGISTERS_H
#define _SOFT_VM_REGISTERS_H

#include <stdlib.h>

#define SOFT_VM_NUM_REGS 8

#define SOFT_VM_REGISTER_TABLE \
	X(rax) X(rbx) X(rcx) X(rdx) \
	X(rdi) X(rsi) X(rsp) X(rbp)

#define X(y) soft_##y,
enum SOFT_VM_REGISTERS {
	SOFT_VM_REGISTER_TABLE
};
#undef X

extern char * soft_vm_registers[];
extern size_t num_soft_vm_registers;

#endif // _SOFT_VM_REGISTERS_H
