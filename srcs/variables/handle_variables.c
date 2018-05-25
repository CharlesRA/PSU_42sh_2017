/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** variables and env
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "variables.h"
#include "linked_list.h"

static char *strcpy_no_end_byte(char *dest, char *src)
{
	for (int i = 0; src[i]; i++) {
		dest[i] = src[i];
	}
	return (dest);
}

static char *shift_array(char *array, int shift_size, int offset)
{
	int old_len = strlen(array);
	char stock;

	if (old_len > shift_size) {
		array = strcpy(array, array + (old_len - shift_size));
		array = realloc(array - offset, sizeof(char) * (shift_size + 1));
		array += offset;
	} else if (old_len < shift_size) {
		array = realloc(array - offset, sizeof(char) * (shift_size + 1));
		array += offset;
		array = strcpy(array + (shift_size - old_len), array);
		array -= (shift_size - old_len);
	}
	return (array);
}

static char *find_variable(circular_dll_t *variables, char **envp, char *command,
			int offset)
{
	int old_len = strlen(command);
	int len = 1;
	char *var = NULL;
	circular_dll_t *temp = variables->go_to[NEXT];

	for (len = 1; command[len + 1] > 20 && command[len + 1] != '$'; len++);
	for (; temp != variables; temp = temp->go_to[NEXT]) {
		if (strncmp(((variable_t *)temp->data)->name, command + 1, len) == 0) {
			var = strdup(((variable_t *)temp->data)->value);
		}
	}
	for (int i = 0; envp[i] != NULL; i++) {
		if (var == NULL && strncmp(envp[i], command + 1, len) == 0) {
			var = strdup(envp[i] + len + 1);
		}
	}
	if (var == NULL)
		return (NULL);
	len++;
	command = shift_array(command, (old_len - len) + strlen(var), offset);
	command = strcpy_no_end_byte(command, var);
	return (command);
}

char *replace_variable(circular_dll_t *variables, char **envp, char *command)
{
	int is_variable = 0;
	int len = strlen(command);
	char *copy = strdup(command);
	char *fail;

	for (int i = 0; command[i]; i++) {
		if (command[i] == '$') {
			command = find_variable(variables, envp,
						command + i, i);
		}
		if (command == NULL) {
			fail = strndup(copy + i + 1, len - i - 1);
			fprintf(stderr, "%s: Undefined variable.\n", fail);
			free(fail);
			return (command);
		}
	}
	if (command == NULL)
		command = copy;
	else
		free(copy);
	return (command);
}
