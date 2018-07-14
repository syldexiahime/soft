#include "soft-vm.h"

soft_VM create_vm()
{
	soft_VM vm;
	vm.running = true;
	vm.pc = 0;
	for (int i = 0; i < SOFT_VM_NUM_REGS; i ++) {
		vm.r[i].soft_int32 = 0;
	}

	return vm;
}

soft_instr program[] = {
	// opcode,   datatype,      src,   dest, immediate
	{ soft_load, soft_float_t,  noop,  0x1,  0x00000000004293f5c3 },
	{ soft_load, soft_float_t,  noop,  0x2,  0x000000000041bb3333 },
	{ soft_add,  soft_float_t,  0x1,   0x2,  0x000000000000000000 },
	{ soft_add,  soft_float_t,  noop,  0x1,  0x000000000041bb3333 },
	{ halt,      noop,          noop,  noop, noop }
};

void soft_vm_decode_instr(soft_VM *vm, soft_instr instr)
{
	switch (instr.opcode) {
		case halt: vm->running = false; break;
		case noop: break;

		case soft_load: SOFT_VM_EXECUTE_INSTR(vm, instr, LOAD) break;

		case soft_add: SOFT_VM_EXECUTE_INSTR(vm, instr, ADD); break;
		case soft_sub: SOFT_VM_EXECUTE_INSTR(vm, instr, SUB); break;
		case soft_mul: SOFT_VM_EXECUTE_INSTR(vm, instr, MUL); break;
		case soft_div: SOFT_VM_EXECUTE_INSTR(vm, instr, DIV); break;

		default:
			break;
	}
}

void show_registers(soft_VM *vm)
{
	printf("Instruction: %d\n", vm->pc);
	printf("R: ");
	for (int i = 0; i < SOFT_VM_NUM_REGS; i++) {
		printf("0x%04X ", vm->r[i].soft_int32);
		printf("(%f) ", vm->r[i].soft_float);
	}
	printf("\n");
}

void run_vm()
{
	soft_VM vm;
	vm = create_vm();

	while (vm.running == true) {
		show_registers(&vm);
		soft_vm_decode_instr(&vm, program[vm.pc++]);
		show_registers(&vm);
		printf("\n");
	}

	printf("--------\n");

}
