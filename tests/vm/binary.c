#include "vm/soft-vm.h"
#include "vm/vm-test.h"

#define SOFT_VM_BINARY_TEST(operation, operator, debug) \
	_SOFT_VM_INSTR_TEST(operation, operator, int32, reg, debug); \
	_SOFT_VM_INSTR_TEST(operation, operator, int32, imm, debug);

SOFT_VM_BINARY_TEST(and, &, false)
SOFT_VM_BINARY_TEST(or,  |, false)
SOFT_VM_BINARY_TEST(xor, ^, false)
SOFT_VM_BINARY_TEST(lshift, <<, false)
SOFT_VM_BINARY_TEST(rshift, >>, false)
// SOFT_VM_BWNOT_TEST(not, ~, false)

