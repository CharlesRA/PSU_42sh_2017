/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** ignore end of file special variable
*/

#include "variables.h"
#include "shell.h"
#include "define.h"

int handle_ignoreeof(shell_t *tcsh, char **envp, variable_t *ignoreeof)
{
	if (ignoreeof->value[0] == '\0') {
		tcsh->is_eof = 1;
	} else
		tcsh->is_eof = 1;
	return (EXIT_NORMAL);
}
