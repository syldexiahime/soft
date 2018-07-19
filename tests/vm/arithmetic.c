#include "vm/soft-vm.h"
#include "vm/vm-test.h"

#define _ARITHMETIC_TEST_SET_TEST_DATA(d1, d2, soft_type, operator) \
	union SoftData test_data_1; \
	union SoftData test_data_2; \
	union SoftData res; \
	test_data_1.soft_##soft_type = d1; \
	test_data_2.soft_##soft_type = d2; \
	res.soft_##soft_type = test_data_1.soft_##soft_type operator test_data_2.soft_##soft_type;

#define _ARITHMETIC_TEST_SET_PROGRAM_reg(operation, soft_type) \
	soft_instr test_program[] = { \
		{ soft_instr_load, soft_##soft_type##_t,  noop,  0x1,  {test_data_1.soft_int32} }, \
		{ soft_instr_load, soft_##soft_type##_t,  noop,  0x2,  {test_data_2.soft_int32} }, \
		{ soft_instr_##operation,  soft_##soft_type##_t,  0x2,   0x1,  {noop} }, \
		{ halt,            noop,          noop,  noop, {noop} } \
	}; \

#define _ARITHMETIC_TEST_SET_PROGRAM_imm(operation, soft_type) \
	soft_instr test_program[] = { \
		{ soft_instr_load, soft_##soft_type##_t,  noop,  0x1,  {test_data_1.soft_int32} }, \
		{ soft_instr_##operation, soft_##soft_type##_t,  noop,  0x1,  {test_data_2.soft_int32} }, \
		{ halt,            noop,          noop,  noop, {noop} } \
	}; \


#define _ARITHMETIC_TEST(operation, operator, soft_type, source, debug) \
void soft_vm_test_##operation##_##soft_type##_##source(void **state) \
{ \
	_ARITHMETIC_TEST_SET_TEST_DATA(23, 47, soft_type, operator); \
\
	_ARITHMETIC_TEST_SET_PROGRAM_##source(operation, soft_type) \
\
	if (debug) { \
		_SOFT_VM_TEST_LOAD_AND_RUN_DEBUG(vm, test_program); \
		printf("res: 0x%04X\nreg: 0x%04X\n", res.soft_int32, vm.r[0x1].soft_int32); \
	} \
	else { \
		_SOFT_VM_TEST_LOAD_AND_RUN(vm, test_program); \
	} \
\
	assert_true(res.soft_##soft_type == vm.r[0x1].soft_##soft_type); \
}

#define ARITHMETIC_TEST(operation, operator, soft_type, debug) \
	_ARITHMETIC_TEST(operation, operator, soft_type, reg, debug); \
	_ARITHMETIC_TEST(operation, operator, soft_type, imm, debug);

// Build tests using macros. Honestly this is probably a terrible idea.
ARITHMETIC_TEST(add, +, int32, false)
ARITHMETIC_TEST(sub, -, int32, false)
ARITHMETIC_TEST(mul, *, int32, false)
ARITHMETIC_TEST(div, /, int32, false)

ARITHMETIC_TEST(add, +, float, false)
ARITHMETIC_TEST(sub, -, float, false)
ARITHMETIC_TEST(mul, *, float, false)
ARITHMETIC_TEST(div, /, float, false)
