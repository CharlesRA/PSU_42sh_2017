/*
** EPITECH PROJECT, 2018
** print env
** File description:
** minishell
*/

#include "shell.h"
#include "str.h"

char **print_env(shell_t *new, char **envp)
{
	for (int i = 0 ; envp[i] != NULL ; i++) {
		if (my_strlen(envp[i]) != 0) {
			my_putstr(envp[i]);
			my_putchar('\n');
		}
	}
	return (envp);
}
