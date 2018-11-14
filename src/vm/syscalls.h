#ifndef _SOFT_VM_SYSCALLS_H
#define _SOFT_VM_SYSCALLS_H

#include "vm/soft-vm.h"
#include "vm/sval.h"
#include "vm/instructions.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
 
/* Not technically required, but needed on some UNIX distributions */
#include <sys/types.h>
#include <sys/stat.h>

enum soft_syscalls {
	soft_sys_open,
	soft_sys_read,
	soft_sys_write,
	soft_sys_malloc,
	soft_sys_free
};

struct soft_vm;

void soft_vm_syscall(struct soft_vm * vm, struct soft_instr instr);

#endif // _SOFT_VM_SYSCALLS_H
