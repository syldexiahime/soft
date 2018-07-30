#ifndef _SOFT_VM_H
#define _SOFT_VM_H

#include <stdbool.h>

#include "soft.h"
#include "vm/opcodes.h"
#include "vm/instructions.h"
#include "vm/datatypes.h"

#define SOFT_VM_NUM_REGS 8

typedef struct {
	bool running;
	int pc;
	union SoftData r[SOFT_VM_NUM_REGS];
	bool zf;
	soft_instr *program;
} soft_VM;

void soft_vm_init_vm(soft_VM *vm);
void soft_vm_load_program(soft_VM *vm, soft_instr *new_program);
void soft_vm_run_vm(soft_VM *vm);
void soft_vm_run_vm_debug(soft_VM *vm);

#endif // SOFT_VM_H
