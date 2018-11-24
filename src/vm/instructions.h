#ifndef _SOFT_VM_INSTRUCTIONS_H
#define _SOFT_VM_INSTRUCTIONS_H

#include "vm/datatypes.h"

#include <stdint.h>

struct soft_instr {
	uint32_t opcode : 7;
	uint32_t iflag : 1;
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
	X(syscall), \
 \
	/** \
	 * Data instruction thingies \
	 * */ \
	X(dloadi), \
	X(dload), \
	X(dstore), \
	X(dmovi), \
	X(dmov), \
	X(dpush), \
	X(dpop), \
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
	X(and), \
	X(or), \
	X(not), \
	X(xor), \
	X(lshift), \
	X(rshift), \
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
