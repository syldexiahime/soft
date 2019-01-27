#ifndef _SOFT_VM_TEST_H
#define _SOFT_VM_TEST_H

#include "soft-test.h"
#include "vm/soft-vm.h"

#define sinstr(opc, s, d, im) \
	(struct soft_instr) { .opcode = soft_instr_##opc, .src = s, .dst = d, .imm = im }

struct soft_vm vm;

/**
 * Sval tests
 * */
void soft_test_sval_null(void ** state);
void soft_test_sval_nan(void ** state);
void soft_test_sval_true(void ** state);
void soft_test_sval_false(void ** state);
void soft_test_sval_bool(void ** state);
void soft_test_sval_int(void ** state);
void soft_test_sval_double(void ** state);
void soft_test_sval_pointer(void ** state);
void soft_test_sval_string(void ** state);
void soft_test_sval_falsey(void ** state);
void soft_test_sval_casts(void ** state);
void soft_test_sval_arithmetic_int(void ** state);
void soft_test_sval_arithmetic_double(void ** state);
void soft_test_sval_arithmetic_string(void ** state);

/**
 * Load instruction tests
 * */
void soft_vm_test_load_dw(void ** state);
void soft_vm_test_loadi(void ** state);

void soft_vm_test_store_dw(void ** state);

void soft_vm_test_movi(void ** state);
void soft_vm_test_mov(void ** state);

void soft_vm_test_dynamic_arithmetic(void ** state);
void soft_vm_test_dynamic_comparison(void ** state);
void soft_vm_test_dynamic_bitwise(void ** state);

void soft_vm_test_push_dw_and_pop_dw(void ** state);

void soft_vm_test_jmp(void ** state);
void soft_vm_test_jmpz(void ** state);
void soft_vm_test_jmpnz(void ** state);
void soft_vm_test_jmpgt(void ** state);
void soft_vm_test_jmpgte(void ** state);
void soft_vm_test_jmplt(void ** state);
void soft_vm_test_jmplte(void ** state);

#endif // _SOFT_VM_TEST_H
