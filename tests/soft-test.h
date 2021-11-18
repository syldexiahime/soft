#ifndef _SOFT_TEST_H
#define _SOFT_TEST_H

#include "soft.h"

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>
#include <string.h>

struct dump_memory_args {
	char * arr;
	size_t len;
};
#define dump_memory(...) dump_memory((struct dump_memory_args){__VA_ARGS__})
static inline void (dump_memory) (struct dump_memory_args args)
{
	char * arr = args.arr;
	size_t len = args.len ? args.len : strlen(arr);

	printf("--[arr]-----------------------\n");
	for (size_t i = 0; i < len; i+=8) {
		printf("%04zu:", i);
		for (size_t k = i; k < i + 8; k++) {
			if (k - i == 4)
				printf(" ");

			if (k < len)
				printf(" %02x", (unsigned) (unsigned char) arr[i + k]);
			else
				printf("   ");
		}
		printf("    ");
		for (size_t k = i; (k < i + 8) && (k < len); k++) {
			char * ch = alloca(sizeof(char) * 3);
			ch[1] = '\0';
			switch (arr[i + k]) {
				case '\n': ch = "\\n"; break;
				default: ch[0] = arr[i + k]; break;
			}
			printf("%s", ch);
		}
		printf("\n");
	}
}

#endif // _SOFT_TEST_H
