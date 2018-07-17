#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "soft.h"
#include "vm/soft-vm.h"

soft_VM vm;

static void soft_vm_test_load_reg_int32(void **state)
{
	union SoftData test_data;
	test_data.soft_int32 = 0x23;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_int32_t,  noop,  0x1,  {test_data.soft_int32} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(test_data.soft_int32 == vm.r[0x1].soft_int32);
}

static void soft_vm_test_load_reg_float(void **state)
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

/* A test case that does nothing and succeeds. */
static void soft_vm_test_add_float_reg(void **state)
{
	union SoftData float_1; 
	union SoftData float_2;
	float sum;
	float_1.soft_float = 27.3;
	float_2.soft_float = 44.4;
	sum = float_1.soft_float + float_2.soft_float;
	soft_instr test_program[] = {
		// opcode,         datatype,      src,   dest, immediate
		{ soft_instr_load, soft_float_t,  noop,  0x1,  {float_1.soft_int32} },
		{ soft_instr_load, soft_float_t,  noop,  0x2,  {float_2.soft_int32} },
		{ soft_instr_add,  soft_float_t,  0x1,   0x2,  {noop} },
		{ halt,            noop,          noop,  noop, {noop} }
	};

	soft_vm_load_program(&vm, test_program);
	soft_vm_run_vm(&vm);

	assert_true(sum == vm.r[0x2].soft_float);
}

static void soft_vm_test_eq_reg_int32(void **state)
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

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(soft_vm_test_load_reg_int32),
        cmocka_unit_test(soft_vm_test_load_reg_float),
        cmocka_unit_test(soft_vm_test_add_float_reg),
		cmocka_unit_test(soft_vm_test_eq_reg_int32),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
