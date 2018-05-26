/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** term special variable handling
*/

#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "shell.h"
#include "define.h"

static int reset_term(char **envp, variable_t *term, int i)
{
	int len_env;
	int len_var;

	if (strcmp(term->value, envp[i] + 5) != 0) {
		len_env = strlen(envp[i] + 5);
		len_var = strlen(term->value);
		if (len_env < len_var) {
			envp[i] = realloc(envp[i],
					sizeof(char) * (len_var + 6));
		}
		envp[i] += 5;
		envp[i] = strcpy(envp[i], term->value);
		envp[i] -= 5;
	}
	return (EXIT_NORMAL);
}

int handle_term(shell_t *new, char **envp, variable_t *term)
{
	int i = find_correct_line_env(envp, "TERM");

	if (i == -1) {
		for (i = 0; envp[i] != NULL; i++);
		envp = realloc(envp, sizeof(char *) * (i + 2));
		if (envp == NULL)
			return (EXIT_FAIL);
		envp[i] = my_strdupcat("TERM=", term->value);
		if (envp[i] == NULL)
			return (EXIT_FAIL);
		envp[i + 1] = NULL;
		return (EXIT_NORMAL);
	} else
		reset_term(envp, term, i);
	return (EXIT_NORMAL);
}
