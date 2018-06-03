#include <stdio.h>

#include "soft-vm.h"

VM create_vm() {
	VM vm;
	vm.running = 1;
	vm.pc = 0;
	for (int i = 0; i < NUM_REGS; i ++) {
		vm.r[i] = 0;
	}

	return vm;
}

int program[] = {
	0x2064,
	0x21c8,
	0x3201,
	0x0000
};

int fetch(VM *vm) {
	return program[vm->pc++];
}

Command decode(int instr) {
	Command cmd;

	cmd.instr = (instr & 0xF000) >> 12;
	cmd.r1 = (instr & 0xF00) >> 8;
	cmd.r2 = (instr & 0xF0) >> 4;
	cmd.r3 = (instr & 0xF);
	cmd.imm = (instr & 0xFF);

	return cmd;
}

void execute(VM *vm, Command cmd) {
	switch (cmd.instr) {
		case hlt:
			vm->running = 0;
			break;
		case nop:
			break;
		case ldi:
			vm->r[cmd.r1] = cmd.imm;
			break;
		case add:
			vm->r[cmd.r1] = vm->r[cmd.r2] + vm->r[cmd.r3];
			break;
		case sub:
			vm->r[cmd.r1] = vm->r[cmd.r2] - vm->r[cmd.r3];
			break;
		default:
			break;
	}
}

void show_registers(VM *vm) {
	printf("R: ");
	for (int i = 0; i < NUM_REGS; i++) {
		printf("%04X ", vm->r[i]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	VM vm;
	vm = create_vm();

	while (vm.running == 1) {
		execute(&vm, decode(fetch(&vm)));
		show_registers(&vm);
	}

	return 0;
}
