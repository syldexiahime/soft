#include <stdlib.h>
#include <string.h>

#include "vm/vm-test.h"
#include "assembler/assembler-test.h"
#include "assembler/tokenizer.h"

struct soft_asm_tokenizer * tokenizer;

void show_tokens ()
{
	struct soft_asm_tokens * tokens = tokenizer->tokens;

	printf("\n");
	printf("tokens: %p, length: %zu", tokens, tokens->length);
	for (int i = 0; i < tokens->length; i++)
		printf("\ntoken: %d, type: %d, value: %s", i, tokens->tokens_array[i]->type, tokens->tokens_array[i]->val);
	printf("\n\n");
}

void soft_asm_tokenizer_test_read_word (void ** state)
{
	tokenizer = soft_asm_tokenizer_init("test mov rax t3st _test $test");
	soft_asm_tokenize();

	check_token(tokenizer, 0, SOFT_ASM_WORD,     "test");
	check_token(tokenizer, 1, SOFT_ASM_KEYWORD,  "mov");
	check_token(tokenizer, 2, SOFT_ASM_REGISTER, "rax");
	check_token(tokenizer, 3, SOFT_ASM_WORD,     "t3st");
	check_token(tokenizer, 4, SOFT_ASM_WORD,     "_test");
	check_token(tokenizer, 5, SOFT_ASM_WORD,     "$test");
	assert_true(tokenizer->tokens->length == 6);

	tokenizer = soft_asm_tokenizer_init("MOV RAX");
	soft_asm_tokenize();

	check_token(tokenizer, 0, SOFT_ASM_KEYWORD, "MOV");
	check_token(tokenizer, 1, SOFT_ASM_REGISTER, "RAX");

	tokenizer = soft_asm_tokenizer_init("1notaword");
	soft_asm_tokenize();

	assert_true(tokenizer->tokens->tokens_array[0]->type != SOFT_ASM_WORD);
	assert_true(tokenizer->tokens->tokens_array[0]->type != SOFT_ASM_KEYWORD);
	assert_true(tokenizer->tokens->tokens_array[0]->type != SOFT_ASM_REGISTER);
}

void soft_asm_tokenizer_test_read_number (void ** state)
{
	tokenizer = soft_asm_tokenizer_init("12345 12.45 0b10101 0x3f9a 01237");
	soft_asm_tokenize();

	assert_true(tokenizer->tokens->length == 5);
	check_token(tokenizer, 0, SOFT_ASM_NUMBER, "12345");
	check_token(tokenizer, 1, SOFT_ASM_FLOAT,  "12.45");
	check_token(tokenizer, 2, SOFT_ASM_BINARY, "0b10101");
	check_token(tokenizer, 3, SOFT_ASM_HEX,    "0x3f9a");
	check_token(tokenizer, 4, SOFT_ASM_OCT,    "01237");

	tokenizer = soft_asm_tokenizer_init("123abc");
	soft_asm_tokenize();

	assert_true(tokenizer->tokens->length == 2);
	check_token(tokenizer, 0, SOFT_ASM_NUMBER, "123");
	check_token(tokenizer, 1, SOFT_ASM_WORD,   "abc");

	tokenizer = soft_asm_tokenizer_init("0b10123");
	soft_asm_tokenize();

	assert_true(tokenizer->tokens->length == 2);
	check_token(tokenizer, 0, SOFT_ASM_BINARY, "0b101");
	check_token(tokenizer, 1, SOFT_ASM_NUMBER, "23");

	tokenizer = soft_asm_tokenizer_init("0x19afza19");
	soft_asm_tokenize();

	assert_true(tokenizer->tokens->length == 2);
	check_token(tokenizer, 0, SOFT_ASM_HEX,  "0x19af");
	check_token(tokenizer, 1, SOFT_ASM_WORD, "za19");

	tokenizer = soft_asm_tokenizer_init("0217809");
	soft_asm_tokenize();

	assert_true(tokenizer->tokens->length == 2);
	check_token(tokenizer, 0, SOFT_ASM_OCT,    "0217");
	check_token(tokenizer, 1, SOFT_ASM_NUMBER, "809");
}

void soft_asm_tokenizer_test_read_symbol (void ** state)
{
	tokenizer = soft_asm_tokenizer_init(", . - [ ]");
	soft_asm_tokenize();

	assert_true(tokenizer->tokens->length == 5);
	check_token(tokenizer, 0, SOFT_ASM_SYMBOL, ",");
	check_token(tokenizer, 1, SOFT_ASM_SYMBOL, ".");
	check_token(tokenizer, 2, SOFT_ASM_SYMBOL, "-");
	check_token(tokenizer, 3, SOFT_ASM_SYMBOL, "[");
	check_token(tokenizer, 4, SOFT_ASM_SYMBOL, "]");
}

void soft_asm_tokenizer_test_skip_comment (void ** state)
{
	tokenizer = soft_asm_tokenizer_init("foo bar");
	soft_asm_tokenize();
	assert_true(tokenizer->tokens->length == 2);

	tokenizer = soft_asm_tokenizer_init("foo ; bar");
	soft_asm_tokenize();
	assert_true(tokenizer->tokens->length == 1);

	tokenizer = soft_asm_tokenizer_init("foo ; bar\n baz");
	soft_asm_tokenize();
	assert_true(tokenizer->tokens->length == 3);
}

void soft_asm_tokenizer_test_read_section (void ** state)
{
	tokenizer = soft_asm_tokenizer_init("[Section.Data]");
	soft_asm_tokenize();

	assert_true(tokenizer->tokens->length == 5);
	check_token(tokenizer, 0, SOFT_ASM_SYMBOL, "[");
	check_token(tokenizer, 1, SOFT_ASM_KEYWORD, "Section");
	check_token(tokenizer, 2, SOFT_ASM_SYMBOL, ".");
	check_token(tokenizer, 3, SOFT_ASM_KEYWORD, "Data");
	check_token(tokenizer, 4, SOFT_ASM_SYMBOL, "]");
}

void soft_asm_tokenizer_test_thingy (void ** state)
{
	tokenizer = soft_asm_tokenizer_init("foo bar");
	soft_asm_tokenize();
	assert_true(tokenizer->tokens->length == 2);

	tokenizer = soft_asm_tokenizer_init("foo ; bar");
	soft_asm_tokenize();
	assert_true(tokenizer->tokens->length == 1);

	tokenizer = soft_asm_tokenizer_init("foo ; bar\n baz");
	soft_asm_tokenize();
	assert_true(tokenizer->tokens->length == 3);
}
