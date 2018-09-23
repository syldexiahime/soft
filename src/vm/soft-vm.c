#include "vm/soft-vm.h"

static void soft_vm_decode_instr(struct soft_vm * vm, struct soft_instr instr);
static void soft_vm_show_registers(struct soft_vm * vm);

void soft_vm_init_vm(struct soft_vm * vm)
{
	vm->running = false;
	vm->pc = 0;
	for (int i = 0; i < SOFT_VM_NUM_REGS; i ++) {
		vm->r[i].soft_int32 = 0;
	}
	vm->zf = false;
}

void soft_vm_load_program(struct soft_vm * vm, struct soft_instr * program)
{
	vm->program = program;
	soft_vm_init_vm(vm);
}

static void soft_vm_decode_instr(struct soft_vm * vm, struct soft_instr instr)
{
	switch (instr.opcode) {
		case halt: vm->running = false; break;
		case noop: break;

		case soft_instr_syscall:   soft_vm_syscall(vm, instr);                       break;

		case soft_instr_load:      SOFT_VM_EXECUTE_INSTR(vm, instr, LOAD,);          break;
		case soft_instr_movreg:    SOFT_VM_EXECUTE_INSTR(vm, instr, MOV_REG,);       break;
		case soft_instr_movaddr:   SOFT_VM_EXECUTE_INSTR(vm, instr, MOV_ADDR,);      break;

		case soft_instr_add:       SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, +);  break;
		case soft_instr_sub:       SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, -);  break;
		case soft_instr_mul:       SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, *);  break;
		case soft_instr_div:       SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, /);  break;

		case soft_instr_eq:        SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, ==); break;
		case soft_instr_gt:        SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON,  >); break;
		case soft_instr_lt:        SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON,  <); break;
		case soft_instr_gteq:      SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, >=); break;
		case soft_instr_lteq:      SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, <=); break;

		case soft_instr_and:       SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY,  &);     break;
		case soft_instr_or:        SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY,  |);     break;
		case soft_instr_xor:       SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY,  ^);     break;
		case soft_instr_lshift:    SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY, <<);     break;
		case soft_instr_rshift:    SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY, >>);     break;
		case soft_instr_not:       SOFT_VM_EXECUTE_INSTR(vm, instr, BWNOT,);         break;

		case soft_instr_jmp:       SOFT_VM_EXECUTE_JMP_INSTR(vm, instr, JMP);        break;
		case soft_instr_jmpz:      SOFT_VM_EXECUTE_JMP_INSTR(vm, instr, JMPZ);       break;
		case soft_instr_jmpnz:     SOFT_VM_EXECUTE_JMP_INSTR(vm, instr, JMPNZ);      break;

		case soft_instr_castint32: SOFT_VM_EXECUTE_INSTR(vm, instr, CAST_INT32,);    break;
		case soft_instr_castfloat: SOFT_VM_EXECUTE_INSTR(vm, instr, CAST_FLOAT,);    break;

		default: assert(false); break;
	}
	vm->pc++;
}

static void soft_vm_show_registers(struct soft_vm * vm)
{
	printf("Instruction: %d\n", vm->pc);
	printf("R: ");
	for (int i = 0; i < SOFT_VM_NUM_REGS; i++) {
		printf("0x%04X ", vm->r[i].soft_int32);
		printf("(%f) ", vm->r[i].soft_float);
	}
	printf("\n");
}

void soft_vm_run_vm(struct soft_vm * vm)
{
	vm->running = true;

	while (vm->running == true) {
		soft_vm_decode_instr(vm, vm->program[vm->pc]);
	}
}

void soft_vm_run_vm_debug(struct soft_vm * vm)
{
	vm->running = true;

	while (vm->running == true) {
		soft_vm_show_registers(vm);
		soft_vm_decode_instr(vm, vm->program[vm->pc]);
		soft_vm_show_registers(vm);
		printf("\n");
	}

	printf("--------\n");
}
