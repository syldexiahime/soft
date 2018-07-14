#include <stdio.h>
#include <stdint.h>

#include "soft-vm.h"

#define SOFT_GET_INSTR_VALUE(vm, instr) (instr.src == noop ? instr.imm : vm->r[instr.src])

#define SOFT_INSTR(vm, instr, operation) \
switch(instr.datatype) { \
	case soft_int32_t: SOFT_##operation(vm, instr, soft_int32); break; \
	case soft_float_t: SOFT_##operation(vm, instr, soft_float); break; \
}

#define SOFT_LOAD(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t = instr.imm.soft_type_t

#define SOFT_ADD(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t += SOFT_GET_INSTR_VALUE(vm, instr).soft_type_t
#define SOFT_SUB(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t -= SOFT_GET_INSTR_VALUE(vm, instr).soft_type_t
#define SOFT_MUL(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t *= SOFT_GET_INSTR_VALUE(vm, instr).soft_type_t
#define SOFT_DIV(vm, instr, soft_type_t) vm->r[instr.dst].soft_type_t /= SOFT_GET_INSTR_VALUE(vm, instr).soft_type_t

soft_VM create_vm()
{
	soft_VM vm;
	vm.running = 0;
	vm.pc = 0;
	for (int i = 0; i < NUM_REGS; i ++) {
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

void soft_vm_execute_instr(soft_VM *vm, soft_instr instr)
{
	switch (instr.opcode) {
		case halt: vm->running = 1; break;
		case noop: break;

		case soft_load: SOFT_INSTR(vm, instr, LOAD) break;

		case soft_add: SOFT_INSTR(vm, instr, ADD); break;
		case soft_sub: SOFT_INSTR(vm, instr, SUB); break;
		case soft_mul: SOFT_INSTR(vm, instr, MUL); break;
		case soft_div: SOFT_INSTR(vm, instr, DIV); break;

		default:
			break;
	}
}

void show_registers(soft_VM *vm)
{
	printf("Instruction: %d\n", vm->pc);
	printf("R: ");
	for (int i = 0; i < NUM_REGS; i++) {
		printf("0x%04X ", vm->r[i].soft_int32);
		printf("(%f) ", vm->r[i].soft_float);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	soft_VM vm;
	vm = create_vm();

	while (vm.running == 0) {
		show_registers(&vm);
		soft_vm_execute_instr(&vm, program[vm.pc++]);
		show_registers(&vm);
		printf("\n");
	}

	printf("--------\n");

	return 0;
}
