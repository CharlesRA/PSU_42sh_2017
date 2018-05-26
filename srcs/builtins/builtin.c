/*
** EPITECH PROJECT, 2018
** builtin
** File description:
** minishell
*/

#include "shell.h"
#include "bultin.h"

int check_builtin(char *command)
{
	for (int i = 0 ; tab[i].builtin != NULL ; i++)
		if (my_strcmp(command, tab[i].builtin) == 0)
			return (1);
	return (0);
}

char **apply_builtin(const char *command, shell_t *new, char **envp)
{
	char **(*pointeurSurFonction)(shell_t *, char **);

	for (int i = 0 ; tab[i].builtin != NULL ; i++) {
		if (my_strcmp(command, tab[i].builtin) == 0) {
			pointeurSurFonction = tab[i].function;
			envp = pointeurSurFonction(new, envp);
			return (envp);
		}
	}
	return (NULL);
}
