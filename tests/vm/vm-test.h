#ifndef _SOFT_VM_TEST_H
#define _SOFT_VM_TEST_H

#include "soft-test.h"
#include "vm/soft-vm.h"

#define sinstr(opc, iflg, s, d, im) \
	(struct soft_instr) { .opcode = soft_instr_##opc, .iflag = iflg, .src = s, .dst = d, .imm = im }

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
void soft_vm_test_dloadi(void ** state);
void soft_vm_test_dload(void ** state);

void soft_vm_test_dstore(void ** state);

void soft_vm_test_dmovi(void **state);
void soft_vm_test_dmov(void **state);

/**
 * Dynamic Arithmetic tests
 * */
void soft_vm_test_dynamic_arithmetic(void ** state);
void soft_vm_test_dynamic_comparison(void ** state);

#endif // _SOFT_VM_TEST_H
