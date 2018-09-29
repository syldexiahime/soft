#ifndef _SOFT_PREPROCESSOR_H
#define _SOFT_PREPROCESSOR_H

#include "soft.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils/charstream.h"
#include "utils/helpers.h"

typedef struct {
	size_t  length;
	size_t  size;
	char ** argument_array;
} soft_macro_args;

typedef struct {
	char * name;
	char * body;
} soft_macro;

typedef struct {
	soft_macro ** macro_array;
	size_t length;
	size_t size;
} soft_macros;

typedef struct {
	soft_macros *   macros;
	struct soft_compiler_warnings * warnings;
} soft_preprocessor;

soft_preprocessor * soft_preprocessor_init();
char * soft_asm_preprocess(char * buffer);

#endif // _SOFT_PREPROCESSOR_H
