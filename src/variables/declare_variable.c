/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** declare variables
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variables.h"

static int check_invalid(char *name)
{
	int len = strlen(name);

	if (name[len - 1] == '$')
		return (1);
	return (0);
}

int declare_variable(circular_dll_t *variables, circular_dll_t *command)
{
	char **setting_variable = NULL;
	variable_t *new_variable;

/* --------------- new undeclared ---------------------
	if (check_invalid(new->different_command[0][1]) == 1) {
		fprintf(stderr, "Illegal variable name.\n");
		return (1);
	}
	if (check_invalid_char(new->different_variable[0][1]) == 1) {
		fprintf(stderr,
			"set: Variable name must begin with a letter\n");
		return (1);
		}*/
	new_variable = malloc(sizeof(*new_variable));
	if (new_variable == NULL)
		return (1);
/* ---------------- variable_set undeclared -----------------
	new_variable->name = strdup(variable_set[0]);
	new_variable->value = strdup(variable_set[1]);
	add_back(variables, new_variable);
	for (int i = 0; variable_set[i] != NULL; i++)
		free(variable_set[i]);
		free(variable_set);*/
	return (0);
}
