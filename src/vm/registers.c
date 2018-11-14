#include "vm/registers.h"


#define X(y) #y,
char * soft_vm_registers[] = {
	SOFT_VM_REGISTER_TABLE
};
#undef X

size_t num_soft_vm_registers = sizeof(soft_vm_registers) / sizeof(char *);

