#define NUM_REGS 4

typedef enum {
	halt,
	noop,

	load_int,
	load_float,

	add_int_reg,
	sub_int_reg,
	mul_int_reg,
	div_int_reg,
	add_int_imm,
	sub_int_imm,
	mul_int_imm,
	div_int_imm,

	add_float_reg,
	sub_float_reg,
	mul_float_reg,
	div_float_reg,
	add_float_imm,
	sub_float_imm,
	mul_float_imm,
	div_float_imm
} soft_INSTRUCTION_SET;

union Data {
	int i;
	long l;
	float f;
};

typedef struct {
	short running;
	int pc;
	union Data r[NUM_REGS];
} soft_VM;

typedef struct {
	uint8_t opcode;
	uint8_t src : 4;
	uint8_t dst : 4;
	uint64_t imm;
} soft_instr;
