#include "vm/soft-vm.h"

enum SOFT_VM_REGISTERS _regs;

void soft_vm_init_vm (struct soft_vm * vm)
{
	for (int i = 0; i < SOFT_VM_NUM_REGS; i++) {
		vm->r[i].qw = 0;
	}
	vm->zf = 0;
	vm->sf = 0;
	vm->ip = 0;
}

void soft_vm_load_program (struct soft_vm * vm, struct soft_program * program)
{
	soft_vm_init_vm(vm);

	vm->ds = program->datastore;
	vm->instructions = program->instructions;
	vm->ip = vm->instructions;
}

void soft_vm_run_vm (struct soft_vm * vm)
{

#if SOFT_VM_USE_COMPUTED_GOTO

#define X(opname) &&label_##opname,
	static void * jump_table[num_soft_instrs] = {
		SOFT_INSTRUCTION_SET
	};
#undef X

#define softvm_op(opname) label_##opname: ;

#else

#define softvm_op(opname) case soft_instr_##opname:

#endif

	struct soft_instr instr;

	goto start; // Don't increment ip on first run

	increment_pc: ;

		vm->ip++;

	start: ;

		instr = *vm->ip;

#if SOFT_VM_USE_COMPUTED_GOTO

	goto * jump_table[instr.opcode];

#else

	switch (instr.opcode) {

#endif

		softvm_op(halt)
			goto exit_vm;

		softvm_op(breakpoint)
			vm->ip++;
			goto exit_vm;

		softvm_op(noop)
			goto increment_pc;

		softvm_op(int)
			soft_vm_syscall(vm, instr);
			goto increment_pc;

		softvm_op(load)
			vm->r[instr.dst].b = *(byte_t *) (vm->r[instr.src].ptr);
			goto increment_pc;

		softvm_op(load_w)
			vm->r[instr.dst].w = *(word_t *) (vm->r[instr.src].ptr);
			goto increment_pc;

		softvm_op(load_dw)
			vm->r[instr.dst].dw = *(doubleword_t *) (vm->r[instr.src].ptr);
			goto increment_pc;

		softvm_op(load_qw)
			vm->r[instr.dst].qw = *(quadword_t *) (vm->r[instr.src].ptr);
			goto increment_pc;

		softvm_op(loadi)
			vm->r[instr.dst].b = *(byte_t *) (vm->ds + instr.imm);
			goto increment_pc;

		softvm_op(loadi_w)
			vm->r[instr.dst].w = *(word_t *) (vm->ds + instr.imm);
			goto increment_pc;

		softvm_op(loadi_dw)
			vm->r[instr.dst].dw = *(doubleword_t *) (vm->ds + instr.imm);
			goto increment_pc;

		softvm_op(loadi_qw)
			vm->r[instr.dst].qw = *(quadword_t *) (vm->ds + instr.imm);
			goto increment_pc;

		softvm_op(store)
			*(byte_t *) vm->r[instr.dst].ptr = vm->r[instr.src].b;
			goto increment_pc;

		softvm_op(store_w)
			*(word_t *) vm->r[instr.dst].ptr = vm->r[instr.src].w;
			goto increment_pc;

		softvm_op(store_dw)
			*(doubleword_t *) vm->r[instr.dst].ptr = vm->r[instr.src].dw;
			goto increment_pc;

		softvm_op(store_qw)
			*(quadword_t *) vm->r[instr.dst].ptr = vm->r[instr.src].qw;
			goto increment_pc;

		softvm_op(storep)
			*(byte_t *) vm->r[instr.dst].ptr = *(byte_t *) vm->r[instr.src].ptr;
			goto increment_pc;

		softvm_op(storep_w)
			*(word_t *) vm->r[instr.dst].ptr = *(word_t *) vm->r[instr.src].ptr;
			goto increment_pc;

		softvm_op(storep_dw)
			*(doubleword_t *) vm->r[instr.dst].ptr = *(doubleword_t *) vm->r[instr.src].ptr;
			goto increment_pc;

		softvm_op(storep_qw)
			*(quadword_t *) vm->r[instr.dst].ptr = *(quadword_t *) vm->r[instr.src].ptr;
			goto increment_pc;

		softvm_op(storemem)
			*(byte_t *) vm->r[instr.dst].ptr = *(byte_t *) (vm->ds + instr.imm);
			goto increment_pc;

		softvm_op(storemem_w)
			*(word_t *) vm->r[instr.dst].ptr = *(word_t *) (vm->ds + instr.imm);
			goto increment_pc;

		softvm_op(storemem_dw)
			*(doubleword_t *) vm->r[instr.dst].ptr = *(doubleword_t *) (vm->ds + instr.imm);
			goto increment_pc;

		softvm_op(storemem_qw)
			*(quadword_t *) vm->r[instr.dst].ptr = *(quadword_t *) (vm->ds + instr.imm);
			goto increment_pc;

		softvm_op(memset)
			*(byte_t *) (vm->ds + instr.imm) = vm->r[instr.src].b;
			goto increment_pc;

		softvm_op(memset_w)
			*(word_t *) (vm->ds + instr.imm) = vm->r[instr.src].w;
			goto increment_pc;

		softvm_op(memset_dw)
			*(doubleword_t *) (vm->ds + instr.imm) = vm->r[instr.src].dw;
			goto increment_pc;

		softvm_op(memset_qw)
			*(quadword_t *) (vm->ds + instr.imm) = vm->r[instr.src].qw;
			goto increment_pc;

		softvm_op(memsetp)
			*(byte_t *) (vm->ds + instr.imm) = *((byte_t *) vm->r[instr.src].ptr);
			goto increment_pc;

		softvm_op(memsetp_w)
			*(word_t *) (vm->ds + instr.imm) = *((word_t *) vm->r[instr.src].ptr);
			goto increment_pc;

		softvm_op(memsetp_dw)
			*(doubleword_t *) (vm->ds + instr.imm) = *((doubleword_t *) vm->r[instr.src].ptr);
			goto increment_pc;

		softvm_op(memsetp_qw)
			*(quadword_t *) (vm->ds + instr.imm) = *((quadword_t *) vm->r[instr.src].ptr);
			goto increment_pc;

		softvm_op(mov)
			vm->r[instr.dst] = vm->r[instr.src];
			goto increment_pc;

		softvm_op(movi)
			vm->r[instr.dst].dw = instr.imm;
			goto increment_pc;

		softvm_op(push) {
			byte_t * ptr        = (byte_t *) vm->r[soft_rsp].ptr;
			*ptr                = vm->r[instr.src].b;
			vm->r[soft_rsp].ptr = --ptr;
			goto increment_pc;
		}

		softvm_op(push_w) {
			word_t * ptr        = (word_t *) vm->r[soft_rsp].ptr;
			*ptr                = vm->r[instr.src].w;
			vm->r[soft_rsp].ptr = --ptr;
			goto increment_pc;
		}

		softvm_op(push_dw) {
			doubleword_t * ptr  = (doubleword_t *) vm->r[soft_rsp].ptr;
			*ptr                = vm->r[instr.src].dw;
			vm->r[soft_rsp].ptr = --ptr;
			goto increment_pc;
		}

		softvm_op(push_qw) {
			quadword_t * ptr    = (quadword_t *) vm->r[soft_rsp].ptr;
			*ptr                = vm->r[instr.src].qw;
			vm->r[soft_rsp].ptr = --ptr;
			goto increment_pc;
		}

		softvm_op(pop) {
			byte_t * ptr        = ((byte_t *) vm->r[soft_rsp].ptr) + 1;
			vm->r[instr.dst].b  = *ptr;
			vm->r[soft_rsp].ptr = ptr;
			goto increment_pc;
		}

		softvm_op(pop_w) {
			word_t * ptr        = ((word_t *) vm->r[soft_rsp].ptr) + 1;
			vm->r[instr.dst].w  = *ptr;
			vm->r[soft_rsp].ptr = ptr;
			goto increment_pc;
		}

		softvm_op(pop_dw) {
			doubleword_t * ptr  = ((doubleword_t *) vm->r[soft_rsp].ptr) + 1;
			vm->r[instr.dst].dw = *ptr;
			vm->r[soft_rsp].ptr = ptr;
			goto increment_pc;
		}

		softvm_op(pop_qw) {
			quadword_t * ptr    = ((quadword_t *) vm->r[soft_rsp].ptr) + 1;
			vm->r[instr.dst].qw = *ptr;
			vm->r[soft_rsp].ptr = ptr;
			goto increment_pc;
		}

		/**
		 * Dynamic Arithmetic
		 * */

		softvm_op(dadd)
			sval_arithmetic(vm->r[instr.dst].sval, vm->r[instr.src].sval, +, vm->r[instr.imm].sval);
			goto increment_pc;

		softvm_op(dsub)
			sval_arithmetic(vm->r[instr.dst].sval, vm->r[instr.src].sval, -, vm->r[instr.imm].sval);
			goto increment_pc;

		softvm_op(dmul)
			sval_arithmetic(vm->r[instr.dst].sval, vm->r[instr.src].sval, *, vm->r[instr.imm].sval);
			goto increment_pc;

		softvm_op(ddiv)
			sval_arithmetic(vm->r[instr.dst].sval, vm->r[instr.src].sval, /, vm->r[instr.imm].sval);
			goto increment_pc;

		softvm_op(daddi)
			sval_arithmetic(vm->r[instr.dst].sval, vm->r[instr.src].sval, +, sval_from_int(instr.imm));
			goto increment_pc;

		softvm_op(dsubi)
			sval_arithmetic(vm->r[instr.dst].sval, vm->r[instr.src].sval, -, sval_from_int(instr.imm));
			goto increment_pc;

		softvm_op(dmuli)
			sval_arithmetic(vm->r[instr.dst].sval, vm->r[instr.src].sval, *, sval_from_int(instr.imm));
			goto increment_pc;

		softvm_op(ddivi)
			sval_arithmetic(vm->r[instr.dst].sval, vm->r[instr.src].sval, /, sval_from_int(instr.imm));
			goto increment_pc;

		softvm_op(dcmp) {
			sval_t res;
			sval_arithmetic(res, vm->r[instr.src].sval, -, vm->r[instr.imm].sval);

			if (sval_is_double(res)) {
				double d = sval_to_double(res);
				vm->zf = d == 0.0;
				vm->sf = d <  0.0;
			}
			else if (sval_is_int(res)) {
				int32_t i = sval_to_int(res);
				vm->zf = i == 0;
				vm->sf = i <  0;
			}
			else {
				vm->zf = 0;
				vm->sf = 0;
			}

			goto increment_pc;
		}

		softvm_op(dand)
			vm->r[instr.dst].sval = sval_from_int(sval_cast_to_int(vm->r[instr.src].sval) & sval_cast_to_int(vm->r[instr.imm].sval));
			goto increment_pc;

		softvm_op(dor)
			vm->r[instr.dst].sval = sval_from_int(sval_cast_to_int(vm->r[instr.src].sval) | sval_cast_to_int(vm->r[instr.imm].sval));
			goto increment_pc;

		softvm_op(dnot)
			vm->r[instr.dst].sval = sval_from_int(~ sval_cast_to_int(vm->r[instr.src].sval));
			goto increment_pc;

		softvm_op(dxor)
			vm->r[instr.dst].sval = sval_from_int(sval_cast_to_int(vm->r[instr.src].sval) ^ sval_cast_to_int(vm->r[instr.imm].sval));
			goto increment_pc;

		softvm_op(dlshift)
			vm->r[instr.dst].sval = sval_from_int(sval_cast_to_int(vm->r[instr.src].sval) << sval_cast_to_int(vm->r[instr.imm].sval));
			goto increment_pc;

		softvm_op(drshift)
			vm->r[instr.dst].sval = sval_from_int(sval_cast_to_int(vm->r[instr.src].sval) >> sval_cast_to_int(vm->r[instr.imm].sval));
			goto increment_pc;

		softvm_op(jmp)
			vm->ip = (struct soft_instr *) vm->r[instr.src].ptr;
			goto start;

		softvm_op(jmpz)
			if (vm->zf)
				vm->ip = (struct soft_instr *) vm->r[instr.src].ptr;
			goto start;

		softvm_op(jmpnz)
			if (!vm->zf)
				vm->ip = (struct soft_instr *) vm->r[instr.src].ptr;
			goto start;

		softvm_op(jmpgt)
			if (!vm->zf && !vm->sf)
				vm->ip = (struct soft_instr *) vm->r[instr.src].ptr;
			goto start;

		softvm_op(jmpgte)
			if (vm->zf || !vm->sf)
				vm->ip = (struct soft_instr *) vm->r[instr.src].ptr;
			goto start;

		softvm_op(jmplt)
			if (!vm->zf && vm->sf)
				vm->ip = (struct soft_instr *) vm->r[instr.src].ptr;
			goto start;

		softvm_op(jmplte)
			if (vm->zf || vm->sf)
				vm->ip = (struct soft_instr *) vm->r[instr.src].ptr;
			goto start;

		softvm_op(castint32)
			// TODO
			goto increment_pc;

		softvm_op(castfloat)
			// TODO
			goto increment_pc;


#if !SOFT_VM_USE_COMPUTED_GOTO

	}

#endif

	exit_vm: ;

		return;
}

