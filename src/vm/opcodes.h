#ifndef _SOFT_VM_OPCODES_H
#define _SOFT_VM_OPCODES_H

typedef enum {
	halt = 0x00,
	noop = 0x0E,
	soft_instr_syscall = 0x0F,

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

	soft_instr_and = 0x40,
	soft_instr_or,
	soft_instr_not,
	soft_instr_xor,
	soft_instr_lshift,
	soft_instr_rshift,

	soft_instr_jmp = 0x50,
	soft_instr_jmpz,
	soft_instr_jmpnz,

	soft_instr_castint32 = 0x60,
	soft_instr_castfloat
} soft_INSTRUCTION_SET;

#endif // _SOFT_VM_OPCODES_H
