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
	long r[NUM_REGS];
} VM;

typedef struct {
	unsigned char instr;
	int args[5];
} Command;
