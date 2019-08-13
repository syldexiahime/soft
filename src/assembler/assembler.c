#include "assembler/assembler.h"
#include "assembler/tokenizer.h"
#include "utils/charstream.h"
#include "vm/soft-vm.h"

#define X(y) #y,
char * soft_asm_instructions[] = {
	SOFT_INSTRUCTION_SET
};
#undef X

struct soft_asm_assembler * assembler;

struct soft_asm_assembler * soft_asm_assembler_init (char * buffer)
{
	if (!assembler)
		assembler = malloc(sizeof(struct soft_asm_assembler));

	soft_asm_tokenizer_init(buffer);

	struct soft_compiler_warnings * w = malloc(sizeof(struct soft_compiler_warnings));
	w->length = 0;
	w->size   = 8;
	w->warnings_array = malloc(w->size * sizeof(char *));
	assembler->warnings = w;

	return assembler;
}

void soft_asm_assembler_warn (char * filename, char * message)
{
	struct soft_compiler_warnings * w = assembler->warnings;

	if (w->length >= w->size)
		w->warnings_array = (char **) realloc(w->warnings_array, (w->size *= 2) * sizeof(char *));

	w->warnings_array[w->length++] = soft_charstream_warn(filename, message);
}

bool soft_asm_assembler_is_instruction (char * word)
{
	int i;

	for (i = 0; i < num_soft_asm_instrs; i++) {
		if (strcmp(word, soft_asm_instructions[i]) == 0)
			return true;
	}

	if (strcmp(word, "call") == 0)
		return true;

	return false;
}

struct soft_instr * soft_asm_assembler_read_line ()
{
	struct soft_instr * instr;

	uint8_t  opcode;
	uint8_t  src;
	uint8_t  dst;
	uint16_t imm;

	struct soft_asm_token * tok = soft_asm_tokenizer_consume();

	if (tok->type != SOFT_ASM_WORD)
		soft_asm_assembler_warn("filename", "Unexpected token");

	int i;
	bool is_instr = false;
	for (i = 0; i < num_soft_asm_instrs; i++) {
		if (strcmp(tok->val, soft_asm_instructions[i]) == 0) {
			is_instr = true;
			break;
		}
	}

	if (strcmp(word, "call") == 0)
		is_instr = true;

	if (strstr(word, "jmp") != NULL)
		is_instr = true;

	if (!is_instr) {
		// TODO
	}

	opcode = i;
}

void soft_asm_parse_section ()
{
	int section_type = 0;

	struct soft_asm_token * tok = soft_asm_tokenizer_peek();
	while (tok->type == SOFT_ASM_EOL) {
		soft_asm_tokenizer_skip();
		tok = soft_asm_tokenizer_peek();
	}

	if (!(tok->type == SOFT_ASM_SYMBOL && strcmp(tok->val, "[") == 0))
		return soft_asm_assembler_warn("filename", "Unexpected token.");

	printf("type: %d, val: %s\n", tok->type, tok->val);

	tok = soft_asm_tokenizer_consume();
	if (!(tok->type == SOFT_ASM_KEYWORD && strcmp(tok->val, "section") == 0))
		return soft_asm_assembler_warn("filename", "Unexpected token.");

	tok = soft_asm_tokenizer_consume();
	if (!(tok->type == SOFT_ASM_SYMBOL && strcmp(tok->val, ".") == 0))
		return soft_asm_assembler_warn("filename", "Unexpected token.");

	tok = soft_asm_tokenizer_consume();
	if (tok->type == SOFT_ASM_KEYWORD)
		section_type = strcmp(tok->val, "data") ? 1 :
		               strcmp(tok->val, "text") ? 2 :
		               strcmp(tok->val, "bss")  ? 3 : 0;
	else
		return soft_asm_assembler_warn("filename", "Unexpected token.");

	tok = soft_asm_tokenizer_consume();
	if (!(tok->type == SOFT_ASM_SYMBOL && strcmp(tok->val, "]") == 0))
		return soft_asm_assembler_warn("filename", "Unexpected token.");

	while (!soft_asm_tokenizer_eof())
		soft_asm_assembler_read_line();
}

struct soft_program * soft_asm_assemble (char * buffer)
{
	int i = 0;
	int size = 256;
	struct soft_program * prog = malloc(sizeof(struct soft_program));

	soft_asm_assembler_init(buffer);

	// while (!soft_asm_tokenizer_eof()) {
		soft_asm_parse_section();
	// }

	return prog;
}
