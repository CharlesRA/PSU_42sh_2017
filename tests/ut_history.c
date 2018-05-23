/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unit test for history replacement with "!!"
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "linked_list.h"
#include "shell.h"

char *history_handling(circular_dll_t *, char *);

void redirect_all_std(void)
{
	cr_redirect_stdout();
	cr_redirect_stderr();
}

Test(history, simple_replace01, .init = redirect_all_std)
{
	circular_dll_t *list = create_list();
	char *str = strdup("!!\n");
	char *prev_command = strdup("ok\n");

	add_back(list, prev_command);
	str = history_handling(list, str);
	cr_assert_stdout_eq_str("ok\n");
	cr_assert_str_eq(str, "ok\n");
}

Test(history, simple_replace02, .init = redirect_all_std)
{
	circular_dll_t *list = create_list();
	char *str = strdup("!!!!\n");
	char *prev_command = strdup("ok\n");

	add_back(list, prev_command);
	str = history_handling(list, str);
	cr_assert_stdout_eq_str("okok\n");
	cr_assert_str_eq(str, "okok\n");
}

Test(history, null_history, .init = redirect_all_std)
{
	circular_dll_t *list = create_list();
	char *str = strdup("!!\n");

	str = history_handling(list, str);
	cr_assert_stdout_eq_str("exit\n");
	cr_assert_str_eq(str, "exit\n");
}

Test(history, simple_replace03)
{
	circular_dll_t *list = create_list();
	char *str = strdup("!! !!\n");
	char *prev_command = strdup("ok\n");

	add_back(list, prev_command);
	str = history_handling(list, str);
	cr_assert_str_eq(str, "ok ok\n");
	add_back(list, strdup(str));
	str = strdup("!! !!\n");
	str = history_handling(list, str);
	cr_assert_str_eq(str, "ok ok ok ok\n");
}
