#ifndef _SOFT_VM_TEST_H
#define _SOFT_VM_TEST_H

#include "soft-test.h"
#include "vm/soft-vm.h"

#define _SOFT_VM_TEST_LOAD_AND_RUN_NDEBUG(vm, program) \
	soft_vm_load_program(&vm, program); \
	soft_vm_run_vm(&vm);

#define _SOFT_VM_TEST_LOAD_AND_RUN_DEBUG(vm, program) \
	soft_vm_load_program(&vm, program); \
	soft_vm_run_vm_debug(&vm); \
	printf("\n");

#define _SOFT_VM_TEST_LOAD_AND_RUN(vm, program, debug) \
	if (debug) { \
		_SOFT_VM_TEST_LOAD_AND_RUN_DEBUG(vm, program); \
		printf("res: 0x%04X\nreg: 0x%04X\n", res.soft_int32, vm.r[0x1].soft_int32); \
	} \
	else { \
		_SOFT_VM_TEST_LOAD_AND_RUN_NDEBUG(vm, program); \
	}

#define _SOFT_VM_TEST_SET_TEST_DATA(d1, d2, soft_type, operator) \
	union SoftData test_data_1; \
	union SoftData test_data_2; \
	union SoftData res; \
	test_data_1.soft_##soft_type = d1; \
	test_data_2.soft_##soft_type = d2; \
	res.soft_##soft_type = test_data_1.soft_##soft_type operator test_data_2.soft_##soft_type;

#define _SOFT_VM_TEST_SET_PROGRAM_reg(operation, soft_type, td1, td2) \
	{ \
		{ soft_instr_load, soft_##soft_type,  noop,  0x1,  {td1.soft_int32} }, \
		{ soft_instr_load, soft_##soft_type,  noop,  0x2,  {td2.soft_int32} }, \
		{ soft_instr_##operation,  soft_##soft_type,  0x2,   0x1,  {noop} }, \
		{ halt,            noop,          noop,  noop, {noop} } \
	};

#define _SOFT_VM_TEST_SET_PROGRAM_imm(operation, soft_type, td1, td2) \
	{ \
		{ soft_instr_load, soft_##soft_type,  noop,  0x1,  {td1.soft_int32} }, \
		{ soft_instr_##operation, soft_##soft_type,  noop,  0x1,  {td2.soft_int32} }, \
		{ halt,            noop,          noop,  noop, {noop} } \
	};

#define _SOFT_VM_INSTR_TEST(operation, operator, soft_type, source, debug) \
void soft_vm_test_##operation##_##soft_type##_##source(void **state) \
{ \
	_SOFT_VM_TEST_SET_TEST_DATA(23, 47, soft_type, operator); \
\
	struct soft_instr test_program[] = _SOFT_VM_TEST_SET_PROGRAM_##source(operation, soft_type, test_data_1, test_data_2) \
\
	_SOFT_VM_TEST_LOAD_AND_RUN(vm, test_program, debug); \
\
	assert_true(res.soft_##soft_type == vm.r[0x1].soft_##soft_type); \
}

#define SOFT_VM_INSTR_TEST(operation, operator, soft_type, debug) \
	_SOFT_VM_INSTR_TEST(operation, operator, soft_type, reg, debug); \
	_SOFT_VM_INSTR_TEST(operation, operator, soft_type, imm, debug);

struct soft_vm vm;

/**
 * Load instruction tests
 * */
void soft_vm_test_load_int32(void **state);
void soft_vm_test_load_float(void **state);
void soft_vm_test_load_ptr(void **state);

void soft_vm_test_mov_reg_int32_to_reg(void **state);
void soft_vm_test_mov_reg_float_to_reg(void **state);
void soft_vm_test_mov_reg_int32_to_addr(void **state);
void soft_vm_test_mov_reg_float_to_addr(void **state);
void soft_vm_test_mov_addr_int32_to_reg(void **state);
void soft_vm_test_mov_addr_float_to_reg(void **state);
void soft_vm_test_mov_addr_int32_to_addr(void **state);
void soft_vm_test_mov_addr_float_to_addr(void **state);

/**
 * Arithmetic instruction tests
 * */
#define _SOFT_VM_TEST_FUNCTION_DEFINITION_SOURCE(instruction, type) \
	void soft_vm_test_##instruction##_##type##_reg(void **state); \
	void soft_vm_test_##instruction##_##type##_imm(void **state);

#define SOFT_VM_ARITHMETIC_TEST_FUNCTION_DEFINITION(instruction) \
	_SOFT_VM_TEST_FUNCTION_DEFINITION_SOURCE(instruction, int32) \
	_SOFT_VM_TEST_FUNCTION_DEFINITION_SOURCE(instruction, float)

SOFT_VM_ARITHMETIC_TEST_FUNCTION_DEFINITION(add)
SOFT_VM_ARITHMETIC_TEST_FUNCTION_DEFINITION(sub)
SOFT_VM_ARITHMETIC_TEST_FUNCTION_DEFINITION(mul)
SOFT_VM_ARITHMETIC_TEST_FUNCTION_DEFINITION(div)

void soft_vm_test_add_ptr_reg(void **state);
void soft_vm_test_add_ptr_imm(void **state);
void soft_vm_test_sub_ptr_imm(void **state);
void soft_vm_test_sub_ptr_reg(void **state);


/**
 * Binary instruction tests
 * */
void soft_vm_test_and_int32_reg(void **state);
void soft_vm_test_or_int32_reg(void **state);
void soft_vm_test_xor_int32_reg(void **state);
void soft_vm_test_lshift_int32_reg(void **state);
void soft_vm_test_rshift_int32_reg(void **state);
void soft_vm_test_not_int32_reg(void **state);

void soft_vm_test_and_int32_imm(void **state);
void soft_vm_test_or_int32_imm(void **state);
void soft_vm_test_xor_int32_imm(void **state);
void soft_vm_test_lshift_int32_imm(void **state);
void soft_vm_test_rshift_int32_imm(void **state);
void soft_vm_test_not_int32_imm(void **state);

/**
 * Comparison instruction tests
 * */
#define SOFT_VM_COMPARISON_TEST_FUNCTION_DEFINITION(instruction) \
	_SOFT_VM_TEST_FUNCTION_DEFINITION_SOURCE(instruction, int32) \
	_SOFT_VM_TEST_FUNCTION_DEFINITION_SOURCE(instruction, float)

SOFT_VM_COMPARISON_TEST_FUNCTION_DEFINITION(eq)
SOFT_VM_COMPARISON_TEST_FUNCTION_DEFINITION(gt)
SOFT_VM_COMPARISON_TEST_FUNCTION_DEFINITION(lt)
SOFT_VM_COMPARISON_TEST_FUNCTION_DEFINITION(gteq)
SOFT_VM_COMPARISON_TEST_FUNCTION_DEFINITION(lteq)

/**
 * Jump instruction tests
 * */

void soft_vm_test_jmp(void **state);
void soft_vm_test_jmpz(void **state);
void soft_vm_test_jmpnz(void **state);

#endif // _SOFT_VM_TEST_H
