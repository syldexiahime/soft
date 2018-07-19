#include "vm/soft-vm.h"
#include "vm/vm-test.h"

void soft_vm_test_and_int_reg(void **state)
{
	union SoftData bin_1, bin_2;
	int res;
	bin_1.soft_int32 = 0b00111100;
	bin_2.soft_int32 = 0b00001101;
	res              = 0b00001100;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_int32_t,  noop,  0x1,  {bin_1.soft_int32} },
		{ soft_instr_load, soft_int32_t,  noop,  0x2,  {bin_2.soft_int32} },
		{ soft_instr_and,  soft_int32_t,   0x1,  0x2,  {noop} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(res == vm.r[0x2].soft_int32);
}

void soft_vm_test_and_float_reg(void **state)
{
	union SoftData bin_1, bin_2;
	int res;
	bin_1.soft_int32 = 0b00111100;
	bin_2.soft_int32 = 0b00001101;
	res              = 0b00001100;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_float_t,  noop,  0x1,  {bin_1.soft_int32} },
		{ soft_instr_load, soft_float_t,  noop,  0x2,  {bin_2.soft_int32} },
		{ soft_instr_and,  soft_float_t,   0x1,  0x2,  {noop} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(res == vm.r[0x2].soft_int32);
}
