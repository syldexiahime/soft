#include "vm/soft-vm.h"

enum {
	soft_sys_open,
	soft_sys_read,
	soft_sys_write,
	soft_sys_malloc,
	soft_sys_free
} _SOFT_SYSCALLS;

void soft_vm_syscall(soft_VM *vm, soft_instr instr);
