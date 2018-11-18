#include "vm/vm-test.h"

void soft_vm_test_dynamic_comparison(void ** state)
{
	char * istr = smalloc(sizeof(char) * 2);
	char * dstr = smalloc(sizeof(char) * 5);
	char * nanstr = smalloc(sizeof(char));
	strcpy(istr, "17");
	strcpy(dstr, "17.00");
	strcpy(nanstr, "a");

	sval_t datastore[] = {
		sval_from_int(17),
		sval_from_double(17),
		sval_from_string(istr),
		sval_from_string(dstr),
		sval_from_string(nanstr),
	};

	struct soft_instr instructions[] = {
		sinstr(dload, 1, 0, soft_rax, 0),
		sinstr(dload, 1, 0, soft_rbx, 1),
		sinstr(dload, 1, 0, soft_rcx, 2),
		sinstr(dload, 1, 0, soft_rdx, 3),
		sinstr(deq, 0, soft_rax, soft_rdi, soft_rax),
		sinstr(deq, 0, soft_rax, soft_rsi, soft_rbx),
		sinstr(deq, 0, soft_rax, soft_rsp, soft_rcx),
		sinstr(deq, 0, soft_rax, soft_rbp, soft_rdx),
		sinstr(breakpoint, 0, 0, 0, 0),
		sinstr(dload, 1, 0, soft_rbx, 4),
		sinstr(deq, 0, soft_rax, soft_rdi, soft_rbx),
		sinstr(halt, 0, 0, 0, 0),
	};

	struct soft_program test_program = {
		.datastore = &datastore,
		.instructions = &instructions,
	};

	soft_vm_load_program(&vm, &test_program);
	soft_vm_run_vm(&vm);

	assert_true(sval_is_true(vm.r[soft_rdi]));
	assert_true(sval_is_true(vm.r[soft_rsi]));
	assert_true(sval_is_true(vm.r[soft_rsp]));
	assert_true(sval_is_true(vm.r[soft_rbp]));

	soft_vm_run_vm(&vm);

	assert_true(sval_is_false(vm.r[soft_rdi]));
}
