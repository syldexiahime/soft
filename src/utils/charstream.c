#include "utils/charstream.h"

soft_charstream * charstream;

soft_charstream * soft_charstream_init(char * buffer)
{
	if (!charstream) charstream = malloc(sizeof(soft_charstream));

	charstream->buffer = buffer;
	charstream->index  = 0;
	charstream->line   = 0;
	charstream->column = 0;

	return charstream;
}

void soft_charstream_skip()    {        charstream->index++;                           }
char soft_charstream_peek()    { return charstream->buffer[charstream->index];         }
char soft_charstream_consume() { return charstream->buffer[charstream->index++];       }
bool soft_charstream_eof()     { return charstream->buffer[charstream->index] == '\0'; }

bool soft_charstream_expect(bool (*eval_function)(char))
{
	return eval_function(soft_charstream_peek());
}

bool soft_charstream_expect_at_pos(bool (*eval_function)(char, int), int index)
{
	return eval_function(soft_charstream_peek(), index);
}

char * soft_charstream_read_while(bool (*eval_function)(char))
{
	uint16_t size = 16;
	char * buffer = malloc(size);
	uint16_t index = 0;

	while (soft_charstream_expect(eval_function) && index <= size) {
		if (index == size) {
			size += 16;
			buffer = (char *) realloc(buffer, size);
		}
		buffer[index] = soft_charstream_consume();
		index++;
	}
	buffer[index] = '\0';

	return buffer;
}

char * soft_charstream_read_whilei(bool (*eval_function)(char, int))
{
	uint16_t size = 16;
	char * buffer = malloc(size);
	uint16_t index = 0;

	while (soft_charstream_expect_at_pos(eval_function, index) && index <= size) {
		if (index == size) {
			size += 16;
			buffer = (char *) realloc(buffer, size);
		}
		buffer[index] = soft_charstream_consume();
		index++;
	}
	buffer[index] = '\0';

	return buffer;
}

char * soft_charstream_warn(char * filename, char * message)
{
	char * warnstr = malloc(sizeof(filename) + sizeof(message) + 32);

	sprintf(warnstr, "%s:%d:%d: error: %s", filename, charstream->line, charstream->column, message);

	return warnstr;
}
