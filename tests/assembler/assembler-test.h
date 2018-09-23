#ifndef _SOFT_ASSEMBLER_TEST_H
#define _SOFT_ASSEMBLER_TEST_H

#include "soft-test.h"
#include "utils/charstream.h"
#include "assembler/tokenizer.h"
#include "assembler/assembler.h"

/**
 * Helper functions and macros for running tests
 * */
#define check_token(tokenizer, index, token_type, value) \
	assert_true(tokenizer->tokens->tokens_array[index]->type == token_type); \
	assert_true(strcmp(tokenizer->tokens->tokens_array[index]->val, value) == 0);

/**
 * Non public tokenizer functions
 * */
struct soft_asm_token * soft_asm_tokenizer_read_word(struct soft_asm_tokenizer * tokenizer, struct soft_charstream * charstream);

/**
 * Tokenizer tests
 * */
void soft_asm_tokenizer_test_read_section(void ** state);
void soft_asm_tokenizer_test_read_word(void ** state);
void soft_asm_tokenizer_test_read_number(void ** state);
void soft_asm_tokenizer_test_read_symbol(void ** state);
void soft_asm_tokenizer_test_skip_comment(void **state);

#endif // _SOFT_ASSEMBLER_TEST_H
