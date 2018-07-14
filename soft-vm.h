#define NUM_REGS 8

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
	uint8_t running;
	int pc;
	union SoftData r[NUM_REGS];
} soft_VM;

typedef struct {
	uint16_t opcode : 8;
	uint16_t datatype : 8;
	uint8_t src : 4;
	uint8_t dst : 4;
	union SoftData imm;
} soft_instr;
