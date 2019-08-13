#include "utils/charstream.h"

struct soft_charstream * charstream;

inline void   soft_charstream_set_buffer (char * buffer) { charstream->buffer = buffer; }
inline char * soft_charstream_get_buffer () { return charstream->buffer; }

inline void   soft_charstream_set_pos (size_t i) { charstream->index = i; }
inline size_t soft_charstream_get_pos () { return charstream->index; }

struct soft_charstream * soft_charstream_init (char * buffer)
{
	if (!charstream)
		charstream = malloc(sizeof(struct soft_charstream));

	soft_charstream_set_buffer(buffer);
	charstream->index  = 0;
	charstream->line   = 0;
	charstream->column = 0;

	return charstream;
}

inline char soft_charstream_peek ()    { return charstream->buffer[charstream->index];     }
inline bool soft_charstream_eof ()     { return soft_charstream_peek() == '\0';            }
inline void soft_charstream_skip ()    { if (!soft_charstream_eof()) charstream->index++;  }
inline char soft_charstream_consume () { char c = soft_charstream_peek(); soft_charstream_skip(); return c; }

bool soft_charstream_expect (bool (*eval_function)(char))
{
	return eval_function(soft_charstream_peek());
}

bool soft_charstream_expect_at_pos (bool (*eval_function)(char, size_t), int index)
{
	return eval_function(soft_charstream_peek(), index);
}

char * soft_charstream_read_while (bool (*eval_function)(char))
{
	uint16_t size = 16;
	char * buffer = malloc(size);
	uint16_t index = 0;

	while (soft_charstream_expect(eval_function)) {
		if (index + 1 >= size) {
			size += 16;
			buffer = (char *) realloc(buffer, size);
		}
		buffer[index] = soft_charstream_consume();
		index++;
	}
	buffer[index] = '\0';

	return buffer;
}

char * soft_charstream_read_whilei (bool (*eval_function)(char, size_t))
{
	uint16_t size = 16;
	char * buffer = malloc(size);
	uint16_t index = 0;

	while (soft_charstream_expect_at_pos(eval_function, index)) {
		if (index + 1 >= size) {
			size += 16;
			buffer = (char *) realloc(buffer, size);
		}
		buffer[index] = soft_charstream_consume();
		index++;
	}
	buffer[index] = '\0';

	return buffer;
}

char * soft_charstream_read_quote ()
{
	uint16_t size = 16;
	char * buffer = malloc(size);
	uint16_t index = 0;

	char quote = soft_charstream_consume();
	bool escaped = false;

	char next = soft_charstream_peek();

	while (!(next == quote && escaped) && !soft_charstream_eof()) {
		if (index + 2 >= size) {
			size += 16;
			buffer = (char *) realloc(buffer, size);
		}
		buffer[index++] = next;
		next = soft_charstream_peek();
		escaped = next == '\\';
	}
	if (next != quote) soft_charstream_panic("filename", "Unable to find match quotes.");
	buffer[index++] = soft_charstream_consume();
	buffer[index]   = '\0';

	return buffer;
}

void soft_charstream_skip_whitespace ()
{
	while (!soft_charstream_eof()) {
		char p = soft_charstream_peek();

		if (!isspace(p))
			return;

		soft_charstream_skip();
	}
}

void soft_charstream_skip_inline_whitespace ()
{
	while (!soft_charstream_eof()) {
		char p = soft_charstream_peek();

		if (p == '\n' || !isspace(p))
			return;

		soft_charstream_skip();
	}
}

void soft_charstream_skip_to_next_line ()
{
	while (!soft_charstream_eof()) {
		char next = soft_charstream_peek();
		if (next == '\n') return;
		soft_charstream_skip();
	}
}

char * soft_charstream_warn (char * filename, char * message)
{
	char * warnstr = malloc(sizeof(filename) + sizeof(message) + 32);
	sprintf(warnstr, "%s:%d:%d: error: %s", filename, charstream->line, charstream->column, message);
	return warnstr;
}

void soft_charstream_panic (char * filename, char * message)
{
	printf("%s:%d:%d: error: %s", filename, charstream->line, charstream->column, message);
	exit(1);
}
