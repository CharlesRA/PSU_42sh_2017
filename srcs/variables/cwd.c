/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** cwd special variable
*/

#include <stdio.h>
#include <string.h>
#include "variables.h"
#include "shell.h"

int handle_cwd(shell_t *data, char **envp, variable_t *cwd)
{
	if (cwd == NULL) {
		cwd = malloc(sizeof(*cwd));
		if (cwd == NULL)
			return (EXIT_FAIL);
		cwd->name = strdup("cwd");
		if (cwd->name == NULL)
			return (EXIT_FAIL);
	}
	cwd->value = getcwd(NULL, 0);
	if (cwd->value == NULL) {
		fprintf(stderr, "Error getting current working directory\n");
		return (EXIT_FAIL);
	}
	add_variable(data->variables, cwd);
	return (EXIT_NORMAL);
}
