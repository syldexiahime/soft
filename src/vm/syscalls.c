#include "vm/syscalls.h"


void soft_vm_syscall(struct soft_vm * vm, struct soft_instr instr)
{
	switch (instr.imm) {

		case soft_sys_open: {
			char*  buffer = (char *)  sval_to_pointer(vm->r[0]);
			int    oflags =          vm->r[1].as_int;
			mode_t mode   = (mode_t) vm->r[2].as_int;

			vm->r[instr.dst].as_int = open(buffer, oflags, mode);
			break;
		}

		case soft_sys_read: {
			int     fildes =          vm->r[0].as_int;
			void *  buffer =          sval_to_pointer(vm->r[1]);
			size_t  nbytes = (size_t) vm->r[2].as_int;

			vm->r[instr.dst].as_int = read(fildes, buffer, nbytes);
			break;
		}

		case soft_sys_write: {
			int     fildes =          vm->r[0].as_int;
			void *  buffer =          sval_to_pointer(vm->r[1]);
			size_t  nbytes = (size_t) vm->r[2].as_int;

			vm->r[instr.dst].as_int = write(fildes, buffer, nbytes);
			break;
		}

		case soft_sys_malloc: {
			size_t nbytes = (size_t) vm->r[0].as_int;

			// vm->r[instr.dst] = sval_from_pointer(malloc(nbytes));
			break;
		}

		case soft_sys_free: {
			void * ptr = sval_to_pointer(vm->r[0]);

			free(ptr);
			break;
		}

	}
}
