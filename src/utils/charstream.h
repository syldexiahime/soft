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
bool soft_charstream_eof(soft_charstream *stream);

#endif // _SOFT_CHARSTREAM_H
