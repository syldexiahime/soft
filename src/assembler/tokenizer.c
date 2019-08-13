#include "assembler/tokenizer.h"

#include "assembler/assembler.h"
#include "vm/registers.h"
#include "assembler/keywords.h"
#include "utils/charstream.h"
#include "utils/helpers.h"

#include <stdlib.h>
#include <string.h>

struct soft_asm_tokenizer * tokenizer = NULL;

bool is_soft_asm_word (char c, size_t i) {
	return c == '$' || c == '_' || (i == 0 ? isalpha(c) : isalnum(c));
}

bool is_soft_asm_symbol (char c, size_t i) {
	for (size_t s = 0; s < num_soft_asm_symbols; s++) {
		if (strlen(soft_asm_symbols[s]) > i && c == soft_asm_symbols[s][i])
			return true;
	}

	return false;
}

bool is_soft_asm_keyword (char * word)
{
	size_t len = strlen(word);
	char * lword = alloca(len);

	for (size_t i = len + 1; i--;)
		lword[i] = tolower(word[i]);

	for (size_t i = 0; i < num_soft_asm_keywords; i++) {
		if (strcmp(lword, soft_asm_keywords[i]) == 0)
			return true;
	}

	return false;
}

bool is_soft_asm_instruction (char * word)
{
	size_t len = strlen(word);
	char * lword = alloca(len);

	for (size_t i = len + 1; i--;)
		lword[i] = tolower(word[i]);

	for (size_t i = 0; i < num_soft_instrs; i++) {
		if (strcmp(lword, soft_asm_instructions[i]) == 0)
			return true;
	}

	return false;
}

bool is_soft_asm_register (char * word)
{
	size_t len = strlen(word);
	char * lword = alloca(len);

	for (size_t i = len + 1; i--;)
		lword[i] = tolower(word[i]);

	for (size_t i = 0; i < num_soft_vm_registers; i++) {
		if (strcmp(lword, soft_vm_registers[i]) == 0)
			return true;
	}

	return false;
}

struct soft_asm_tokenizer * soft_asm_tokenizer_init (char * buffer)
{
	if (!tokenizer)
		tokenizer = malloc(sizeof(struct soft_asm_tokenizer));

	soft_charstream_init(buffer);

	struct soft_asm_tokens * t = malloc(sizeof(struct soft_asm_tokens));
	t->length = 0;
	t->size   = 128;
	t->tokens_array = malloc(t->size * sizeof(struct soft_asm_token *));
	tokenizer->tokens = t;

	struct soft_compiler_warnings * w = malloc(sizeof(struct soft_compiler_warnings));
	w->length = 0;
	w->size   = 8;
	w->warnings_array = malloc(w->size * sizeof(char *));
	tokenizer->warnings = w;

	tokenizer->index = 0;

	return tokenizer;
}

void soft_asm_tokenizer_add_token (struct soft_asm_token * tok)
{
	struct soft_asm_tokens * t = tokenizer->tokens;

	if (t->length >= t->size)
		t->tokens_array = (struct soft_asm_token **) realloc(t->tokens_array, (t->size *= 2) * sizeof(struct soft_asm_token *));

	t->tokens_array[t->length++] = tok;
}

void soft_asm_tokenizer_warn (char * filename, char * message)
{
	struct soft_compiler_warnings * w = tokenizer->warnings;

	if (w->length >= w->size)
		w->warnings_array = (char **) realloc(w->warnings_array, (w->size *= 2) * sizeof(char *));

	w->warnings_array[w->length++] = soft_charstream_warn(filename, message);
}

void soft_asm_tokenizer_read_word ()
{
	char * buf;
	buf = soft_charstream_read_whilei(is_soft_asm_word);

	if (strlen(buf) == 0)
		soft_asm_tokenizer_warn("filename", "Unexpected symbol found.");

	struct soft_asm_token * tok = malloc(sizeof(struct soft_asm_token));
	tok->type = is_soft_asm_keyword(buf)     ? SOFT_ASM_KEYWORD  :
	            is_soft_asm_register(buf)    ? SOFT_ASM_REGISTER :
	            is_soft_asm_instruction(buf) ? SOFT_ASM_INSTRUCTION :
	                                           SOFT_ASM_WORD;
	tok->val  = buf;

	soft_asm_tokenizer_add_token(tok);
}

void soft_asm_tokenizer_read_number ()
{
	int i = 0;
	int size = 8;
	char * buf = malloc(size);
	char p = soft_charstream_consume();

	struct soft_asm_token * tok = malloc(sizeof(struct soft_asm_token));

	buf[i++] = p;

	if (p == '0') {
		p = soft_charstream_peek();
		if (p == 'x') {
			tok->type = SOFT_ASM_HEX;
			buf[i++] = p;
			soft_charstream_skip();

			while (ishex(soft_charstream_peek())) {
				if (i >= size)
					buf = realloc(buf, (size *= 2));

				buf[i++] = soft_charstream_consume();
			}
		}
		else if (p == 'b') {
			tok->type = SOFT_ASM_BINARY;
			buf[i++] = p;
			soft_charstream_skip();

			while (isbin(soft_charstream_peek())) {
				if (i >= size)
					buf = realloc(buf, (size *= 2));

				buf[i++] = soft_charstream_consume();
			}
		}
		else if (isoct(p)) {
			tok->type = SOFT_ASM_OCT;
			buf[i++] = p;
			soft_charstream_skip();

			while (isoct(soft_charstream_peek())) {
				if (i >= size)
					buf = realloc(buf, (size) *= 2);

				buf[i++] = soft_charstream_consume();
			}
		}
		else if (p == '8' || p == '9' || !is_soft_asm_symbol(p, 0)) {
			tok->type = SOFT_ASM_UNDEFINED;
			soft_charstream_warn("filename", "Unexpected character.");
		}
	}
	else if (isnumber(p) || p == '.') {
		tok->type = SOFT_ASM_NUMBER;

		while (isnumber(soft_charstream_peek())) {
			if (i >= size)
				buf = realloc(buf, (size *= 2));

			buf[i++] = soft_charstream_consume();
		}

		if (soft_charstream_peek() == '.') {
			tok->type = SOFT_ASM_FLOAT;
			buf[i++] = soft_charstream_consume();
		}

		while (isnumber(soft_charstream_peek())) {
			if (i >= size)
				buf = realloc(buf, (size *= 2));

			buf[i++] = soft_charstream_consume();
		}
	}

	if (i >= size)
		buf = realloc(buf, (size *= 2));

	buf[i++] = '\0';

	tok->val = buf;
	soft_asm_tokenizer_add_token(tok);
}

void soft_asm_tokenizer_read_symbol ()
{
	char * buf;
	buf = soft_charstream_read_whilei(is_soft_asm_symbol);

	if (strcmp(buf, ";") == 0)
		return soft_charstream_skip_to_next_line();

	struct soft_asm_token * tok = malloc(sizeof(struct soft_asm_token));
	tok->type = SOFT_ASM_SYMBOL;
	tok->val  = buf;

	soft_asm_tokenizer_add_token(tok);
}

void soft_asm_tokenizer_read_eol ()
{
	if (soft_charstream_peek() != '\n') {
		// TODO emit some error
	}

	soft_charstream_skip();

	struct soft_asm_token * tok = malloc(sizeof(struct soft_asm_token));
	tok->type = SOFT_ASM_EOL;
	tok->val  = NULL;

	soft_asm_tokenizer_add_token(tok);
}

void soft_asm_tokenizer_read_eof ()
{
	struct soft_asm_token * tok = malloc(sizeof(struct soft_asm_token));
	tok->type = SOFT_ASM_EOF;
	tok->val  = NULL;

	soft_asm_tokenizer_add_token(tok);
}

void soft_asm_tokenizer_read_next ()
{
	char next = soft_charstream_peek();

	while (next != '\n' && isspace(next)) {
		soft_charstream_skip_whitespace();
		next = soft_charstream_peek();
	}

	if (isnumber(next))              return soft_asm_tokenizer_read_number();
	if (is_soft_asm_word(next, 0))   return soft_asm_tokenizer_read_word();
	if (is_soft_asm_symbol(next, 0)) return soft_asm_tokenizer_read_symbol();
	if (next == '\n')                return soft_asm_tokenizer_read_eol();
	if (soft_charstream_eof())       return soft_asm_tokenizer_read_eof();
}

struct soft_asm_token * soft_asm_tokenizer_get_token (int index)
{
	struct soft_asm_tokens * t = tokenizer->tokens;

	if (index > t->size)
		return NULL;

	if (tokenizer->tokens->tokens_array[tokenizer->index] == NULL)
		soft_asm_tokenizer_read_next();

	return t->tokens_array[index];
}

bool soft_asm_tokenizer_eof ()
{
	struct soft_asm_token * tok = soft_asm_tokenizer_get_token(tokenizer->index);

	return tok->type == SOFT_ASM_EOF;
}

void soft_asm_tokenizer_skip ()
{
	tokenizer->index++;
}

struct soft_asm_token * soft_asm_tokenizer_peek ()
{
	return soft_asm_tokenizer_get_token(tokenizer->index);
}

struct soft_asm_token * soft_asm_tokenizer_consume ()
{
	return soft_asm_tokenizer_get_token(++tokenizer->index);
}

void soft_asm_tokenize ()
{
	while (!soft_charstream_eof())
		soft_asm_tokenizer_read_next();
}

