#include "utils/util-test.h"

void soft_test_tagged_pointers(void ** state)
{
	uint8_t tag = 0b11;
	void * ptr = malloc(sizeof(void *));

	tagged_pointer_t tptr = tag_pointer(ptr, tag);

	assert_true(ptr != tptr);
	assert_false(is_tagged_pointer(ptr));
	assert_true(is_tagged_pointer(tptr));

	assert_true(untag_pointer(tptr) == ptr);
	assert_true(get_pointer_tag(tptr) == tag);
	assert_true(check_pointer_tag(tptr, tag));
	assert_false(check_pointer_tag(tptr, 0b111));
}
