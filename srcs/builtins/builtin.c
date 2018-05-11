/*
** EPITECH PROJECT, 2018
** builtin
** File description:
** minishell
*/

#include "shell.h"
#include "builtins.h"
#include "str.h"

int check_builtin(shell_t *tcsh, char *command)
{
	for (int i = 0; i != 4; i++)
		if (my_strcmp(command, tab[i].builtin) == 0)
			return (1);
	return (0);
}

char **apply_builtin(const char *command, shell_t *tcsh, char **envp)
{
	char **(*pointeurSurFonction)(shell_t *, char **);

	for (int i = 0; i != 4; i++) {
		if (my_strcmp(command, tab[i].builtin) == 0) {
			pointeurSurFonction = tab[i].function;
			envp = pointeurSurFonction(tcsh,envp);
			return (envp);
		}
	}
	return (NULL);
}
