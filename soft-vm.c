#include <stdio.h>
#include <stdint.h>

#include "soft-vm.h"

soft_VM create_vm() {
	soft_VM vm;
	vm.running = 1;
	vm.pc = 0;
	for (int i = 0; i < NUM_REGS; i ++) {
		vm.r[i].i = 0;
	}

	return vm;
}

soft_instr program[] = {
	{ load_float,    0x00, 0x00, 0x00000000004293f5c3 },
	{ load_float,    0x00, 0x01, 0x000000000041bb3333 },
	{ add_float_reg, 0x00, 0x01, 0x000000000000000000 },
	{ add_float_imm, 0x00, 0x00, 0x000000000041bb3333 }
};

void soft_vm_execute_instr(soft_VM *vm, soft_instr instr) {
	switch (instr.opcode) {
		case halt: vm->running = 0; break;
		case noop: break;

		case load_int:   vm->r[instr.dst].i = instr.imm; break;
		case load_float: vm->r[instr.dst].f = *(float*)&instr.imm; break;

		case add_int_reg: vm->r[instr.dst].i += vm->r[instr.src].i; break;
		case sub_int_reg: vm->r[instr.dst].i -= vm->r[instr.src].i; break;
		case mul_int_reg: vm->r[instr.dst].i *= vm->r[instr.src].i; break;
		case div_int_reg: vm->r[instr.dst].i /= vm->r[instr.src].i; break;
		case add_int_imm: vm->r[instr.dst].i += instr.imm; break;
		case sub_int_imm: vm->r[instr.dst].i -= instr.imm; break;
		case mul_int_imm: vm->r[instr.dst].i *= instr.imm; break;
		case div_int_imm: vm->r[instr.dst].i /= instr.imm; break;

		case add_float_reg: vm->r[instr.dst].f += vm->r[instr.src].f; break;
		case sub_float_reg: vm->r[instr.dst].f -= vm->r[instr.src].f; break;
		case mul_float_reg: vm->r[instr.dst].f *= vm->r[instr.src].f; break;
		case div_float_reg: vm->r[instr.dst].f /= vm->r[instr.src].f; break;
		case add_float_imm: vm->r[instr.dst].f += *(float*)&instr.imm; break;
		case sub_float_imm: vm->r[instr.dst].f -= *(float*)&instr.imm; break;
		case mul_float_imm: vm->r[instr.dst].f *= *(float*)&instr.imm; break;
		case div_float_imm: vm->r[instr.dst].f /= *(float*)&instr.imm; break;

		default:
			break;
	}
}

void show_registers(soft_VM *vm) {
	printf("Instruction: %d\n", vm->pc);
	printf("R: ");
	for (int i = 0; i < NUM_REGS; i++) {
		printf("0x%04f ", vm->r[i].f);
		printf("(%f) ", vm->r[i].f);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	soft_VM vm;
	vm = create_vm();

	while (vm.running == 1) {
		show_registers(&vm);
		soft_vm_execute_instr(&vm, program[vm.pc++]);
		show_registers(&vm);
		printf("\n");
	}

	printf("--------\n");

	return 0;
}
