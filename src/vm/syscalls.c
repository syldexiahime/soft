#include "vm/syscalls.h"
#include "utils/helpers.h"


void soft_vm_syscall(struct soft_vm * vm, struct soft_instr instr)
{
	switch (instr.imm) {

		case soft_sys_open: {
			char*  buffer = (char *) vm->r[0].dw;
			int    oflags = (int)    vm->r[1].w;
			mode_t mode   = (mode_t) vm->r[2].w;

			vm->r[instr.dst].w = bitwise_cast(word_t, ssize_t, open(buffer, oflags, mode));
			break;
		}

		case soft_sys_read: {
			int     fildes = (int)    vm->r[0].w;
			void *  buffer = (void *) vm->r[1].dw;
			size_t  nbytes = (size_t) vm->r[2].w;

			vm->r[instr.dst].w = bitwise_cast(word_t, ssize_t, read(fildes, buffer, nbytes));
			break;
		}

		case soft_sys_write: {
			int     fildes = (int)    vm->r[0].w;
			void *  buffer = (void *) vm->r[1].dw;
			size_t  nbytes = (size_t) vm->r[2].w;

			vm->r[instr.dst].w = bitwise_cast(word_t, ssize_t, write(fildes, buffer, nbytes));
			break;
		}

		case soft_sys_malloc: {
			size_t nbytes = (size_t) vm->r[0].w;

			// vm->r[instr.dst] = sval_from_pointer(malloc(nbytes));
			break;
		}

		case soft_sys_free: {
			void * ptr = (void *) vm->r[0].dw;

			free(ptr);
			break;
		}

	}
}
