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

bool soft_charstream_eof(soft_charstream *stream)
{
	return stream->buffer[stream->index] == '\0';
}
