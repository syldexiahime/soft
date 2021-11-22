#ifndef _SOFT_VM_H
#define _SOFT_VM_H

#include "soft.h"
#include "vm/sval.h"
#include "vm/registers.h"
#include "vm/datatypes.h"
#include "vm/syscalls.h"

#include <stdbool.h>
#include <assert.h>

struct soft_program {
	size_t ds_size;
	char * datastore;
	struct soft_instr * instructions;
};

typedef uint64_t quadword_t;
typedef uint32_t doubleword_t;
typedef uint16_t word_t;
typedef uint8_t  byte_t;

union vm_register {
	void *       ptr;
	quadword_t   qw;
	doubleword_t dw;
	word_t       w;
	byte_t       b;
	sval_t       sval;
};

struct soft_vm {
	union vm_register r[SOFT_VM_NUM_REGS];
	struct soft_instr * ip;
	bool zf;
	bool sf;
	char * ds;
	struct soft_instr * instructions;
};

void soft_vm_init_vm(struct soft_vm * vm);
void soft_vm_load_program(struct soft_vm * vm, struct soft_program * program);
void soft_vm_run_vm(struct soft_vm * vm);
void soft_vm_run_vm_debug(struct soft_vm * vm);

#if __GNUC__
#ifndef SOFT_VM_USE_COMPUTED_GOTO
#define SOFT_VM_USE_COMPUTED_GOTO 1
#endif // SOFT_VM_USE_COMPUTED_GOTO
#endif // __GNUC__

#endif // SOFT_VM_H
