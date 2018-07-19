#ifndef _SOFT_VM_TEST_H
#define _SOFT_VM_TEST_H

#include "soft-test.h"
#include "vm/soft-vm.h"

#define _SOFT_VM_TEST_LOAD_AND_RUN(vm, program) \
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm(&vm);

#define _SOFT_VM_TEST_LOAD_AND_RUN_DEBUG(vm, program) \
	soft_vm_load_program(&vm, test_program); \
	soft_vm_run_vm_debug(&vm); \
	printf("\n");

soft_VM vm;

/**
 * Load instruction tests
 * */
void soft_vm_test_load_int32(void **state);
void soft_vm_test_load_float(void **state);

/**
 * Arithmetic instruction tests
 * */
void soft_vm_test_add_int32_reg(void **state);
void soft_vm_test_sub_int32_reg(void **state);
void soft_vm_test_mul_int32_reg(void **state);
void soft_vm_test_div_int32_reg(void **state);

void soft_vm_test_add_int32_imm(void **state);
void soft_vm_test_sub_int32_imm(void **state);
void soft_vm_test_mul_int32_imm(void **state);
void soft_vm_test_div_int32_imm(void **state);

void soft_vm_test_add_float_reg(void **state);
void soft_vm_test_sub_float_reg(void **state);
void soft_vm_test_mul_float_reg(void **state);
void soft_vm_test_div_float_reg(void **state);

void soft_vm_test_add_float_imm(void **state);
void soft_vm_test_sub_float_imm(void **state);
void soft_vm_test_mul_float_imm(void **state);
void soft_vm_test_div_float_imm(void **state);


/**
 * Comparison instruction tests
 * */
void soft_vm_test_eq_reg_int32(void **state);

/**
 * Binary instruction tests
 * */
void soft_vm_test_and_float_reg(void **state);

#endif // _SOFT_VM_TEST_H
