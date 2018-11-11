#include "utils/tagged-pointer.h"

inline bool is_tagged_pointer(void * ptr)
{
	return (uintptr_t) ptr & TAGGED_POINTER_MASK;
}

inline void * tag_pointer(void * ptr, uint8_t tagmask)
{
	assert(tagmask <= TAGGED_POINTER_MASK);
	return (void *) ((uintptr_t) ptr | tagmask);
}

inline void * untag_pointer(void * ptr)
{
	return (void *) ((uintptr_t) ptr & ~TAGGED_POINTER_MASK);
}

uint8_t get_pointer_tag(void * ptr)
{
	return (uint8_t) ((uintptr_t) ptr & TAGGED_POINTER_MASK);
}

inline bool check_pointer_tag(void * ptr, uint8_t tag)
{
	return get_pointer_tag(ptr) == tag;
}

