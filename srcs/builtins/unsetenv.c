/*
** EPITECH PROJECT, 2018
** unsetenv
** File description:
** minishell
*/

#include "shell.h"

char **unset_env(shell_t *new, char **envp)
{
	int i = find_correct_line_env(envp, new->array[1]);

	if (i != -1)
		envp[i][0] = '\0';
	return (envp);
}
