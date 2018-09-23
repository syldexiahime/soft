#ifndef _SOFT_CHARSTREAM_H
#define _SOFT_CHARSTREAM_H

#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


struct soft_charstream {
	int     index;
	int     line;
	int     column;
	char *  buffer;
};

void   soft_charstream_set_buffer(char * buffer);
char * soft_charstream_get_buffer();
void   soft_charstream_set_pos(size_t i);
size_t soft_charstream_get_pos();

struct soft_charstream * soft_charstream_init(char * buffer);

char soft_charstream_peek();
char soft_charstream_consume();
void soft_charstream_skip();
bool soft_charstream_eof();

bool   soft_charstream_expect(bool (*eval_function)(char));
char * soft_charstream_read_while(bool (*eval_function)(char));
char * soft_charstream_read_whilei(bool (*eval_function)(char, size_t));

char * soft_charstream_read_quote();
void   soft_charstream_skip_whitespace();
void   soft_charstream_skip_to_next_line();

char * soft_charstream_warn(char * filename, char * message);
void   soft_charstream_panic(char * filename, char * message);

#define soft_charstream_skip_inline_whitespace(next) \
do { \
	next = soft_charstream_peek(); \
	while (next != '\n' &&isspace(next) && !soft_charstream_eof()) { soft_charstream_skip(); next = soft_charstream_peek(); }; \
} while (0)

#endif // _SOFT_CHARSTREAM_H
