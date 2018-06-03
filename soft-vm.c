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

char program[] = {
	0x02, 0x00, 0x00, 0x64,
	0x02, 0x01, 0x00, 0xc8,
	0x03, 0x02, 0x00, 0x01,
	0x02, 0x03, 0x00, 0x20,
	0x04, 0x00, 0x02, 0x03,
	0x00,
};

int fetch(VM *vm) {
	return program[vm->pc++];
}

Command decode(VM *vm, unsigned char instr) {
	Command cmd;

	cmd.instr = instr;

	switch (cmd.instr) {
		case hlt:
		case nop:
		case ldi:
			cmd.args[0] = fetch(vm);
			cmd.args[1] = (fetch(vm) << 8) | fetch(vm);
			break;
		case add:
		case sub:
			cmd.args[0] = fetch(vm);
			cmd.args[1] = fetch(vm);
			cmd.args[2] = fetch(vm);
			break;
		default:
			break;
	}

	printf("Cmd: %d", cmd.instr);
	for (int i = 0; i < 5; i++) {
		printf(" %d", cmd.args[i]);
	}
	printf("\n");

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
			vm->r[cmd.args[0]] = cmd.args[1];
			break;
		case add:
			vm->r[cmd.args[0]] = vm->r[cmd.args[1]] + vm->r[cmd.args[2]];
			break;
		case sub:
			vm->r[cmd.args[0]] = vm->r[cmd.args[1]] - vm->r[cmd.args[2]];
			break;
		default:
			break;
	}
}

void show_registers(VM *vm) {
	printf("R: ");
	for (int i = 0; i < NUM_REGS; i++) {
		printf("0x%04lX ", vm->r[i]);
		printf("(%ld) ", vm->r[i]);
	}
	printf("\n");
}

int main(int argc, char **argv) {
	VM vm;
	vm = create_vm();

	while (vm.running == 1) {
		execute(&vm, decode(&vm, fetch(&vm)));
		show_registers(&vm);
	}

	printf("--------\n");

	return 0;
}
