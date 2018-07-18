#include "vm/soft-vm.h"
#include "vm/vm-test.h"

void soft_vm_test_load_int32(void **state)
{
	union SoftData test_data;
	test_data.soft_int32 = 12345;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_int32_t,  noop,  0x1,  {test_data.soft_int32} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(test_data.soft_int32 == vm.r[0x1].soft_int32);
}

void soft_vm_test_load_float(void **state)
{
	union SoftData test_data;
	test_data.soft_float = 0x4293f5c3;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_float_t,  noop,  0x1,  {test_data.soft_int32} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(test_data.soft_float == vm.r[0x1].soft_float);
}
