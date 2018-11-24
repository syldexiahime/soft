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
	sval_t * datastore;
	struct soft_instr * instructions;
};

struct soft_vm {
	union sval r[SOFT_VM_NUM_REGS];
	struct soft_instr * ip;
	bool zf;
	bool sf;
	sval_t * ds;
	struct soft_instr * instructions;
};

void soft_vm_init_vm(struct soft_vm * vm);
void soft_vm_load_program(struct soft_vm * vm, struct soft_program * program);
void soft_vm_run_vm(struct soft_vm * vm);
void soft_vm_run_vm_debug(struct soft_vm * vm);

#ifdef __GNUC__
#define SOFT_VM_USE_COMPUTED_GOTO
#endif

#endif // SOFT_VM_H
