#ifndef _SOFT_ASSEMBLER_H
#define _SOFT_ASSEMBLER_H

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "assembler/keywords.h"
#include "utils/charstream.h"

enum soft_asm_token_types {
	SOFT_ASM_EOF,
	SOFT_ASM_SECTION,
	SOFT_ASM_WORD,
	SOFT_ASM_NUMBER,
	SOFT_ASM_FLOAT,
	SOFT_ASM_OCT,
	SOFT_ASM_HEX,
	SOFT_ASM_BINARY,
	SOFT_ASM_KEYWORD,
	SOFT_ASM_REGISTER,
	SOFT_ASM_SYMBOL,
	SOFT_ASM_UNDEFINED,
	SOFT_ASM_EOL,
};

bool is_soft_asm_word(char c, size_t i);
bool is_soft_asm_symbol(char c, size_t i);
bool is_soft_asm_keyword(char * word);
bool is_soft_asm_register(char * word);

#endif // _SOFT_ASSEMBLER_H
