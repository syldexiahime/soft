#include <stdlib.h>
#include <string.h>

#include "vm/vm-test.h"
#include "preprocessor/preprocessor-test.h"
#include "utils/charstream.h"

soft_preprocessor * preprocessor;

void soft_preprocessor_test_parse_macro_args(void ** state)
{
	preprocessor = soft_preprocessor_init();
	soft_charstream_init("arg1 a_22 3arg");
	soft_macro_args * args = soft_preprocessor_parse_macro_args();
	assert_true(args->length == 2);
	assert_true(strcmp(args->argument_array[0], "arg1") == 0);
	assert_true(strcmp(args->argument_array[1], "a_22") == 0);
}

void soft_preprocessor_test_build_macro(void ** state)
{
	preprocessor = soft_preprocessor_init();
	soft_charstream_init("ello Wor");
	soft_macro_args * args = soft_preprocessor_parse_macro_args();
	char * macro = soft_preprocessor_build_macro("H%1 %2ld!", args);
	assert_true(strcmp(macro, "Hello World!") == 0);
}

void soft_preprocessor_test_replace_macro(void ** state)
{
	preprocessor = soft_preprocessor_init();
	soft_charstream_init("ello Wor");
	soft_macro_args * args = soft_preprocessor_parse_macro_args();
	char * macro = soft_preprocessor_build_macro("H%1 %2ld!", args);
	assert_true(strcmp(macro, "Hello World!") == 0);
}
