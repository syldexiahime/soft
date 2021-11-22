#ifndef _SOFT_VM_INSTRUCTIONS_H
#define _SOFT_VM_INSTRUCTIONS_H

#include "vm/datatypes.h"

#include <stdint.h>

struct soft_instr {
	uint32_t opcode : 8;
	uint32_t src    : 4;
	uint32_t dst    : 4;
	uint32_t imm    : 16;
};

#define SOFT_INSTRUCTION_SET \
	/** \
	 * Misc. instructions \
	 * */ \
	X(noop) \
	X(halt) \
	X(breakpoint) \
	X(int) \
 \
	/** \
	 * Data instruction thingies \
	 * */ \
	X(mov) \
	X(movi) \
	X(load) \
	X(load_w) \
	X(load_dw) \
	X(load_qw) \
	X(loadi) \
	X(loadi_w) \
	X(loadi_dw) \
	X(loadi_qw) \
	X(store) \
	X(store_w) \
	X(store_dw) \
	X(store_qw) \
	X(storep) \
	X(storep_w) \
	X(storep_dw) \
	X(storep_qw) \
	X(storemem) \
	X(storemem_w) \
	X(storemem_dw) \
	X(storemem_qw) \
	X(memset) \
	X(memset_w) \
	X(memset_dw) \
	X(memset_qw) \
	X(memsetp) \
	X(memsetp_w) \
	X(memsetp_dw) \
	X(memsetp_qw) \
	X(push) \
	X(push_w) \
	X(push_dw) \
	X(push_qw) \
	X(pop) \
	X(pop_w) \
	X(pop_dw) \
	X(pop_qw) \
\
	/** \
	 * Arithmetic instructions \
	 * */ \
	X(dadd) \
	X(dsub) \
	X(dmul) \
	X(ddiv) \
	X(daddi) \
	X(dsubi) \
	X(dmuli) \
	X(ddivi) \
\
	X(dcmp) \
\
	/** \
	 * Bitwise instructions \
	 * */ \
	X(dand) \
	X(dor) \
	X(dnot) \
	X(dxor) \
	X(dlshift) \
	X(drshift) \
\
	/** \
	 * Jump instructions \
	 * */ \
	X(jmp) \
	X(jmpz) \
	X(jmpnz) \
	X(jmpgt) \
	X(jmpgte) \
	X(jmplt) \
	X(jmplte) \
\
	/** \
	 * Cast instructions \
	 * */ \
	X(castint32) \
	X(castfloat)


#define X(opname) soft_instr_##opname,
enum soft_instruction_set {
	SOFT_INSTRUCTION_SET
	num_soft_instrs,
};
#undef X

#define soft_instr_loadi_ptr    soft_instr_loadi_qw
#define soft_instr_load_ptr     soft_instr_load_qw
#define soft_instr_store_ptr    soft_instr_store_qw
#define soft_instr_storep_ptr   soft_instr_storep_qw
#define soft_instr_storemem_ptr soft_instr_storemem_qw
#define soft_instr_memset_ptr   soft_instr_memset_qw
#define soft_instr_memsetp_ptr  soft_instr_memsetp_qw

#endif // _SOFT_VM_INSTRUCTIONS_H
