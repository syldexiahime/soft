#include "assembler/assembler.h"

bool is_soft_asm_word(char c, size_t i) {
	return c == '$' || c == '_' || (i == 0 ? isalpha(c) : isalnum(c));
}

bool is_soft_asm_symbol(char c, size_t i) {
	for (size_t s = 0; s < num_soft_asm_symbols; s++) {
		if (strlen(soft_asm_symbols[s]) > i && c == soft_asm_symbols[s][i]) return true;
	}

	return false;
}

bool is_soft_asm_keyword(char * word)
{
	size_t len = strlen(word);
	char * lword = alloca(len);

	for (size_t i = len + 1; i--;) lword[i] = tolower(word[i]);

	for (size_t i = 0; i < num_soft_asm_keywords; i++) {
		if (strcmp(lword, soft_asm_keywords[i]) == 0) return true;
	}

	return false;
}

bool is_soft_asm_register(char * word)
{
	size_t len = strlen(word);
	char * lword = alloca(len);

	for (size_t i = len + 1; i--;) lword[i] = tolower(word[i]);

	for (size_t i = 0; i < num_soft_asm_registers; i++) {
		if (strcmp(lword, soft_asm_registers[i]) == 0) return true;
	}

	return false;
}
