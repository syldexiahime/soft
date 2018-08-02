#include <stdlib.h>
#include <stdint.h>

#include "utils/charstream.h"

void soft_charstream_init(soft_charstream *stream, char *buffer)
{
	stream->buffer = buffer;
	stream->index  = 0;
	stream->line   = 0;
	stream->column = 0;
}

char soft_charstream_peek(soft_charstream *stream)
{
	return stream->buffer[stream->index];
}

char soft_charstream_consume(soft_charstream *stream)
{
	return stream->buffer[stream->index++];
}

void soft_charstream_skip(soft_charstream *stream)
{
	stream->index++;
}

bool soft_charstream_eof(soft_charstream *stream)
{
	return stream->buffer[stream->index] == '\0';
}

bool soft_charstream_expect(soft_charstream *stream, bool (*eval_function)(char))
{
	return eval_function(soft_charstream_peek(stream));
}

char* soft_charstream_read_while(soft_charstream * charstream, bool (*eval_function)(char))
{
	uint16_t size = 16;
	char * buffer = malloc(size);
	uint16_t index = 0;

	while (soft_charstream_expect(charstream, eval_function) && index <= size) {
		if (index == size) {
			size += 16;
			buffer = (char *) realloc(buffer, size);
		}
		buffer[index] = soft_charstream_consume(charstream);
		index++;
	}
	buffer[index] = '\0';

	return buffer;
}
