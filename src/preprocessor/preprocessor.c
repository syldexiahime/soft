#include "preprocessor/preprocessor.h"

void soft_preprocessor_read_directive (char * nbuf);
void soft_preprocessor_replace_macro (struct soft_macro * macro);

bool is_soft_preprocessor_word (char c, size_t i) { return i == 0 ? isalpha(c) : isalnum(c) || c == '_' || c == '$'; }

struct soft_preprocessor * preprocessor;

struct soft_preprocessor * soft_preprocessor_init ()
{
	if (!preprocessor) preprocessor = calloc(1, sizeof(struct soft_preprocessor));
	if (preprocessor->warnings) free(preprocessor->warnings);
	if (preprocessor->macros)   free(preprocessor->macros);

	struct soft_compiler_warnings * w = malloc(sizeof(struct soft_compiler_warnings));
	w->length = 0; w->size = 8;
	w->warnings_array = malloc(w->size * sizeof(char *));
	preprocessor->warnings = w;

	struct soft_macros * m = malloc(sizeof(struct soft_macros));
	m->length = 0; m->size = 0;
	m->macro_array = malloc(sizeof(struct soft_macro **));
	preprocessor->macros = m;

	return preprocessor;
}

void soft_preprocessor_warn (char * filename, char * message)
{
	struct soft_compiler_warnings * w = preprocessor->warnings;
	if (w->length >= w->size) {
		w->size *= 2;
		w->warnings_array = (char **) realloc(w->warnings_array, w->size * sizeof(char *));
	}
	w->warnings_array[w->length++] = soft_charstream_warn(filename, message);
}

struct soft_macro_args * soft_preprocessor_parse_macro_args ()
{
	struct soft_macro_args * args = malloc(sizeof(struct soft_macro_args));
	args->length = 0; args->size = 8;
	args->argument_array = malloc(args->size * sizeof(char *));

	soft_charstream_skip_inline_whitespace();

	char next = soft_charstream_peek();
	while (is_soft_preprocessor_word(next, 0) && next != '\n' && !soft_charstream_eof()) {
		if (args->length >= args->size)
			args->argument_array = realloc(args->argument_array, (args->size += 8));

		args->argument_array[args->length++] = soft_charstream_read_whilei(is_soft_preprocessor_word);
		soft_charstream_skip_inline_whitespace();

		next = soft_charstream_peek();
	}

	return args;
}

char * soft_preprocessor_build_macro (char * macro, struct soft_macro_args * arguments)
{
	size_t argslen = 0;

	for (size_t i = 0; i < arguments->length; i++) {
		argslen += strlen(arguments->argument_array[i]);
	}

	size_t macrolen = strlen(macro);
	size_t buflen   = macrolen + argslen;
	char * buf      = malloc(buflen * sizeof(char));
	strcpy(buf, macro);

	char next;
	size_t arg_pos;
	char * arg_no = malloc(3 * sizeof(char));
	bool parsing_replacement = false;

	for (size_t i = 0; i < buflen; i++) {
		next = buf[i];

		if (parsing_replacement) {
			if (isdigit(next)) {
				if (i - arg_pos == 3) {
					arg_no[i - arg_pos] = '\0';
				}
				else if (i - arg_pos < 3) {
					arg_no[i - arg_pos] = next;
				}
				else {
					// TODO emit some error
					continue;
				}
			}
			else {
				parsing_replacement = false;
				char * argstr = arguments->argument_array[parse_int(arg_no) - 1];
				str_replace_at(buf, argstr, arg_pos - 1, strlen(arg_no) + 1);
			}
		}
		if (next == '%') {
			parsing_replacement = true;
			arg_pos = i + 1;
		}
	}

	free(arg_no);

	return buf;
}

struct soft_macro * soft_preprocessor_get_macro (char * word)
{
	struct soft_macro ** macros = preprocessor->macros->macro_array;
	for (size_t i = 0; i < preprocessor->macros->length; i++) {
		if (!macros[i]) continue;
		if (strcmp(word, macros[i]->name) == 0) return macros[i];
	}

	return NULL;
}

void soft_preprocessor_define_macro (char * nbuf)
{
	size_t i    = 0;
	size_t pos  = 0;
	size_t len  = 0;
	size_t size = 32;
	char * buf  = malloc(size);
	char * str  = NULL;
	char * name = NULL;

	buf[0] = '\0';

	struct soft_macro * macro = NULL;

	soft_charstream_skip_inline_whitespace();
	name = soft_charstream_read_whilei(is_soft_preprocessor_word);

	goto go_next;

	concat_buf: ;
	len = strlen(str);
	i = i + len;
	if (i + 1 >= size)
		buf = realloc(buf, (size += (i * 1.5) + 1));
	strcat(buf, str);
	free(str);

	go_next: ;
	char next = soft_charstream_peek();
	while (!soft_charstream_eof()) {

		if (i + 1 >= size)
			buf = realloc(buf, (size *= 2));

		if (next == '\'' || next == '"') {
			str = soft_charstream_read_quote();

			goto concat_buf;
		}
		else if (is_soft_preprocessor_word(next, 0)) {
			str   = soft_charstream_read_whilei(is_soft_preprocessor_word);

			macro = soft_preprocessor_get_macro(str);
			if (macro != NULL) {
				soft_preprocessor_replace_macro(macro);
				macro = NULL;

				free(str);
			}
			else {
				goto concat_buf;
			}
		}
		else if (next == '%') {
			soft_charstream_skip();
			next = soft_charstream_peek();
			if (is_soft_preprocessor_word(next, 0)) {
				str = soft_charstream_read_whilei((bool (*)(char)) is_soft_preprocessor_word);

				if (strcmp(str, "endmacro") == 0) {
					free(str);

					goto end;
				}

				// Kinda hacky but only way I could think of getting it to work
				soft_charstream_set_pos(soft_charstream_get_pos() - strlen(str));

				free(str);
				soft_preprocessor_read_directive(nbuf);
			}
			else if (isdigit(next)) {
				str = soft_charstream_read_while((bool (*)(char)) isdigit);

				goto concat_buf;
			}
			else {
				// TODO throw some sort of error
			}
		}
		else {
			buf[i++] = next;
			soft_charstream_skip();
		}

		next = soft_charstream_peek();
	}

	end: ;

	if (soft_charstream_eof())
		soft_preprocessor_warn("filename", "missing endmacro");

	if (soft_preprocessor_get_macro(name)) {
		soft_preprocessor_warn("filename", "macro already exists");
		return;
	}

	if (strlen(name) == 0) {
		soft_preprocessor_warn("filename", "invalid macro name");
		return;
	}

	macro = calloc(1, sizeof(struct soft_macro));
	macro->name = name;
	macro->body = buf;

	struct soft_macros * macros = preprocessor->macros;

	for (size_t i = 0; i < macros->length; i++) {
		if (!macros->macro_array[i]) {
			macros->macro_array[i] = macro;

			return;
		}
	}

	if (macros->length++ >= macros->size)
		macros->macro_array = realloc(macros->macro_array, (macros->size *= 2));

	macros->macro_array[macros->length - 1] = macro;
}

void soft_preprocessor_replace_macro (struct soft_macro * macro)
{
	char * buffer = soft_charstream_get_buffer();
	size_t buffer_size = strlen(buffer);
	size_t macro_start_pos = soft_charstream_get_pos();

	struct soft_macro_args * arguments = soft_preprocessor_parse_macro_args();
	char * nmacro = soft_preprocessor_build_macro(macro->body, arguments);

	size_t macro_size = strlen(nmacro);
	size_t nbufsize   = buffer_size + macro_size;

	buffer = realloc(buffer, nbufsize);

	buffer = str_replace_at(buffer, nmacro, soft_charstream_get_pos(), macro_size);

	soft_charstream_set_buffer(buffer);
}

void soft_preprocessor_parse_macro (char * nbuf)
{
	char next;

	soft_charstream_skip_whitespace();

	char * name = soft_charstream_read_whilei(is_soft_preprocessor_word);
	next = soft_charstream_peek();
	while (next != '\n' && isspace(next)) { soft_charstream_skip(); next = soft_charstream_peek(); }
	char * num_args = soft_charstream_read_while((bool (*)(char)) isdigit);
	while (next != '\n' && isspace(next)) { soft_charstream_skip(); next = soft_charstream_peek(); }

	// if (soft_charstream_consume() != '\n'); // TODO PANIC

	size_t i = 0;
	size_t pos = 0;
	size_t len = 0;
	size_t size = 256;
	char * buf = malloc(size);
	char * word = NULL;
	char * str = NULL;
	struct soft_macro * macro = NULL;

	next = soft_charstream_peek();

	while (!soft_charstream_eof()) {

		while (next != '%' && !soft_charstream_eof()) {
			if (i + 1 >= size) buf = realloc(buf, (size *= 2));
			buf[i++] = next;

			next = soft_charstream_peek();
			if (next == '\'' || next == '"') {
				str = soft_charstream_read_quote();
				len = strlen(str);
				if (i + len + 1 >= size) buf = realloc(buf, (size += (i += len * 1.5) + 1));
				strcat(buf, str);
				free(str);
			}

			if (isalpha(next)) {
				word      = soft_charstream_read_whilei(is_soft_preprocessor_word);
				macro = soft_preprocessor_get_macro(word);
				if (macro != NULL) {
					soft_preprocessor_replace_macro(macro);
					macro = NULL;
				}
				else {
					strcat(buf, word);
				}
			}
		}

		if (next == '%') {
			soft_charstream_skip();
			next = soft_charstream_peek();
			if (isalpha(next)) {
				char * str = soft_charstream_read_while((bool (*)(char)) isalpha);
				if (strcmp(str, "endmacro") == 0) break;
			}
			if (isdigit(next)) {
				char * param = soft_charstream_read_while((bool (*)(char)) isdigit);
			}
		}

	}

}

void soft_preprocessor_read_directive (char * nbuf)
{
	soft_charstream_skip();

	char * type = soft_charstream_read_while((bool (*)(char)) isalpha);

	if (strcmp(type, "macro") == 0)
		return soft_preprocessor_define_macro(nbuf);

	soft_preprocessor_warn("filename", "Unkown preprocessor directive");
}

char * soft_preprocessor_preprocess (char * buffer)
{
	int i = 0;
	int size = 256;
	char * buf = malloc(size);
	soft_charstream_init(buffer);

	buf[0] = '\0';

	bool in_quote = false;

	while (!soft_charstream_eof()) {
		char p = soft_charstream_peek();

		if (p == '\\') {
			buf[i++] = soft_charstream_consume();
			continue;
		}

		if (p == '\'' || p == '"') in_quote = !in_quote;
		if (p == ';') while (soft_charstream_peek(p) != '\n') soft_charstream_skip();
		if (p == '%') soft_preprocessor_read_directive(buf);

		if (is_soft_preprocessor_word(p, 0)) {
			char * str = soft_charstream_read_whilei(is_soft_preprocessor_word);

			struct soft_macro * macro = soft_preprocessor_get_macro(str);
			if (macro != NULL) {
				soft_preprocessor_replace_macro(macro);
			}
			else {
				size_t len = strlen(str);

				len = strlen(str);
				i = i + len;
				if (i + 1 >= size)
					buf = realloc(buf, (size += (i * 1.5) + 1));

				strcat(buf, str);
			}

			macro = NULL;
			free(str);
		}
		else {
			buf[i++] = soft_charstream_consume();
		}
	}

	if (buf[i++] != '\0') {
		buf[i] = '\0';
	}

	return buf;
}
