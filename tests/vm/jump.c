#include "vm/soft-vm.h"
#include "vm/vm-test.h"

void soft_vm_test_jmp(void **state)
{
	union SoftData test_data_1, test_data_2;
	test_data_1.soft_float = 10.23;
	test_data_2.soft_float = 274.86;
	struct soft_instr test_program[] = {
		{ soft_instr_load, soft_int32,  noop,  0x1,  {test_data_1.soft_int32} }, // 0
		{ soft_instr_jmp,          noop,  noop,  noop, {3} }, // 1
		{ soft_instr_load, soft_int32,  noop,  0x1,  {test_data_2.soft_int32} }, // 2
		{ halt,            noop,          noop,  noop, {noop} } // 3
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(test_data_1.soft_float == vm.r[0x1].soft_float);
	assert_true(test_data_2.soft_float != vm.r[0x1].soft_float);
}

void soft_vm_test_jmpz(void **state)
{
	union SoftData test_data_1, test_data_2;
	test_data_1.soft_float = 10.23;
	test_data_2.soft_float = 274.86;
	struct soft_instr test_program[] = {
		{ soft_instr_load, soft_int32,  noop,  0x1,  {test_data_1.soft_int32} }, // 0
		{ soft_instr_eq,   soft_int32,  noop,  0x1,  {test_data_1.soft_int32} }, // 1
		{ soft_instr_jmpz,         noop,  noop,  noop, {4} }, // 2
		{ soft_instr_load, soft_int32,  noop,  0x1,  {test_data_2.soft_int32} }, // 3
		{ halt,            noop,          noop,  noop, {noop} } // 4
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(test_data_1.soft_float == vm.r[0x1].soft_float);
	assert_true(test_data_2.soft_float != vm.r[0x1].soft_float);
}

void soft_vm_test_jmpnz(void **state)
{
	union SoftData test_data_1, test_data_2;
	test_data_1.soft_float = 10.23;
	test_data_2.soft_float = 274.86;
	struct soft_instr test_program[] = {
		{ soft_instr_load, soft_int32,  noop,  0x1,  {test_data_1.soft_int32} }, // 0
		{ soft_instr_eq,   soft_int32,  noop,  0x1,  {test_data_2.soft_int32} }, // 1
		{ soft_instr_jmpnz,        noop,  noop,  noop, {4} }, // 2
		{ soft_instr_load, soft_int32,  noop,  0x1,  {test_data_2.soft_int32} }, // 3
		{ halt,            noop,          noop,  noop, {noop} } // 4
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(test_data_1.soft_float == vm.r[0x1].soft_float);
	assert_true(test_data_2.soft_float != vm.r[0x1].soft_float);
}
