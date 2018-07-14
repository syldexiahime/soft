#include <stdio.h>
#include <stdint.h>

#include "soft.h"

#ifndef SOFT_VM_H
#define SOFT_VM_H

#define SOFT_VM_GET_INSTR_VALUE(vm, instr) (instr.src == noop ? instr.imm : vm->r[instr.src])

#define SOFT_VM_EXECUTE_INSTR(vm, instr, operation) \
switch(instr.datatype) { \
	case soft_int32_t: SOFT_VM_##operation(vm, instr, soft_int32); break; \
	case soft_float_t: SOFT_VM_##operation(vm, instr, soft_float); break; \
}

#define SOFT_VM_LOAD(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t = instr.imm.soft_type_t

#define SOFT_VM_ADD(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t += SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t
#define SOFT_VM_SUB(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t -= SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t
#define SOFT_VM_MUL(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t *= SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t
#define SOFT_VM_DIV(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t /= SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t

#define SOFT_VM_NUM_REGS 8

typedef enum {
	noop = 0x0F,
	halt = 0x00,

	soft_load = 0x10,

	soft_add = 0x20,
	soft_sub,
	soft_mul,
	soft_div,
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
	boolean running;
	int pc;
	union SoftData r[SOFT_VM_NUM_REGS];
} soft_VM;

typedef struct {
	uint16_t opcode : 8;
	uint16_t datatype : 8;
	uint8_t src : 4;
	uint8_t dst : 4;
	union SoftData imm;
} soft_instr;

soft_VM create_VM();
void soft_vm_execute_instr(soft_VM *vm, soft_instr instr);
void show_registers(soft_VM *vm);
void run_vm();

#endif // SOFT_VM_H
