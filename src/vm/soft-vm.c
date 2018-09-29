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

#define make_jump_table(soft_type_t) \
{ \
	&&halt, \
	&&noop, \
	&&syscall, \
	&&soft_type_t##_load, \
	&&soft_type_t##_movreg, \
	&&soft_type_t##_movaddr, \
	&&soft_type_t##_add, \
	&&soft_type_t##_sub, \
	&&soft_type_t##_mul, \
	&&soft_type_t##_div, \
	&&soft_type_t##_eq, \
	&&soft_type_t##_gt, \
	&&soft_type_t##_lt, \
	&&soft_type_t##_gteq, \
	&&soft_type_t##_lteq, \
	&&soft_type_t##_and, \
	&&soft_type_t##_or, \
	&&soft_type_t##_xor, \
	&&soft_type_t##_lshift, \
	&&soft_type_t##_rshift, \
	&&soft_type_t##_not, \
	&&jmp, \
	&&jmpz, \
	&&jmpnz, \
	&&soft_type_t##_castint32, \
	&&soft_type_t##_castfloat \
}

#define make_jump_labels(soft_type_t) \
	soft_type_t##_load:      soft_vm_load(soft_type_t);           goto end; \
	soft_type_t##_movreg:    soft_vm_mov_reg(soft_type_t);        goto end; \
	soft_type_t##_movaddr:   soft_vm_mov_addr(soft_type_t);       goto end; \
	soft_type_t##_add:       soft_vm_arithmetic(soft_type_t, +);  goto end; \
	soft_type_t##_sub:       soft_vm_arithmetic(soft_type_t, -);  goto end; \
	soft_type_t##_mul:       soft_vm_arithmetic(soft_type_t, *);  goto end; \
	soft_type_t##_div:       soft_vm_arithmetic(soft_type_t, /);  goto end; \
	soft_type_t##_and:       soft_vm_binary(&);                   goto end; \
	soft_type_t##_or:        soft_vm_binary(|);                   goto end; \
	soft_type_t##_xor:       soft_vm_binary(^);                   goto end; \
	soft_type_t##_lshift:    soft_vm_binary(<<);                  goto end; \
	soft_type_t##_rshift:    soft_vm_binary(>>);                  goto end; \
	soft_type_t##_not:       soft_vm_not();                       goto end; \
	soft_type_t##_eq:        soft_vm_comparison(soft_type_t, ==); goto end; \
	soft_type_t##_gt:        soft_vm_comparison(soft_type_t, >);  goto end; \
	soft_type_t##_lt:        soft_vm_comparison(soft_type_t, <);  goto end; \
	soft_type_t##_gteq:      soft_vm_comparison(soft_type_t, >=); goto end; \
	soft_type_t##_lteq:      soft_vm_comparison(soft_type_t, <=); goto end; \
	soft_type_t##_castint32: soft_vm_cast_int32(soft_type_t);     goto end; \
	soft_type_t##_castfloat: soft_vm_cast_float(soft_type_t);     goto end;

static void soft_vm_decode_instr(struct soft_vm * vm, struct soft_instr instr)
{
	static void * jump_table[][num_soft_instrs] = {
		make_jump_table(soft_ptr),
		make_jump_table(soft_int32),
		make_jump_table(soft_float),
	};

	goto * jump_table[instr.datatype][instr.opcode];

	invalid:
	// TODO possibly add some error reporting or something here?
	goto end;

	halt:               vm->running = false;              goto end;
	noop:                                                 goto end;
	syscall:            soft_vm_syscall(vm, instr);       goto end;
	jmp:                soft_vm_jmp();                    goto end;
	jmpz:               soft_vm_jmpz();                   goto end;
	jmpnz:              soft_vm_jmpnz();                  goto end;

	soft_ptr_load:      soft_vm_load(soft_ptr);           goto end;
	soft_ptr_movreg:    soft_vm_mov_reg(soft_ptr);        goto end;
	soft_ptr_movaddr:   soft_vm_mov_addr(soft_ptr);       goto end;
	soft_ptr_add:       soft_vm_ptr_arithmetic(+);        goto end;
	soft_ptr_sub:       soft_vm_ptr_arithmetic(-);        goto end;
	soft_ptr_eq:        soft_vm_comparison(soft_ptr, ==); goto end;
	soft_ptr_gt:        soft_vm_comparison(soft_ptr, >);  goto end;
	soft_ptr_lt:        soft_vm_comparison(soft_ptr, <);  goto end;
	soft_ptr_gteq:      soft_vm_comparison(soft_ptr, >=); goto end;
	soft_ptr_lteq:      soft_vm_comparison(soft_ptr, <=); goto end;
	soft_ptr_castint32: soft_vm_cast_int32(soft_ptr);     goto end;
	soft_ptr_mul:                                         goto invalid;
	soft_ptr_div:                                         goto invalid;
	soft_ptr_and:                                         goto invalid;
	soft_ptr_or:                                          goto invalid;
	soft_ptr_xor:                                         goto invalid;
	soft_ptr_lshift:                                      goto invalid;
	soft_ptr_rshift:                                      goto invalid;
	soft_ptr_not:                                         goto invalid;
	soft_ptr_castfloat:                                   goto invalid;

	make_jump_labels(soft_int32);
	make_jump_labels(soft_float);

	increment_pc:
	end: vm->pc++;
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
