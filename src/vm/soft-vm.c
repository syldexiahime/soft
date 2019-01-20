#include "vm/soft-vm.h"

enum SOFT_VM_REGISTERS _regs;

void soft_vm_init_vm(struct soft_vm * vm)
{
	for (int i = 0; i < SOFT_VM_NUM_REGS; i ++) {
		vm->r[i].hw = 0;
	}
	vm->zf = 0;
	vm->sf = 0;
	vm->ip = 0;
}

void soft_vm_load_program(struct soft_vm * vm, struct soft_program * program)
{
	soft_vm_init_vm(vm);

	vm->ds = program->datastore;
	vm->instructions = program->instructions;
	vm->ip = vm->instructions;
}

void soft_vm_run_vm(struct soft_vm * vm)
{

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

	struct soft_instr instr;

	goto start; // Don't increment ip on first run

	increment_pc: ;

		vm->ip++;

	start: ;

		instr = *vm->ip;

#ifdef SOFT_VM_USE_COMPUTED_GOTO

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

		softvm_op(loadi)
			vm->r[instr.dst] = *((union vm_register *) sval_to_pointer(bitwise_cast(sval_t, union vm_register, vm->r[instr.src])));
			goto increment_pc;

		softvm_op(load_dw)
			memcpy(&vm->r[instr.dst], &vm->ds[instr.imm], sizeof(doubleword_t));
			goto increment_pc;

		softvm_op(load_w)
			memcpy(&vm->r[instr.dst], &vm->ds[instr.imm], sizeof(word_t));
			goto increment_pc;

		softvm_op(store_dw) {
			doubleword_t * ptr = sval_to_pointer(bitwise_cast(sval_t, union vm_register, vm->r[instr.dst]));
			*ptr = vm->r[instr.src].dw;
			goto increment_pc;
		}

		softvm_op(store_w) {
			doubleword_t * ptr = sval_to_pointer(bitwise_cast(sval_t, union vm_register, vm->r[instr.dst]));
			*ptr = vm->r[instr.src].w;
			goto increment_pc;
		}

		softvm_op(mov)
			vm->r[instr.dst] = vm->r[instr.imm];
			goto increment_pc;

		softvm_op(movi)
			vm->r[instr.dst].dw = instr.imm;
			goto increment_pc;

		softvm_op(push_dw) {
			doubleword_t * ptr = bitwise_cast(doubleword_t *, doubleword_t, vm->r[soft_rsp].dw);
			*ptr               = vm->r[instr.src].dw;
			vm->r[soft_rsp].dw = bitwise_cast(doubleword_t, doubleword_t *, --ptr);
			goto increment_pc;
		}

		softvm_op(pop_dw) {
			doubleword_t * ptr  = bitwise_cast(doubleword_t *, doubleword_t, vm->r[soft_rsp].dw) + 1;
			vm->r[instr.dst].dw = *ptr;
			vm->r[soft_rsp].dw  = bitwise_cast(doubleword_t, doubleword_t *, ptr);
			goto increment_pc;
		}

		softvm_op(push_w) {
			word_t * ptr       = bitwise_cast(word_t *, doubleword_t, vm->r[soft_rsp].dw);
			*ptr               = vm->r[instr.src].w;
			vm->r[soft_rsp].dw = bitwise_cast(doubleword_t, word_t *, --ptr);
			goto increment_pc;
		}

		softvm_op(pop_w) {
			word_t * ptr       = bitwise_cast(word_t *, doubleword_t, vm->r[soft_rsp].dw + 1);
			vm->r[instr.dst].w = *ptr;
			vm->r[soft_rsp].dw = bitwise_cast(doubleword_t, word_t *, ptr);
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
			// TODO
			goto start;

		softvm_op(jmpz)
			// TODO
			goto start;

		softvm_op(jmpnz)
			// TODO
			goto start;

		softvm_op(castint32)
			// TODO
			goto increment_pc;

		softvm_op(castfloat)
			// TODO
			goto increment_pc;


#ifndef SOFT_VM_USE_COMPUTED_GOTO

	}

#endif

	exit_vm: ;

		return;
}

