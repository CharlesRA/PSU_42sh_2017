/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** handle special variables case
*/

#include <string.h>
#include "variables.h"
#include "shell.h"
#include "define.h"

static int choose_variable(shell_t *new, char **envp, variable_t *actual_var,
			int i)
{
	if (strcmp(special_variables[i].name, actual_var->name) == 0)
		return (special_variables[i].function(new, envp, actual_var));
	return (EXIT_NORMAL);
}

int handle_special_var(shell_t *new, char **envp)
{
	int is_cwd = 0;
	circular_dll_t *temp = new->variables->go_to[NEXT];
	variable_t *actual_var;

	for (; temp != new->variables; temp = temp->go_to[NEXT]) {
		actual_var = (variable_t *)temp->data;
		for (int i = 0; special_variables[i].name != NULL; i++) {
			choose_variable(new, envp, actual_var, i);
		}
		if (strcmp(actual_var->name, "cwd") == 0)
			is_cwd = 1;
	}
	if (is_cwd == 0) {
		if (handle_cwd(new, envp, NULL) == EXIT_FAIL)
			return (EXIT_FAIL);
	}
}
