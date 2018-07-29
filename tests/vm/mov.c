#include <malloc/malloc.h>

#include "vm/soft-vm.h"
#include "vm/vm-test.h"

#define _SOFT_VM_MOV_TEST_reg(type, value) \
void soft_vm_test_mov_##type##_reg(void **state) \
{ \
	union SoftData test_data; \
	test_data.soft_##type = value; \
	soft_instr test_program[] = { \
		{ soft_instr_load, soft_int32,  noop,  0x1, test_data }, \
		{ soft_instr_mov,  soft_int32,   0x1,  0x2, {noop} }, \
		{ halt,            noop,        noop, noop, {noop} } \
	}; \
\
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm(&vm); \
\
	assert_true(test_data.soft_##type == vm.r[0x2].soft_##type); \
}

#define _SOFT_VM_MOV_TEST_imm(type, value) \
void soft_vm_test_mov_##type##_imm(void **state) \
{ \
	union SoftData test_data, test_ptr; \
	test_data.soft_##type = value; \
	test_ptr.soft_ptr = malloc(sizeof(test_data)); \
	soft_instr test_program[] = { \
		{ soft_instr_load, soft_int32,  noop,  0x1, test_data }, \
		{ soft_instr_mov,  soft_int32,   0x1, noop, test_ptr }, \
		{ halt,            noop,        noop, noop, {noop} } \
	}; \
\
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm(&vm); \
\
	assert_true(test_data.soft_##type == *((soft_##type##_t*) test_ptr.soft_ptr)); \
}

#define SOFT_VM_MOV_TEST(type, value) \
	_SOFT_VM_MOV_TEST_imm(type, value) \
	_SOFT_VM_MOV_TEST_reg(type, value)

SOFT_VM_MOV_TEST(int32, 12345)
SOFT_VM_MOV_TEST(float, 12.45)
