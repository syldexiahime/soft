#include "vm/soft-vm.h"

enum SOFT_VM_REGISTERS _regs;

static void soft_vm_decode_instr(struct soft_vm * vm, struct soft_instr instr);
static void soft_vm_show_registers(struct soft_vm * vm);

void soft_vm_init_vm(struct soft_vm * vm)
{
	for (int i = 0; i < SOFT_VM_NUM_REGS; i ++) {
		vm->r[i].as_bits = 0;
	}
	vm->zf = false;
	vm->ip = NULL;
}

void soft_vm_load_program(struct soft_vm * vm, struct soft_program * program)
{
	vm->ds = program->datastore;
	vm->instructions = program->instructions;
	soft_vm_init_vm(vm);
}

static void soft_vm_show_registers(struct soft_vm * vm)
{
	printf("Instruction: %p\n", vm->ip);
	printf("R: ");
	for (int i = 0; i < SOFT_VM_NUM_REGS; i++) {
		printf("0x%04X ", sval_to_int(vm->r[i]));
		/* printf("(%f) ", vm->r[i]); */
	}
	printf("\n");
}

void soft_vm_run_vm(struct soft_vm * vm)
{
	vm->ip = vm->instructions;

#ifdef SOFT_VM_USE_COMPUTED_GOTO

	#define X(opname) &&label_##opname
	static void * jump_table[num_soft_instrs] = {
		SOFT_INSTRUCTION_SET
	};
	#undef X

	#define softvm_op(opname) label_##opname: ;

#else

	#define softvm_op(opname) case soft_instr_##opname:

#endif

	#define get_sval_from_instr(instr) \
		(!instr.iflag ? vm->r[(uint8_t) instr.imm] : sval_from_bits((uint64_t) instr.imm));

	struct soft_instr instr;
	sval_t * ptr;

	start: ;

		instr = *vm->ip;

#ifdef SOFT_VM_USE_COMPUTED_GOTO

	goto * jump_table[instr.opcode];

#else

	switch (instr.opcode) {

#endif

		softvm_op(halt)
			goto exit_vm;

		softvm_op(noop)
			goto increment_pc;

		softvm_op(syscall)
			soft_vm_syscall(vm, instr);
			goto increment_pc;

		softvm_op(dloadi)
			vm->r[instr.dst] = *((sval_t *) sval_to_pointer(vm->r[instr.src]));
			goto increment_pc;

		softvm_op(dload)
			vm->r[instr.dst] = vm->ds[instr.imm];
			goto increment_pc;

		softvm_op(dstore)
			ptr  = sval_to_pointer(vm->r[instr.dst]);
			*ptr = vm->r[instr.src];
			goto increment_pc;

		softvm_op(dmov)
			vm->r[instr.dst] = vm->r[(uint8_t) instr.imm];
			goto increment_pc;

		softvm_op(dmovi)
			vm->r[instr.dst] = sval_from_int(instr.imm);
			goto increment_pc;

		softvm_op(dpush)
			ptr             = sval_to_pointer(vm->r[soft_rbp]);
			*ptr            = get_sval_from_instr(instr);
			vm->r[soft_rsp] = sval_from_pointer(ptr++);
			goto increment_pc;

		softvm_op(dpop)
			ptr              = sval_to_pointer(vm->r[soft_rbp]);
			vm->r[instr.dst] = *ptr;
			vm->r[soft_rsp]  = sval_from_pointer(ptr--);
			goto increment_pc;

#ifndef SOFT_VM_USE_COMPUTED_GOTO

	}

#endif

	increment_pc:
		vm->ip++;

	goto start;

	exit_vm: ;
	
		return;
}

void soft_vm_run_vm_debug(struct soft_vm * vm)
{
	return;
}
