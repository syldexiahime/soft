#define NUM_REGS 4

typedef enum {
	hlt,
	nop,
	ldi,
	add,
	sub
} INSTRUCTION_SET;

typedef struct {
	short running;
	int pc;
	int r[NUM_REGS];
} VM;

typedef struct {
	int instr, r1, r2, r3, imm;
} Command;
