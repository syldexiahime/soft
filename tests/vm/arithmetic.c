#include "vm/soft-vm.h"
#include "vm/vm-test.h"

void soft_vm_test_add_int32_reg(void **state)
{
	union SoftData test_data_1; 
	union SoftData test_data_2;
	int sum;
	test_data_1.soft_int32 = 27;
	test_data_2.soft_int32 = 44;
	sum = test_data_1.soft_int32 + test_data_2.soft_int32;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_float_t,  noop,  0x1,  {test_data_1.soft_int32} },
		{ soft_instr_load, soft_float_t,  noop,  0x2,  {test_data_2.soft_int32} },
		{ soft_instr_add,  soft_float_t,  0x1,   0x2,  {noop} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(sum == vm.r[0x2].soft_int32);
}

void soft_vm_test_add_int32_imm(void **state)
{
	union SoftData test_data_1; 
	union SoftData test_data_2;
	int sum;
	test_data_1.soft_int32 = 27;
	test_data_2.soft_int32 = 44;
	sum = test_data_1.soft_int32 + test_data_2.soft_int32;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_float_t,  noop,  0x1,  {test_data_1.soft_int32} },
		{ soft_instr_add,  soft_float_t,  noop,  0x1,  {test_data_2.soft_int32} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(sum == vm.r[0x1].soft_int32);
}

void soft_vm_test_add_float_reg(void **state)
{
	union SoftData test_data_1; 
	union SoftData test_data_2;
	float sum;
	test_data_1.soft_float = 27.3;
	test_data_2.soft_float = 44.4;
	sum = test_data_1.soft_float + test_data_2.soft_float;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_float_t,  noop,  0x1,  {test_data_1.soft_int32} },
		{ soft_instr_load, soft_float_t,  noop,  0x2,  {test_data_2.soft_int32} },
		{ soft_instr_add,  soft_float_t,  0x1,   0x2,  {noop} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(sum == vm.r[0x2].soft_float);
}

void soft_vm_test_add_float_imm(void **state)
{
	union SoftData test_data_1; 
	union SoftData test_data_2;
	float sum;
	test_data_1.soft_float = 27.3;
	test_data_2.soft_float = 44.4;
	sum = test_data_1.soft_float + test_data_2.soft_float;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_float_t,  noop,  0x1,  {test_data_1.soft_int32} },
		{ soft_instr_add,  soft_float_t,  noop,  0x1,  {test_data_2.soft_int32} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(sum == vm.r[0x1].soft_float);
}
