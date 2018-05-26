/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** declare variables
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "variables.h"
#include "linked_list.h"

static int is_letter(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

static int check_invalid(char *name)
{
	int len = (name == NULL ? 0 : strlen(name));

	if (name == NULL)
		return (1);
	if (name[len - 1] == '$') {
		fprintf(stderr, "Illegal variable name.\n");
		return (1);
	}
	if (is_letter(name[0]) == 0) {
		fprintf(stderr,
			"set: Variable name must begin with a letter\n");
		return (1);
	}
	if (check_invalid_char(name) == 1) {
		fprintf(stderr,
		"set: Variable name must contain alphanumeric characters.\n");
	}
	return (0);
}

static char *dup_to_char(char *str, char c)
{
	int len = 0;

	if (str == NULL)
		return (NULL);
	for ( ; str[len] != c && str[len] ; len++);
	return (strndup(str, len));
}

static void display_variables(circular_dll_t *variables,
			circular_dll_t *history)
{
	circular_dll_t *temp = variables->go_to[NEXT];

	printf("\t\t%s\n", (char *) history->go_to[PREV]->data);
	for ( ; temp != variables ; temp = temp->go_to[NEXT]) {
		printf("%s\t%s\n", ((variable_t *) temp->data)->name,
		((variable_t *) temp->data)->value);
		fflush(stdout);
	}
}

char **declare_variable(shell_t *data, char **envp)
{
	variable_t *new_variable = malloc(sizeof(*new_variable));
	char **copy = data->different_command[0];

	if (new_variable == NULL) {
		data->return_value = 1;
		return (envp);
	}
	if (copy[1] == NULL) {
		display_variables(data->variables, data->history);
		return (envp);
	}
	for (int i = 1 ; copy[i] != NULL ; i++) {
		new_variable->name = dup_to_char(copy[i], '=');
		if (check_invalid(new_variable->name) == 1) {
			data->return_value = 1;
			return (envp);
		}
		if (strstr(copy[i], "=") == NULL && copy[i + 1] != NULL
		&& strcmp(copy[i + 1], "=") == 0) {
			i += 2;
			new_variable = set_new_variable(new_variable,
							copy[i]);
		} else if (strstr(copy[i], "=") != NULL)
			new_variable = set_new_variable(new_variable,
						strstr(copy[i], "=") + 1);
		add_variable(data->variables, new_variable);
	}
	return (envp);
}
