#include "assembler/keywords.h"

#define SOFT_ASM_KEYWORD_TABLE \
	X(data) X(program) \
	X(load) X(mov) \
	X(add)  X(sub)  X(mul) X(div) \
	X(eq)   X(lt)   X(gt)  X(gteq)   X(lteq) \
	X(and)  X(or)   X(xor) X(lshift) X(rshift) X(not) \
	X(jmp)  X(jmpz) X(jmpnz) \
	X(cast)

#define X(y) soft_asm_##y,
enum SOFT_ASM_KEYWORDS {
	SOFT_ASM_KEYWORD_TABLE
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
#undef X
