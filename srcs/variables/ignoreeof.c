/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** ignore end of file special variable
*/

#include "variables.h"
#include "shell.h"
#include "define.h"

int handle_ignoreeof(shell_t *data, char **envp, variable_t *ignoreeof)
{
	if (ignoreeof->value[0] == '\0') {
		data->is_eof = 1;
	} else
		data->is_eof = 1;
	return (EXIT_NORMAL);
}
