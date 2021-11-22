#include <stdlib.h>
#include <string.h>

#include "vm/vm-test.h"
#include "preprocessor/preprocessor-test.h"
#include "utils/charstream.h"

static struct soft_preprocessor * preprocessor;

void soft_preprocessor_test_parse_macro_args (void ** state)
{
	preprocessor = soft_preprocessor_init();
	soft_charstream_init("arg1 a_22 3arg");
	struct soft_macro_args * args = soft_preprocessor_parse_macro_args();
	assert_true(args->length == 2);
	assert_true(strcmp(args->argument_array[0], "arg1") == 0);
	assert_true(strcmp(args->argument_array[1], "a_22") == 0);
}

void soft_preprocessor_test_build_macro (void ** state)
{
	preprocessor = soft_preprocessor_init();
	soft_charstream_init("ello Wor");
	struct soft_macro_args * args = soft_preprocessor_parse_macro_args();
	char * macro = soft_preprocessor_build_macro("H%1 %2ld!", args);
	assert_true(strcmp(macro, "Hello World!") == 0);
}

void soft_preprocessor_test_define_macro (void ** state)
{
	preprocessor = soft_preprocessor_init();
	soft_charstream_init("maca\nma\ncro\n%endmacro");

	char * buf = malloc(256 * sizeof(char));
	soft_preprocessor_define_macro(buf);

	struct soft_macro * macro = preprocessor->macros->macro_array[0];

	assert_true(macro != NULL);
	assert_true(strcmp(macro->name, "maca") == 0);
	assert_true(strcmp(macro->body, "\nma\ncro\n") == 0);
}
