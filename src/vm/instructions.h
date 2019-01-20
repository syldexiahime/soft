#ifndef _SOFT_VM_INSTRUCTIONS_H
#define _SOFT_VM_INSTRUCTIONS_H

#include "vm/datatypes.h"

#include <stdint.h>

struct soft_instr {
	uint32_t opcode : 8;
	uint32_t src : 4;
	uint32_t dst : 4;
	uint32_t imm : 16;
};


#define SOFT_INSTRUCTION_SET \
	/** \
	 * Misc. instructions \
	 * */ \
	X(halt), \
	X(breakpoint), \
	X(noop), \
	X(int), \
 \
	/** \
	 * Data instruction thingies \
	 * */ \
	X(loadi), \
	X(load_dw), \
	X(load_w), \
	X(store_dw), \
	X(store_w), \
	X(mov), \
	X(movi), \
	X(push_dw), \
	X(pop_dw), \
	X(push_w), \
	X(pop_w), \
\
	/** \
	 * Arithmetic instructions \
	 * */ \
	X(dadd), \
	X(dsub), \
	X(dmul), \
	X(ddiv), \
	X(daddi), \
	X(dsubi), \
	X(dmuli), \
	X(ddivi), \
\
	X(dcmp), \
\
	/** \
	 * Bitwise instructions \
	 * */ \
	X(dand), \
	X(dor), \
	X(dnot), \
	X(dxor), \
	X(dlshift), \
	X(drshift), \
\
	/** \
	 * Jump instructions \
	 * */ \
	X(jmp), \
	X(jmpz), \
	X(jmpnz), \
\
	/** \
	 * Cast instructions \
	 * */ \
	X(castint32), \
	X(castfloat)


#define X(opname) soft_instr_##opname
enum soft_instruction_set {
	SOFT_INSTRUCTION_SET,
	num_soft_instrs,
};
#undef X

#endif // _SOFT_VM_INSTRUCTIONS_H
