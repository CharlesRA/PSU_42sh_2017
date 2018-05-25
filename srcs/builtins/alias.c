/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** alias.c
*/

#include "linked_list.h"
#include "alias.h"
#include "shell.h"
#include "str.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void find_occurence_alias(shell_t *tcsh, circular_dll_t *temp, int i)
{
	if (strcmp(tcsh->different_command[0][i]
	, ((alias_t *)temp->data)->alias) == 0)
		tcsh->different_command[0][i]
	= strdup(((alias_t *)temp->data)->value);
}

void replace_alias(shell_t *tcsh)
{
	circular_dll_t *temp = NULL;

	for (int i = 0 ; tcsh->different_command[0][i] ; i++) {
		temp = tcsh->alias->go_to[NEXT];
		while (temp != tcsh->alias) {
			find_occurence_alias(tcsh, temp, i);
			temp = temp->go_to[NEXT];
		}
	}
}

void *add_alias_to_list(circular_dll_t *list, char *shortcut, char *value)
{
	alias_t *alias = malloc(sizeof(alias_t));

	if (alias == NULL)
		return (NULL);
	alias->value = strdup(value);
	alias->alias = strdup(shortcut);
	add_back(list, alias);
	return (list);
}

char **create_alias(shell_t *tcsh, char **env)
{
	if (my_array_len(tcsh->different_command[0]) == 3
	&& add_alias_to_list(tcsh->alias, tcsh->different_command[0][1]
	, tcsh->different_command[0][2]) == NULL)
		return (NULL);
	return (env);
}
