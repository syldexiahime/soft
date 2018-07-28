/**
 * Helpers
 * */
#define _SOFT_VM_GET_INSTR_VALUE(vm, instr) (instr.src == noop ? instr.imm : vm->r[instr.src])

/**
 * Load instructions
 * */
#define _SOFT_VM_LOAD(vm, instr, soft_type_t, _) \
	vm->r[instr.dst].soft_type_t = instr.imm.soft_type_t

/**
 * Arithmetic instructions
 * */
#define _SOFT_VM_ARITHMETIC(vm, instr, soft_type_t, op) \
	vm->r[instr.dst].soft_type_t op##= _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t

/**
 * Equality instructions
 * */
#define _SOFT_VM_COMPARISON(vm, instr, soft_type_t, op) \
	vm->zf = vm->r[instr.dst].soft_type_t op _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_type_t

/**
 * Binary/Bitwise instructions
 * */
#define _SOFT_VM_BINARY(vm, instr, _, op) \
	vm->r[instr.dst].soft_int32 op##= _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_int32

#define _SOFT_VM_BWNOT(vm, instr, _, __) \
	vm->r[instr.dst].soft_int32 = ~ _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_int32

/**
 * Typecast instructions
 * */
#define _SOFT_VM_CAST_INT32(vm, instr, soft_type_t, _) \
	vm->r[instr.dst].soft_int32 = (soft_int32_t) vm->r[instr.src].soft_type_t

#define _SOFT_VM_CAST_FLOAT(vm, instr, soft_type_t, _) \
	vm->r[instr.dst].soft_int32 = (soft_float_t) vm->r[instr.src].soft_type_t

/**
 * Jump instructions
 * */
#define _SOFT_VM_JMP(vm, instr) \
	vm->pc = _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_ptr32; return

#define _SOFT_VM_JMPZ(vm, instr) \
	if (vm->zf == true) { vm->pc = _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_ptr32; return; }

#define _SOFT_VM_JMPNZ(vm, instr) \
	if (vm->zf == false) { vm->pc = _SOFT_VM_GET_INSTR_VALUE(vm, instr).soft_ptr32; return; }

/**
 * Execution macros
 * */
#define SOFT_VM_EXECUTE_JMP_INSTR(vm, instr, operation) \
		_SOFT_VM_##operation(vm, instr); break; \

#define SOFT_VM_EXECUTE_INSTR(vm, instr, operation, op) \
	switch(instr.datatype) { \
		case soft_ptr32: _SOFT_VM_##operation(vm, instr, soft_ptr32, op); break; \
		case soft_int32: _SOFT_VM_##operation(vm, instr, soft_int32, op); break; \
		case soft_float: _SOFT_VM_##operation(vm, instr, soft_float, op); break; \
\
		default: assert(false); break; \
	}
