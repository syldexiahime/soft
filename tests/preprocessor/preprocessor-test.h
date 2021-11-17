#ifndef _SOFT_PREPROCESSOR_TEST_H
#define _SOFT_PREPROCESSOR_TEST_H

#include "soft-test.h"
#include "preprocessor/preprocessor.h"

/**
 * Non public preprocessor functions
 * */
soft_macro_args * soft_preprocessor_parse_macro_args();
char * soft_preprocessor_build_macro(char * macro, soft_macro_args * arguments);
void soft_preprocessor_replace_macro(soft_macro * macro);
void soft_preprocessor_define_macro(char * nbuf);

/**
 * Preprocessor tests
 * */
void soft_preprocessor_test_parse_macro_args(void ** state);
void soft_preprocessor_test_build_macro(void ** state);
void soft_preprocessor_test_define_macro(void ** state);

#endif // _SOFT_PREPROCESSOR_TEST_H
