#ifndef _SOFT_PREPROCESSOR_H
#define _SOFT_PREPROCESSOR_H

#include "soft.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils/charstream.h"
#include "utils/helpers.h"

struct soft_macro_args {
	size_t  length;
	size_t  size;
	char ** argument_array;
};

struct soft_macro {
	char * name;
	char * body;
};

struct soft_macros {
	struct soft_macro ** macro_array;
	size_t length;
	size_t size;
};

struct soft_preprocessor {
	struct soft_macros * macros;
	struct soft_compiler_warnings * warnings;
};

struct soft_preprocessor * soft_preprocessor_init ();
char * soft_preprocessor_preprocess (char * buffer);

#endif // _SOFT_PREPROCESSOR_H
