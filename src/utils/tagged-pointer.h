#ifndef _SOFT_TAGGED_POINTERS_H
#define _SOFT_TAGGED_POINTERS_H

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

#include "utils/helpers.h"

#define TAGGED_POINTER_MASK 0b111

typedef void * tagged_pointer_t;

bool is_tagged_pointer(void * ptr);

void * tag_pointer(void * ptr, uint8_t tag);
void * untag_pointer(void * ptr);

uint8_t get_pointer_tag(void * ptr);
bool check_pointer_tag(void * ptr, uint8_t tag);

#endif // _SOFT_TAGGED_POINTERS_H
