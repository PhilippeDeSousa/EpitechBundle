#include  <criterion/criterion.h>
#include "minishell.h"

Test(utils, is_convertnb_ok) {
    cr_assert_eq(convertnb(strdup("45")), 45);
    cr_assert_eq(convertnb(strdup("-45")), -45);
    cr_assert_eq(convertnb(strdup("0")), 0);
}