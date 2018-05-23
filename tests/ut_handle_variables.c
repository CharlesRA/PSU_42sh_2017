/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** unit test for variable replacement
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "variables.h"
#include "linked_list.h"

Test(replace_variable, easy_replace01)
{
	circular_dll_t *list = create_list();
	char *envp[] = {"TERM=X86", NULL};
	variable_t *new_var = malloc(sizeof(*new_var));
	char *str = strdup("no $ok\n");

	new_var->name = strdup("ok");
	new_var->value = strdup("yes");
	add_back(list, new_var);
	replace_variable(list, envp, str);
	cr_assert_str_eq(str, "no yes\n");
}

Test(replace_variable, easy_replace02)
{
	circular_dll_t *list = create_list();
	char *envp[] = {"TERM=X86", NULL};
	variable_t *new_var = malloc(sizeof(*new_var));
	char *str = strdup("no $TERM\n");

	new_var->name = strdup("ok");
	new_var->value = strdup("yes");
	add_back(list, new_var);
	replace_variable(list, envp, str);
	cr_assert_str_eq(str, "no X86\n");
}

Test(replace_variable, easy_replace03)
{
	circular_dll_t *list = create_list();
	char *envp[] = {"TERM=X86", NULL};
	variable_t *new_var = malloc(sizeof(*new_var));
	char *str = strdup("no $ok\n");

	new_var->name = strdup("ok");
	new_var->value = strdup("le test");
	add_back(list, new_var);
	replace_variable(list, envp, str);
	cr_assert_str_eq(str, "no le test\n");
}
