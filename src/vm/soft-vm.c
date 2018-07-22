#include <assert.h>
#include "soft-vm.h"

#define _SOFT_VM_GET_INSTR_VALUE(vm, instr) (instr.src == noop ? instr.imm : vm->r[instr.src])

#define _SOFT_VM_LOAD(vm, instr, soft_type_t, _) \
	vm->r[instr.dst].soft_type_t = instr.imm.soft_type_t

#define _SOFT_VM_ARITHMETIC(vm, instr, soft_type_t, op) \
	vm->r[instr.dst].soft_type_t op##= _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t

#define _SOFT_VM_COMPARISON(vm, instr, soft_type_t, op) \
	vm->zf = vm->r[instr.dst].soft_type_t op _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t

#define _SOFT_VM_BINARY(vm, instr, _, op) \
	vm->r[instr.dst].soft_int32 op##= _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_int32

#define _SOFT_VM_BWNOT(vm, instr, _, __) \
	vm->r[instr.dst].soft_int32 = ~ _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_int32

#define _SOFT_VM_JMP(vm, instr) \
	vm->pc = _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_ptr32; return

#define _SOFT_VM_JMPZ(vm, instr) \
	if (vm->zf == true) { vm->pc = _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_ptr32; return; }

#define _SOFT_VM_JMPNZ(vm, instr) \
	if (vm->zf == false) { vm->pc = _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_ptr32; return; }

#define SOFT_VM_EXECUTE_JMP_INSTR(vm, instr, operation) \
		_SOFT_VM_##operation(vm, instr); break; \

#define SOFT_VM_EXECUTE_INSTR(vm, instr, operation, op) \
	switch(instr.datatype) { \
		case soft_ptr32_t: _SOFT_VM_##operation(vm, instr, soft_ptr32, op); break; \
		case soft_int32_t: _SOFT_VM_##operation(vm, instr, soft_int32, op); break; \
		case soft_float_t: _SOFT_VM_##operation(vm, instr, soft_float, op); break; \
\
		default: assert(false); break; \
	}

static void soft_vm_decode_instr(soft_VM *vm, soft_instr instr);
static void soft_vm_show_registers(soft_VM *vm);

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

static void soft_vm_decode_instr(soft_VM *vm, soft_instr instr)
{
	switch (instr.opcode) {
		case halt: vm->running = false; break;
		case noop: break;

		case soft_instr_load:   SOFT_VM_EXECUTE_INSTR(vm, instr, LOAD,)           break;

		case soft_instr_add:    SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, +);  break;
		case soft_instr_sub:    SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, -);  break;
		case soft_instr_mul:    SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, *);  break;
		case soft_instr_div:    SOFT_VM_EXECUTE_INSTR(vm, instr, ARITHMETIC, /);  break;

		case soft_instr_eq:     SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, ==); break;
		case soft_instr_gt:     SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON,  >); break;
		case soft_instr_lt:     SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON,  <); break;
		case soft_instr_gteq:   SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, >=); break;
		case soft_instr_lteq:   SOFT_VM_EXECUTE_INSTR(vm, instr, COMPARISON, <=); break;

		case soft_instr_and:    SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY,  &);     break;
		case soft_instr_or:     SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY,  |);     break;
		case soft_instr_xor:    SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY,  ^);     break;
		case soft_instr_lshift: SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY, <<);     break;
		case soft_instr_rshift: SOFT_VM_EXECUTE_INSTR(vm, instr, BINARY, >>);     break;
		case soft_instr_not:    SOFT_VM_EXECUTE_INSTR(vm, instr, BWNOT,);         break;

		case soft_instr_jmp:    SOFT_VM_EXECUTE_JMP_INSTR(vm, instr, JMP);       break;
		case soft_instr_jmpz:   SOFT_VM_EXECUTE_JMP_INSTR(vm, instr, JMPZ);      break;
		case soft_instr_jmpnz:  SOFT_VM_EXECUTE_JMP_INSTR(vm, instr, JMPNZ);     break;

		default: assert(false); break;
	}
	vm->pc++;
}

static void soft_vm_show_registers(soft_VM *vm)
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
		soft_vm_decode_instr(vm, vm->program[vm->pc]);
	}
}

void soft_vm_run_vm_debug(soft_VM *vm)
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
