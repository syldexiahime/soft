#include "vm/syscalls.h"


void soft_vm_syscall(struct soft_vm * vm, struct soft_instr instr)
{
	switch (instr.imm.soft_int32) {

		case soft_sys_open: {
			char*  buffer = (char*)  vm->r[0].soft_ptr;
			int    oflags =          vm->r[1].soft_int32;
			mode_t mode   = (mode_t) vm->r[2].soft_int32;

			vm->r[instr.dst].soft_int32 = open(buffer, oflags, mode);
			break;
		}

		case soft_sys_read: {
			int    fildes =          vm->r[0].soft_int32;
			void*  buffer =          vm->r[1].soft_ptr;
			size_t nbytes = (size_t) vm->r[2].soft_int32;

			vm->r[instr.dst].soft_int32 = read(fildes, buffer, nbytes);
			break;
		}

		case soft_sys_write: {
			int    fildes =          vm->r[0].soft_int32;
			void*  buffer =          vm->r[1].soft_ptr;
			size_t nbytes = (size_t) vm->r[2].soft_int32;

			vm->r[instr.dst].soft_int32 = write(fildes, buffer, nbytes);
			break;
		}

		case soft_sys_malloc: {
			size_t nbytes = (size_t) vm->r[0].soft_int32;

			vm->r[instr.dst].soft_ptr = malloc(nbytes);
			break;
		}

		case soft_sys_free: {
			void* ptr = vm->r[0].soft_ptr;

			free(ptr);
			break;
		}

	}
}
