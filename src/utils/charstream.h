#ifndef _SOFT_CHARSTREAM_H
#define _SOFT_CHARSTREAM_H

#include <stdbool.h>

typedef struct {
	char* buffer;
	int index;
	int line;
	int column;
} soft_charstream;

void soft_charstream_init(soft_charstream *stream, char *buffer);
char soft_charstream_peek(soft_charstream *stream);
char soft_charstream_consume(soft_charstream *stream);
void soft_charstream_skip(soft_charstream *stream);
bool soft_charstream_eof(soft_charstream *stream);
bool soft_charstream_expect(soft_charstream *stream, bool (*eval_function)(char));
char* soft_charstream_read_while(soft_charstream * charstream, bool (*eval_function)(char));

#endif // _SOFT_CHARSTREAM_H
