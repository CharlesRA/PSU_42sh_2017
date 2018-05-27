/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** alias.c
*/

#include <string.h>
#include "shell.h"

static void find_occurence_alias(shell_t *data, circular_dll_t *temp, int i)
{
	if (strcmp(data->different_command[0][i]
	, ((alias_t *) temp->data)->alias) == 0)
		data->different_command[0][i]
	= strdup(((alias_t *) temp->data)->value);
}

void replace_alias(shell_t *data)
{
	circular_dll_t *temp = NULL;

	for (int i = 0 ; data->different_command[0][i] ; i++) {
		temp = data->alias->go_to[NEXT];
		while (temp != data->alias) {
			find_occurence_alias(data, temp, i);
			temp = temp->go_to[NEXT];
		}
	}
}

static void *add_alias_to_list(circular_dll_t *list, char *shortcut, char *value)
{
	alias_t *alias = malloc(sizeof(alias_t));

	if (alias == NULL)
		return (NULL);
	alias->value = strdup(value);
	alias->alias = strdup(shortcut);
	add_back(list, alias);
	return (list);
}

char **create_alias(shell_t *data, char **env)
{
	if (my_array_len(data->different_command[0]) == 3
	&& add_alias_to_list(data->alias, data->different_command[0][1]
	, data->different_command[0][2]) == NULL)
		return (NULL);
	return (env);
}
