#include "vm/soft-vm.h"
#include "vm/vm-test.h"

#define _SOFT_VM_CMP_TEST(soft_type, source, operation, operator, d1, d2, debug) \
void soft_vm_test_##operation##_##soft_type##_##source(void **state) \
{ \
	_SOFT_VM_TEST_SET_TEST_DATA(d1, d2, soft_type, operator); \
	soft_instr test_program[] = _SOFT_VM_TEST_SET_PROGRAM_##source(operation, soft_type, test_data_1, test_data_2) \
	_SOFT_VM_TEST_LOAD_AND_RUN(vm, test_program, debug); \
\
	assert_true((d1 operator d2) == vm.zf); \
\
	soft_instr test_program_2[] = _SOFT_VM_TEST_SET_PROGRAM_##source(operation, soft_type, test_data_1, test_data_1) \
	_SOFT_VM_TEST_LOAD_AND_RUN(vm, test_program_2, debug); \
\
	assert_true((d1 operator d1) == vm.zf); \
}

#define _SOFT_VM_COMPARISON_TEST(operation, operator, soft_type, d1, d2, debug) \
	_SOFT_VM_CMP_TEST(soft_type, imm, operation, operator, 23, 87, false) \
	_SOFT_VM_CMP_TEST(soft_type, reg, operation, operator, 23, 87, false)

#define SOFT_VM_COMPARISON_TEST(operation, operator, d1, d2, debug) \
	_SOFT_VM_COMPARISON_TEST(operation, operator, int32, d1, d2, debug) \
	_SOFT_VM_COMPARISON_TEST(operation, operator, float, d1, d2, debug)

SOFT_VM_COMPARISON_TEST(eq,   ==, 23, 87, false)
SOFT_VM_COMPARISON_TEST(gt,    >, 23, 87, false)
SOFT_VM_COMPARISON_TEST(lt,    <, 23, 87, false)
SOFT_VM_COMPARISON_TEST(gteq, >=, 23, 87, false)
SOFT_VM_COMPARISON_TEST(lteq, <=, 23, 87, false)
