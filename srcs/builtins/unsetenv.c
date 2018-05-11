/*
** EPITECH PROJECT, 2018
** unsetenv
** File description:
** minishell
*/

#include "shell.h"

char **unset_env(shell_t *tcsh, char **envp)
{
	int i = -1;

	for (int j = 1; tcsh->different_command[0][j] != NULL; j++) {
		if (tcsh->different_command[0][1] != NULL)
			i = find_correct_line_env(envp, tcsh->different_command[0][j]);
		if (i != -1)
			envp[i][0] = '\0';
	}
	return (envp);
}
