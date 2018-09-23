#include "assembler/tokenizer.h"

struct soft_asm_tokenizer * tokenizer = NULL;

struct soft_asm_tokenizer * soft_asm_tokenizer_init(char * buffer)
{
	if (!tokenizer) tokenizer = malloc(sizeof(struct soft_asm_tokenizer));

	tokenizer->tokens   = NULL;
	tokenizer->warnings = NULL;

	return tokenizer;
}

void soft_asm_tokenizer_add_token(struct soft_asm_token * tok)
{
	struct soft_asm_tokens * t = tokenizer->tokens;
	if (t->length >= t->size) {
		t->size *= 2;
		t->tokens_array = (struct soft_asm_token **) realloc(t->tokens_array, t->size * sizeof(struct soft_asm_token *));
	}
	t->tokens_array[t->length++] = tok;
}

void soft_asm_tokenizer_warn(char * filename, char * message)
{
	struct soft_compiler_warnings * w = tokenizer->warnings;
	if (w->length >= w->size) {
		w->size *= 2;
		w->warnings_array = (char **) realloc(w->warnings_array, w->size * sizeof(char *));
	}
	w->warnings_array[w->length++] = soft_charstream_warn(filename, message);
}

void soft_asm_tokenizer_read_word()
{
	char * buf;
	buf = soft_charstream_read_whilei(is_soft_asm_word);

	if (strlen(buf) == 0) soft_asm_tokenizer_warn("filename", "Unexpected symbol found.");

	struct soft_asm_token * tok = malloc(sizeof(struct soft_asm_token));
	tok->type = is_soft_asm_keyword(buf)  ? SOFT_ASM_KEYWORD  :
	            is_soft_asm_register(buf) ? SOFT_ASM_REGISTER :
	                                        SOFT_ASM_WORD;
	tok->val  = buf;

	soft_asm_tokenizer_add_token(tok);
}

void soft_asm_tokenizer_read_number()
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
				if (i >= size) { size *= 2; buf = realloc(buf, size); }
				buf[i++] = soft_charstream_consume();
			}
		}
		else if (p == 'b') {
			tok->type = SOFT_ASM_BINARY;
			buf[i++] = p;
			soft_charstream_skip();
			while (isbin(soft_charstream_peek())) {
				if (i >= size) { size *= 2; buf = realloc(buf, size); }
				buf[i++] = soft_charstream_consume();
			}
		}
		else if (isoct(p)) {
			tok->type = SOFT_ASM_OCT;
			buf[i++] = p;
			soft_charstream_skip();
			while (isoct(soft_charstream_peek())) {
				if (i >= size) { size *= 2; buf = realloc(buf, size); }
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
			if (i >= size) { size *= 2; buf = realloc(buf, size); }
			buf[i++] = soft_charstream_consume();
		}
		if (soft_charstream_peek() == '.') {
			tok->type = SOFT_ASM_FLOAT;
			buf[i++] = soft_charstream_consume();
		}
		while (isnumber(soft_charstream_peek())) {
			if (i >= size) { size *= 2; buf = realloc(buf, size); }
			buf[i++] = soft_charstream_consume();
		}
	}

	if (i >= size) { size *= 2; buf = realloc(buf, size); }
	buf[i++] = '\0';

	tok->val = buf;
	soft_asm_tokenizer_add_token(tok);
}

void soft_asm_tokenizer_read_symbol()
{
	char * buf;
	buf = soft_charstream_read_whilei(is_soft_asm_symbol);

	if (strcmp(buf, ";") == 0) return soft_charstream_skip_to_next_line();

	struct soft_asm_token * tok = malloc(sizeof(struct soft_asm_token));
	tok->type = SOFT_ASM_SYMBOL;
	tok->val  = buf;

	soft_asm_tokenizer_add_token(tok);
}

void soft_asm_tokenizer_read_eol()
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

void soft_asm_tokenizer_read_next()
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
	// if (soft_charstream_eof())       return soft_asm_tokenizer_read_eof();
}

bool soft_asm_tokenizer_eof()
{
	return soft_charstream_eof();
}

void soft_asm_tokenize(char * buffer)
{
	if (tokenizer->tokens)   free(tokenizer->tokens);
	if (tokenizer->warnings) free(tokenizer->warnings);
	if (tokenizer)           free(tokenizer);

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

	while (!soft_asm_tokenizer_eof()) {
		soft_asm_tokenizer_read_next();
	}
}
