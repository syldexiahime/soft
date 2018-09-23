#include <stdlib.h>

#include "vm/soft-vm.h"
#include "vm/vm-test.h"

#define _SOFT_VM_MOV_REG_TEST_to_reg(type, value) \
void soft_vm_test_mov_reg_##type##_to_reg(void **state) \
{ \
	union SoftData test_data; \
	test_data.soft_##type = value; \
	struct soft_instr test_program[] = { \
		{ soft_instr_load,   soft_##type,  noop,  0x1, test_data }, \
		{ soft_instr_movreg, soft_##type,   0x1,  0x2, {noop} }, \
		{ halt,            noop,        noop, noop, {noop} } \
	}; \
\
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm(&vm); \
\
	assert_true(test_data.soft_##type == vm.r[0x2].soft_##type); \
}

#define _SOFT_VM_MOV_REG_TEST_to_addr(type, value) \
void soft_vm_test_mov_reg_##type##_to_addr(void **state) \
{ \
	union SoftData test_data, test_ptr; \
	test_data.soft_##type = value; \
	test_ptr.soft_ptr = malloc(sizeof(test_data)); \
	struct soft_instr test_program[] = { \
		{ soft_instr_load,    soft_##type,  noop,  0x1, test_data }, \
		{ soft_instr_movreg,  soft_##type,   0x1, noop, test_ptr }, \
		{ halt,            noop,        noop, noop, {noop} } \
	}; \
\
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm(&vm); \
\
	assert_true(test_data.soft_##type == *((soft_##type##_t*) test_ptr.soft_ptr)); \
}

#define _SOFT_VM_MOV_ADDR_TEST_to_reg(type, value) \
void soft_vm_test_mov_addr_##type##_to_reg(void **state) \
{ \
	union SoftData test_data, test_ptr; \
	test_data.soft_##type = value; \
	test_ptr.soft_ptr = malloc(sizeof(test_data)); \
	*((soft_##type##_t*) test_ptr.soft_ptr) = test_data.soft_##type; \
	struct soft_instr test_program[] = { \
		{ soft_instr_load,    soft_ptr,     noop,  0x1, test_ptr }, \
		{ soft_instr_movaddr, soft_##type,   0x1,  0x2, {noop} }, \
		{ halt,            noop,        noop, noop, {noop} } \
	}; \
\
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm(&vm); \
\
	assert_true(test_data.soft_##type == vm.r[0x2].soft_##type); \
}

#define _SOFT_VM_MOV_ADDR_TEST_to_addr(type, value) \
void soft_vm_test_mov_addr_##type##_to_addr(void **state) \
{ \
	union SoftData test_data, test_ptr, test_ptr_2; \
	test_data.soft_##type = value; \
	test_ptr.soft_ptr = malloc(sizeof(test_data)); \
	test_ptr_2.soft_ptr = malloc(sizeof(test_data)); \
	*((soft_##type##_t*)test_ptr.soft_ptr) = value; \
	struct soft_instr test_program[] = { \
		{ soft_instr_load,    soft_ptr,     noop,  0x1, test_ptr }, \
		{ soft_instr_movaddr, soft_##type,   0x1, noop, test_ptr_2 }, \
		{ halt,            noop,        noop, noop, {noop} } \
	}; \
\
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm(&vm); \
\
	assert_true(test_data.soft_##type == *((soft_##type##_t*) test_ptr_2.soft_ptr)); \
}

#define SOFT_VM_MOV_TEST(type, value) \
	_SOFT_VM_MOV_REG_TEST_to_reg(type, value) \
	_SOFT_VM_MOV_REG_TEST_to_addr(type, value) \
	_SOFT_VM_MOV_ADDR_TEST_to_reg(type, value) \
	_SOFT_VM_MOV_ADDR_TEST_to_addr(type, value)

SOFT_VM_MOV_TEST(int32, 12345)
SOFT_VM_MOV_TEST(float, 12.45)
