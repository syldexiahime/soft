#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "soft-test.h"
#include "soft.h"
#include "vm/vm-test.h"

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(soft_vm_test_load_int32),
        cmocka_unit_test(soft_vm_test_load_float),

        cmocka_unit_test(soft_vm_test_add_int32_reg),
        cmocka_unit_test(soft_vm_test_sub_int32_reg),
        cmocka_unit_test(soft_vm_test_mul_int32_reg),
        cmocka_unit_test(soft_vm_test_div_int32_reg),
        cmocka_unit_test(soft_vm_test_add_float_reg),
        cmocka_unit_test(soft_vm_test_sub_float_reg),
        cmocka_unit_test(soft_vm_test_mul_float_reg),
        cmocka_unit_test(soft_vm_test_div_float_reg),

        cmocka_unit_test(soft_vm_test_add_int32_imm),
        cmocka_unit_test(soft_vm_test_sub_int32_imm),
        cmocka_unit_test(soft_vm_test_mul_int32_imm),
        cmocka_unit_test(soft_vm_test_div_int32_imm),
        cmocka_unit_test(soft_vm_test_add_float_imm),
        cmocka_unit_test(soft_vm_test_sub_float_imm),
        cmocka_unit_test(soft_vm_test_mul_float_imm),
        cmocka_unit_test(soft_vm_test_div_float_imm),

		cmocka_unit_test(soft_vm_test_eq_reg_int32),

		cmocka_unit_test(soft_vm_test_and_float_reg),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
