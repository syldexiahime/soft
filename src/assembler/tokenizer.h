#ifndef _SOFT_TOKENIZER_H
#define _SOFT_TOKENIZER_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#include "soft.h"
#include "assembler/assembler.h"
#include "assembler/keywords.h"
#include "utils/charstream.h"
#include "utils/helpers.h"

struct soft_asm_token {
	uint8_t type;
	char *  val;
};

struct soft_asm_tokens {
	struct soft_asm_token ** tokens_array;
	size_t length;
	size_t size;
};

struct soft_asm_tokenizer {
	struct soft_asm_tokens *        tokens;
	struct soft_compiler_warnings * warnings;
};

struct soft_asm_tokenizer * soft_asm_tokenizer_init();
struct soft_asm_token soft_asm_tokenizer_peek();
struct soft_asm_token soft_asm_tokenizer_consume();
bool soft_asm_tokenizer_eof();
void soft_asm_tokenize(char * buffer);

#endif // _SOFT_TOKENIZER_H
