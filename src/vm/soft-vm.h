#include <stdio.h>
#include <stdint.h>

#include "soft.h"

#ifndef SOFT_VM_H
#define SOFT_VM_H

#define SOFT_VM_NUM_REGS 8

#define _SOFT_VM_GET_INSTR_VALUE(vm, instr) (instr.src == noop ? instr.imm : vm->r[instr.src])

#define _SOFT_VM_LOAD(vm, instr, soft_type_t, _) vm->r[instr.dst].soft_type_t = instr.imm.soft_type_t
#define _SOFT_VM_ARITHMETIC(vm, instr, soft_type_t, op) vm->r[instr.dst].soft_type_t op##= _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t
#define _SOFT_VM_COMPARISON(vm, instr, soft_type_t, op) vm->zf = vm->r[instr.dst].soft_type_t op _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t

#define SOFT_VM_EXECUTE_INSTR(vm, instr, operation, op) \
switch(instr.datatype) { \
	case soft_int32_t: _SOFT_VM_##operation(vm, instr, soft_int32, op); break; \
	case soft_float_t: _SOFT_VM_##operation(vm, instr, soft_float, op); break; \
}

typedef enum {
	noop = 0x0F,
	halt = 0x00,

	soft_instr_load = 0x10,

	soft_instr_add = 0x20,
	soft_instr_sub,
	soft_instr_mul,
	soft_instr_div,

	soft_instr_eq = 0x30,
	soft_instr_gt,
	soft_instr_lt,
	soft_instr_gteq,
	soft_instr_lteq,
} soft_INSTRUCTION_SET;

typedef enum {
	soft_int32_t  = 0x10,
	soft_float_t = 0x20,
} soft_DATATYPES;

union SoftData {
	int32_t soft_int32;
	float   soft_float;
};

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
void soft_vm_execute_instr(soft_VM *vm, soft_instr instr);
void soft_vm_show_registers(soft_VM *vm);
void soft_vm_run_vm(soft_VM *vm);
void soft_vm_run_vm_debug(soft_VM *vm);

#endif // SOFT_VM_H
