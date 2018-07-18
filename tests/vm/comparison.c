#include "vm/soft-vm.h"
#include "vm/vm-test.h"

void soft_vm_test_eq_reg_int32(void **state)
{
	union SoftData test_data_1, test_data_2;
	test_data_1.soft_int32 = 29;
	test_data_2.soft_int32 = 83;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_int32_t,  noop,  0x1,  {test_data_1.soft_int32} },
		{ soft_instr_load, soft_int32_t,  noop,  0x2,  {test_data_2.soft_int32} },
		{ soft_instr_eq,   soft_int32_t,   0x1,  0x2,  {noop} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(false == vm.zf);

	soft_instr test_program_2[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_int32_t,  noop,  0x1,  {test_data_1.soft_int32} },
		{ soft_instr_load, soft_int32_t,  noop,  0x2,  {test_data_1.soft_int32} },
		{ soft_instr_eq,   soft_int32_t,   0x1,  0x2,  {noop} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program_2);
	soft_vm_run_vm(&vm);

	assert_true(true == vm.zf);
}
