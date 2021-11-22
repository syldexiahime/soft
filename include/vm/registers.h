#ifndef _SOFT_VM_REGISTERS_H
#define _SOFT_VM_REGISTERS_H

#include <stdlib.h>

#define SOFT_VM_NUM_REGS 8

#define SOFT_VM_64BIT_REGISTER_TABLE \
	X(rax) X(rbx) X(rcx) X(rdx) \
	X(rdi) X(rsi) X(rsp) X(rbp)

#define SOFT_VM_32BIT_REGISTER_TABLE \
	X(eax) X(ebx) X(ecx) X(edx)

#define SOFT_VM_16BIT_REGISTER_TABLE \
	X(ax) X(bx) X(cx) X(dx)

#define SOFT_VM_8BIT_REGISTER_TABLE \
	X(al) X(bl) X(cl) X(dl)

#define X(y) soft_##y,
enum SOFT_VM_REGISTERS {
	soft_vm_register_enum_64bit = -1,
	SOFT_VM_64BIT_REGISTER_TABLE
	soft_vm_register_enum_32bit = -1,
	SOFT_VM_32BIT_REGISTER_TABLE
	soft_vm_register_enum_16bit = -1,
	SOFT_VM_16BIT_REGISTER_TABLE
	soft_vm_register_enum_8bit = -1,
	SOFT_VM_8BIT_REGISTER_TABLE
};
#undef X

#define X(y) #y,
static char * soft_vm_64bit_registers[] = {
	SOFT_VM_64BIT_REGISTER_TABLE
};

static char * soft_vm_32bit_registers[] = {
	SOFT_VM_32BIT_REGISTER_TABLE
};

static char * soft_vm_16bit_registers[] = {
	SOFT_VM_16BIT_REGISTER_TABLE
};

static char * soft_vm_8bit_registers[] = {
	SOFT_VM_8BIT_REGISTER_TABLE
};
#undef X

#endif // _SOFT_VM_REGISTERS_H
