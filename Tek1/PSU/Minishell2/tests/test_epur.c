#include  <criterion/criterion.h>
#include "minishell.h"

Test(utils, is_str_epur) {
    cr_assert_str_eq(epur_str(strdup("Hello\tWorld!")), "Hello World!");
    cr_assert_str_eq(epur_str(strdup("Hello  World!")), "Hello World!");
    cr_assert_str_eq(epur_str(strdup("Hello  \tWorld!")), "Hello World!");
    cr_assert_str_eq(epur_str(strdup("Hello  \tWorld!  ")), "Hello World!");
    cr_assert_str_eq(epur_str(strdup("Hello  \tWorld!  \t\t")), "Hello World!");
}