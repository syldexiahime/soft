#include "vm/soft-vm.h"
#include "vm/vm-test.h"

#define SOFT_VM_LOAD_TEST(type, value) \
void soft_vm_test_load_##type(void **state) \
{ \
	union SoftData test_data; \
	test_data.soft_##type = value; \
	struct soft_instr test_program[] = { \
		{ soft_instr_load, soft_##type,  noop,  0x1,  test_data }, \
		{ halt,            noop,          noop,  noop, {noop} } \
	}; \
\
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm(&vm); \
\
	assert_true(test_data.soft_##type == vm.r[0x1].soft_##type); \
}
int ptr = 7;

SOFT_VM_LOAD_TEST(ptr, &ptr)
SOFT_VM_LOAD_TEST(int32, 12345)
SOFT_VM_LOAD_TEST(float, 12.45)
