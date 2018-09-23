#ifndef _SOFT_VM_H
#define _SOFT_VM_H

#include "soft.h"
#include "vm/opcodes.h"
#include "vm/instructions.h"
#include "vm/datatypes.h"

#include "vm/syscalls.h"

#include <stdbool.h>
#include <assert.h>

#define SOFT_VM_NUM_REGS 8

struct soft_vm {
	bool running;
	int pc;
	union SoftData r[SOFT_VM_NUM_REGS];
	bool zf;
	struct soft_instr * program;
};

void soft_vm_init_vm(struct soft_vm * vm);
void soft_vm_load_program(struct soft_vm * vm, struct soft_instr * program);
void soft_vm_run_vm(struct soft_vm * vm);
void soft_vm_run_vm_debug(struct soft_vm * vm);

#endif // SOFT_VM_H
