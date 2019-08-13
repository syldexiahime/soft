#include "assembler/keywords.h"

#define SOFT_ASM_KEYWORD_TABLE \
	X(data) X(text) X(bss) X(section)

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
