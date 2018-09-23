#include "assembler/keywords.h"

#define SOFT_ASM_KEYWORD_TABLE \
	X(data) X(program) \
	X(load) X(mov) \
	X(add)  X(sub)  X(mul) X(div) \
	X(eq)   X(lt)   X(gt)  X(gteq)   X(lteq) \
	X(and)  X(or)   X(xor) X(lshift) X(rshift) X(not) \
	X(jmp)  X(jmpz) X(jmpnz) \
	X(cast)

#define SOFT_ASM_REGISTER_TABLE \
	X(rax) X(rbx) X(rcx) X(rdx) \
	X(rdi) X(rsi) X(rsp) X(rbp)

#define X(y) soft_asm_##y,
enum SOFT_ASM_KEYWORDS {
	SOFT_ASM_KEYWORD_TABLE
};

enum SOFT_ASM_REGISTERS {
	SOFT_ASM_REGISTER_TABLE
};
#undef X

#define X(y) #y,
char * soft_asm_symbols[] = {
	",", ".", "-", "$", "[", "]", ";"
};
size_t num_soft_asm_symbols = sizeof(soft_asm_symbols) / sizeof(char *);

char * soft_asm_keywords[] = {
	SOFT_ASM_KEYWORD_TABLE
};
size_t num_soft_asm_keywords = sizeof(soft_asm_keywords) / sizeof(char *);

char * soft_asm_registers[] = {
	SOFT_ASM_REGISTER_TABLE
};
size_t num_soft_asm_registers = sizeof(soft_asm_registers) / sizeof(char *);
#undef X
