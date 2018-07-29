#ifndef _SOFT_VM_H
#define _SOFT_VM_H

#include <stdio.h>
#include <stdint.h>

#include "vm/opcodes.h"
#include "soft.h"

#define SOFT_VM_NUM_REGS 8

typedef enum {
	soft_ptr32 = 0x00,
	soft_int32 = 0x10,
	soft_float = 0x20,
} soft_DATATYPES;

union SoftData {
	int32_t   soft_int32;
	float     soft_float;
	void*     soft_ptr32;
};

#define soft_int32_t int32_t
#define soft_float_t float
#define soft_ptr32_t void*

typedef struct {
	uint16_t opcode : 8;
	uint16_t datatype : 8;
	uint8_t src : 4;
	uint8_t dst : 4;
	union SoftData imm;
} soft_instr;

typedef struct {
	boolean running;
	int pc;
	union SoftData r[SOFT_VM_NUM_REGS];
	boolean zf;
	soft_instr *program;
} soft_VM;

void soft_vm_init_vm(soft_VM *vm);
void soft_vm_load_program(soft_VM *vm, soft_instr *new_program);
void soft_vm_run_vm(soft_VM *vm);
void soft_vm_run_vm_debug(soft_VM *vm);

#endif // SOFT_VM_H
