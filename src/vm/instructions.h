#ifndef _SOFT_VM_INSTRUCTIONS_H
#define _SOFT_VM_INSTRUCTIONS_H

#include "vm/datatypes.h"

#include <stdint.h>

struct soft_instr {
	uint16_t opcode : 8;
	uint16_t datatype : 8;
	uint8_t src : 4;
	uint8_t dst : 4;
	union SoftData imm;
};

/**
 * Helpers
 * */
#define _soft_vm_get_instr_value() (instr.src == noop ? instr.imm : vm->r[instr.src])

/**
 * Load instructions
 * */
#define soft_vm_load(soft_type_t) \
	vm->r[instr.dst].soft_type_t = instr.imm.soft_type_t

// If destination is empty, copy value to the address held in the immediate
#define soft_vm_mov_reg(soft_type_t) \
	if (instr.dst == noop) { \
		*((soft_type_t##_t*) instr.imm.soft_ptr) = vm->r[instr.src].soft_type_t; \
	} \
	else { \
		vm->r[instr.dst].soft_type_t = vm->r[instr.src].soft_type_t; \
	}

// If the destination is empty, copy the value from the address held in the src register to the address held in the immediate
// Otherwise copy the value from the address held in the src register to the destination register
#define soft_vm_mov_addr(soft_type_t) \
	if (instr.dst == noop) { \
		*((soft_type_t##_t*) instr.imm.soft_ptr) = *((soft_type_t##_t*) vm->r[instr.src].soft_ptr); \
	} \
	else { \
		vm->r[instr.dst].soft_type_t = *((soft_type_t##_t*) vm->r[instr.src].soft_ptr); \
	}

/**
 * Arithmetic instructions
 * */
#define soft_vm_arithmetic(soft_type_t, op) \
	vm->r[instr.dst].soft_type_t op##= _soft_vm_get_instr_value().soft_type_t

#define soft_vm_ptr_arithmetic(op) \
	vm->r[instr.dst].soft_ptr op##= _soft_vm_get_instr_value().soft_int32;

/**
 * Equality instructions
 * */
#define soft_vm_comparison(soft_type_t, op) \
	vm->zf = vm->r[instr.dst].soft_type_t op _soft_vm_get_instr_value().soft_type_t

/**
 * Binary/Bitwise instructions
 * */
#define soft_vm_binary(op) \
	vm->r[instr.dst].soft_int32 op##= _soft_vm_get_instr_value().soft_int32

#define soft_vm_not() \
	vm->r[instr.dst].soft_int32 = ~ _soft_vm_get_instr_value().soft_int32

/**
 * Typecast instructions
 * */
#define soft_vm_cast_ptr(soft_type_t) \
	vm->r[instr.dst].soft_ptr = (soft_ptr_t) vm->r[instr.src].soft_type_t

#define soft_vm_cast_int32(soft_type_t) \
	vm->r[instr.dst].soft_int32 = (soft_int32_t) vm->r[instr.src].soft_type_t

#define soft_vm_cast_float(soft_type_t) \
	vm->r[instr.dst].soft_int32 = (soft_float_t) vm->r[instr.src].soft_type_t

/**
 * Jump instructions
 * */
#define soft_vm_jmp() \
	vm->pc = _soft_vm_get_instr_value().soft_int32; return

#define soft_vm_jmpz() \
	if (vm->zf == true) { vm->pc = _soft_vm_get_instr_value().soft_int32; return; }

#define soft_vm_jmpnz() \
	if (vm->zf == false) { vm->pc = _soft_vm_get_instr_value().soft_int32; return; }

#endif // _SOFT_VM_INSTRUCTIONS_H
