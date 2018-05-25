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

void add_variable(circular_dll_t *variables, variable_t *new_variable)
{
	variable_t *copy = malloc(sizeof(*copy));
	circular_dll_t *temp = variables->go_to[NEXT];
	variable_t *actual = (variable_t *) temp->data;

	if (copy == NULL || new_variable->name == NULL ||
	new_variable->value == NULL)
		return;
	copy->name = new_variable->name;
	copy->value = new_variable->value;
	if (copy->name == NULL || copy->value == NULL)
		return;
	for (; temp != variables; temp = temp->go_to[NEXT]) {
		actual = (variable_t *)temp->data;
		if (strcmp(actual->name, copy->name) > 0) {
			add_back(temp, copy);
			break;
		}
		if (strcmp(actual->name, copy->name) == 0) {
			free(temp->data);
			temp->data = copy;
			break;
		}
	}
	if (temp == variables) {
		add_back(temp, copy);
		return;
	}
}

variable_t *set_new_variable(variable_t *new_variable, char *value)
{
	new_variable->value = strdup(value == NULL ? "\0" : value);
	if (new_variable->value == NULL)
		return (NULL);
	return (new_variable);
}
