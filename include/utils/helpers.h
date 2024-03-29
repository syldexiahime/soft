#ifndef _SOFT_HELPERS_H
#define _SOFT_HELPERS_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define reinterpret_cast(type_to, type_from, value) \
	((union { type_from from; type_to to; }) { (value) }.to)

int    parse_int(char * s);
int    parse_hex(char * s);
int    parse_oct(char * s);
float  parse_float(char * s);
double parse_double(char * s);

char * int_to_str(int i);
char * float_to_str(float f);
char * double_to_str(double f);

bool ishex(char c);
bool isoct(char c);
bool isbin(char c);

bool str_is_int(char * str);
bool str_is_double(char * str);
bool str_is_number(char * str);

char * str_replace_at(char * dst, char * src, size_t pos, size_t len);

// temporary definiton, replace with actual implementation later
#define smalloc(size) malloc(size)
#define srealloc(var, size) realloc(var, size)
#define scalloc(num, size) calloc(num, size)
#define sfree(ptr) free(ptr)

#endif // _SOFT_HELPERS_H
