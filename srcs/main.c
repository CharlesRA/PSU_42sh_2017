/*
** EPITECH PROJECT, 2018
** main
** File description:
** minishell
*/

#include "shell.h"
#include <stdlib.h>

int main(int ac, char **av, char **envp)
{
	shell_t tcsh;

	tcsh.return_value = 0;
	tcsh.alias = malloc(sizeof(alias_t));
	if (tcsh.alias == NULL)
		return (84);
	tcsh.alias[0].shortcut = NULL;
	loop(&tcsh, envp);
	return (0);
}
