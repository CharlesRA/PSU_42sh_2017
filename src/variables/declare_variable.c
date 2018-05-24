/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** declare variables
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "variables.h"
#include "linked_list.h"

static int check_invalid(char *name)
{
	if (name == NULL)
		return (1);
	int len = strlen(name);

	if (name[len - 1] == '$') {
		fprintf(stderr, "Illegal variable name.\n");
		return (1);
	}
	if (is_letter(name[0]) == 0) {
		fprintf(stderr,
			"set: Variable name must begin with a letter\n");
		return (1);
	}
	if (is_alphanum(name) == 0) {
		fprintf(stderr,
		"set: Variable name must contain alphanumeric characters.\n");
	}
	return (0);
}

static char *dup_to_char(char const *str, char c)
{
	int len = 0;

	if (str == NULL)
		return (NULL);
	for (; str[len] != c && str[len]; len++);
	if (str[len] == c)
		len--;
	return(strndup(str, len));
}

static void display_variables(circular_dll_t *variables,
			circular_dll_t *history)
{
	circular_dll_t *temp = variables->go_to[NEXT];

	printf("\t\t%s\n", (char *)history->go_to[PREV]->data);
	for (; temp != variables; temp = temp->go_to[NEXT]) {
		printf("%s\t%s\n", ((variable_t *)temp->data)->name,
		((variable_t *)temp->data)->value);
		fflush(stdout);
	}
}

int declare_variable(circular_dll_t *variables, char **command,
		circular_dll_t *history)
{
	variable_t *new_variable = malloc(sizeof(*new_variable));

	if (new_variable == NULL)
		return (1);
	if (command[1] == NULL) {
		display_variables(variables, history);
		return (0);
	}
	for (int i = 0; command[i] != NULL; i++) {
		new_variable->name = dup_to_char(command[i], '=');
		if (check_invalid(new_variable->name) == 1)
			return (1);
		if (strstr(command[i], "=") != NULL
		&& strcmp(command[i], "=") != 0) {
			new_variable = set_new_variable(new_variable, command[i + 1]);
			i++;
		} else if (strcmp(command[i], "=") == 0) {
			new_variable = set_new_variable(new_variable, command[i + 1]);
			i++;
		}
		add_variable(variables, new_variable);
	}
	return (0);
}
