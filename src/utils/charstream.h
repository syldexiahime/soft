#ifndef _SOFT_CHARSTREAM_H
#define _SOFT_CHARSTREAM_H

#include <stdbool.h>

typedef struct {
	int    index;
	int    line;
	int    column;
	char * buffer;
} soft_charstream;

soft_charstream * soft_charstream_init(char * buffer);
char soft_charstream_peek();
char soft_charstream_consume();
void soft_charstream_skip();
bool soft_charstream_eof();
bool soft_charstream_expect(bool (*eval_function)(char));
char * soft_charstream_read_while(bool (*eval_function)(char));
char * soft_charstream_read_whilei(bool (*eval_function)(char, int));
char * soft_charstream_warn(char * filename, char * message);

#endif // _SOFT_CHARSTREAM_H
