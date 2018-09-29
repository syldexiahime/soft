#ifndef _SOFT_VM_OPCODES_H
#define _SOFT_VM_OPCODES_H

enum soft_instruction_set {
	/**
	 * Misc. instructions
	 * */
	halt,
	noop,
	soft_instr_syscall,

	/**
	 * Data instruction thingies
	 * */
	soft_instr_load,
	soft_instr_movreg,
	soft_instr_movaddr,

	/**
	 * Arithmetic instructions
	 * */
	soft_instr_add,
	soft_instr_sub,
	soft_instr_mul,
	soft_instr_div,

	/**
	 * Logical instructions
	 * */
	soft_instr_eq,
	soft_instr_gt,
	soft_instr_lt,
	soft_instr_gteq,
	soft_instr_lteq,

	/**
	 * Bitwise instructions
	 * */
	soft_instr_and,
	soft_instr_or,
	soft_instr_not,
	soft_instr_xor,
	soft_instr_lshift,
	soft_instr_rshift,

	/**
	 * Jump instructions
	 * */
	soft_instr_jmp,
	soft_instr_jmpz,
	soft_instr_jmpnz,

	/**
	 * Cast instructions
	 * */
	soft_instr_castint32,
	soft_instr_castfloat,

	num_soft_instrs
};

#endif // _SOFT_VM_OPCODES_H
