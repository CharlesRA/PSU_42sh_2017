/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** set builtin
*/

#include <string.h>
#include <stdlib.h>
#include "linked_list.h"
#include "variables.h"

static void new_var(circular_dll_t *variables, variable_t *new_variable)
{
	circular_dll_t *temp = variables->go_to[NEXT];
	variable_t *actual = (variable_t *) temp->data;

	for (; temp != variables; temp = temp->go_to[NEXT]) {
		actual = (variable_t *)temp->data;
		if (strcmp(actual->name, new_variable->name) > 0) {
			add_back(temp, new_variable);
			break;
		}
		if (strcmp(actual->name, new_variable->name) == 0) {
			actual->value = new_variable->value;
			break;
		}
	}
	if (temp == variables) {
		add_back(temp, new_variable);
		return;
	}
}

void add_variable(circular_dll_t *variables, variable_t *new_variable)
{
	variable_t *copy = malloc(sizeof(*copy));

	if (copy == NULL || new_variable->name == NULL ||
	new_variable->value == NULL)
		return;
	copy->name = new_variable->name;
	copy->value = new_variable->value;
	if (copy->name == NULL || copy->value == NULL)
		return;
	new_var(variables, copy);
}

variable_t *set_new_variable(variable_t *new_variable, char *value)
{
	new_variable->value = strdup(value == NULL ? "\0" : value);
	if (new_variable->value == NULL)
		return (NULL);
	return (new_variable);
}

char **set_all_variable(char **variables, shell_t *data,
			variable_t *new_variable, char **envp)
{
	for (int i = 1 ; variables[i] != NULL ; i++) {
		new_variable->name = dup_to_char(variables[i], '=');
		if (check_invalid(new_variable->name) == 1) {
			data->return_value = 1;
			return (envp);
		}
		if (strstr(variables[i], "=") == NULL && variables[i + 1]
		!= NULL && strcmp(variables[i + 1], "=") == 0) {
			i += 2;
			new_variable = set_new_variable(new_variable,
							variables[i]);
		} else if (strstr(variables[i], "=") != NULL)
			new_variable = set_new_variable(new_variable,
						strstr(variables[i], "=") + 1);
		add_variable(data->variables, new_variable);
	}
}
