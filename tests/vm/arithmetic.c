#include "vm/soft-vm.h"
#include "vm/vm-test.h"

#define SOFT_VM_ARITHMETIC_TEST(operation, operator, debug) \
	SOFT_VM_INSTR_TEST(operation, operator, int32, debug) \
	SOFT_VM_INSTR_TEST(operation, operator, float, debug)

// Build tests using macros. Honestly this is probably a terrible idea.
SOFT_VM_ARITHMETIC_TEST(add, +, false)
SOFT_VM_ARITHMETIC_TEST(sub, -, false)
SOFT_VM_ARITHMETIC_TEST(mul, *, false)
SOFT_VM_ARITHMETIC_TEST(div, /, false)

void soft_vm_test_add_ptr_reg(void **state)
{
	union SoftData test_ptr, test_add;
	test_ptr.soft_ptr = &test_ptr;
	test_add.soft_int32 = 1;
	void* res = test_ptr.soft_ptr + test_add.soft_int32;
	soft_instr test_program[] = {
		{ soft_instr_load,   soft_ptr,    noop,  0x1, test_ptr },
		{ soft_instr_load,   soft_int32,  noop,  0x2, test_add },
		{ soft_instr_add,    soft_ptr,     0x2,  0x1, {noop} },
		{ halt,            noop,          noop, noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_false(test_ptr.soft_ptr == vm.r[0x1].soft_ptr);
	assert_true(res == vm.r[0x1].soft_ptr);
}

void soft_vm_test_add_ptr_imm(void **state)
{
	union SoftData test_ptr, test_add;
	test_ptr.soft_ptr = &test_ptr;
	test_add.soft_int32 = 1;
	void* res = test_ptr.soft_ptr + test_add.soft_int32;
	soft_instr test_program[] = {
		{ soft_instr_load,   soft_ptr,    noop,  0x1, test_ptr },
		{ soft_instr_add,    soft_ptr,    noop,  0x1, test_add },
		{ halt,            noop,          noop, noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_false(test_ptr.soft_ptr == vm.r[0x1].soft_ptr);
	assert_true(res == vm.r[0x1].soft_ptr);
}

void soft_vm_test_sub_ptr_reg(void **state)
{
	union SoftData test_ptr, test_sub;
	test_ptr.soft_ptr = &test_ptr;
	test_sub.soft_int32 = 1;
	void* res = test_ptr.soft_ptr - test_sub.soft_int32;
	soft_instr test_program[] = {
		{ soft_instr_load,   soft_ptr,    noop,  0x1, test_ptr },
		{ soft_instr_load,   soft_int32,  noop,  0x2, test_sub },
		{ soft_instr_sub,    soft_ptr,     0x2,  0x1, {noop} },
		{ halt,            noop,          noop, noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_false(test_ptr.soft_ptr == vm.r[0x1].soft_ptr);
	assert_true(res == vm.r[0x1].soft_ptr);
}

void soft_vm_test_sub_ptr_imm(void **state)
{
	union SoftData test_ptr, test_sub;
	test_ptr.soft_ptr = &test_ptr;
	test_sub.soft_int32 = 1;
	void* res = test_ptr.soft_ptr - test_sub.soft_int32;
	soft_instr test_program[] = {
		{ soft_instr_load,   soft_ptr,    noop,  0x1, test_ptr },
		{ soft_instr_sub,    soft_ptr,    noop,  0x1, test_sub },
		{ halt,            noop,          noop, noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_false(test_ptr.soft_ptr == vm.r[0x1].soft_ptr);
	assert_true(res == vm.r[0x1].soft_ptr);
}
