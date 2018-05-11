/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** alias.c
*/

#include "shell.h"
#include "str.h"
#include <string.h>

char *change_command_with_alias(shell_t *tcsh, int i, int j)
{
	if (strcmp(tcsh->different_command[0][i], tcsh->alias[j].shortcut) == 0)
		tcsh->different_command[0][i] = my_strdup(tcsh->alias[j].value);
		if (tcsh->different_command[0][i] == NULL)
			return (NULL);
}

char *check_alias(shell_t *tcsh)
{
	for (int i = 0; tcsh->different_command[0][i] != NULL; i++) {
		for (int j = 0; tcsh->alias[j].shortcut != NULL; j++) {
			if (change_command_with_alias(tcsh, i , j) == NULL)
				return (NULL);
		}
	}
}

int check_alias_already_exist(shell_t *tcsh, int i)
{
	int j = 0;

	for (; tcsh->alias[j].shortcut != NULL; j++) {
		if (strcmp(tcsh->alias[j].shortcut
		, tcsh->different_command[0][i]) == 0)
			break;
	}
	return (j);
}

int create_alias(int *i, int j, int len, shell_t *tcsh)
{
	if (tcsh->different_command[0][*i + 1] != NULL) {
		tcsh->alias[j].shortcut =
		strdup(tcsh->different_command[0][*i]);
		*i += 1;
		tcsh->alias[j].value = strdup(tcsh->different_command[0][*i]);
	}
	return (0);
}

char **parsing_alias(shell_t *tcsh, char **envp)
{
	static size_t len = 0;
	int j = 0;

	for (int i = 1; tcsh->different_command[0][i] != NULL; i++) {
		j = check_alias_already_exist(tcsh, i);
		create_alias(&i, j, len, tcsh);
		if (j == len) {
			len += 1;
			tcsh->alias = realloc(tcsh->alias
			, sizeof(alias_t) * (len + 1));
		}
	}
	if (tcsh->alias == NULL)
		return (NULL);
	tcsh->alias[len].shortcut = NULL;
}
