#include <assert.h>
#include "soft-vm.h"

void soft_vm_init_vm(soft_VM *vm)
{
	vm->running = false;
	vm->pc = 0;
	for (int i = 0; i < SOFT_VM_NUM_REGS; i ++) {
		vm->r[i].soft_int32 = 0;
	}
	vm->zf = false;
}

void soft_vm_load_program(soft_VM *vm, soft_instr *new_program)
{
	vm->program = new_program;
	soft_vm_init_vm(vm);
}

void soft_vm_decode_instr(soft_VM *vm, soft_instr instr)
{
	switch (instr.opcode) {
		case halt: vm->running = false; break;
		case noop: break;

		case soft_instr_load: SOFT_VM_EXECUTE_INSTR(vm, instr, LOAD,) break;

		case soft_instr_add: SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, +); break;
		case soft_instr_sub: SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, -); break;
		case soft_instr_mul: SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, *); break;
		case soft_instr_div: SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, /); break;

		case soft_instr_eq:   SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, ==); break;
		case soft_instr_gt:   SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, >);  break;
		case soft_instr_lt:   SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, <);  break;
		case soft_instr_gteq: SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, >=); break;
		case soft_instr_lteq: SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, <=); break;

		default: assert(false); break;
	}
}

void soft_vm_show_registers(soft_VM *vm)
{
	printf("Instruction: %d\n", vm->pc);
	printf("R: ");
	for (int i = 0; i < SOFT_VM_NUM_REGS; i++) {
		printf("0x%04X ", vm->r[i].soft_int32);
		printf("(%f) ", vm->r[i].soft_float);
	}
	printf("\n");
}

void soft_vm_run_vm(soft_VM *vm)
{
	vm->running = true;

	while (vm->running == true) {
		soft_vm_decode_instr(vm, vm->program[vm->pc++]);
	}
}

void soft_vm_run_vm_debug(soft_VM *vm)
{
	vm->running = true;

	while (vm->running == true) {
		soft_vm_show_registers(vm);
		soft_vm_decode_instr(vm, vm->program[vm->pc++]);
		soft_vm_show_registers(vm);
		printf("\n");
	}

	printf("--------\n");
}
