#include "vm/soft-vm.h"
#include "vm/vm-test.h"

#define SOFT_VM_ARITHMETIC_TEST(operation, operator, debug) \
	SOFT_VM_INSTR_TEST(operation, operator, int32, debug) \
	SOFT_VM_INSTR_TEST(operation, operator, float, debug) \

// Build tests using macros. Honestly this is probably a terrible idea.
SOFT_VM_ARITHMETIC_TEST(add, +, false)
SOFT_VM_ARITHMETIC_TEST(sub, -, false)
SOFT_VM_ARITHMETIC_TEST(mul, *, false)
SOFT_VM_ARITHMETIC_TEST(div, /, false)
