/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** inhibitors.c
*/

#include "linked_list.h"
#include "shell.h"
#include "str.h"
#include <string.h>
#include <stdio.h>

char *remove_backslash(char *command)
{
	char *dest = malloc(sizeof(char) * (my_strlen(command) + 1));
	int j = 0;

	for (int i = 0 ; command[i] != '\0' ; i++) {
		dest[j] = command[i];
		if (command[i] != '\\' && command[i] != '\n' ||
		(command[i] == '\\' && command[i + 1] == '\\') ||
		(command[i - 1] == ' ' && command[i] == '\\' &&
		command[i + 1] == ' ' ))
			j++;
	}
	dest[j] = '\0';
	free(command);
	return (dest);
}

static char *get_the_command_gtl(shell_t *data, char *command, int firstime
, circular_dll_t *list)
{
	size_t size = 0;

	if (firstime == 1)
		printf("? ");
	if (isatty(0) == 0) {
		if (getline(&command, &size, stdin) == -1)
			exit(data->return_value);
		}
	else {
		command = get_next_line(0, list);
		if (command == NULL) {
			exit(data->return_value);
		}
	}
	if (command)
		size = my_strlen(command);
	if (size == 0)
		return (NULL);
	return (command);
}

char *get_the_command_cpy(shell_t *data, char *command, char *all_command
, circular_dll_t *list)
{
	int firstime = 0;
	size_t len = 0;

	do {
		command = get_the_command_gtl(data, command, firstime, list);
		if (command == NULL)
			return (NULL);
		if (command[0] == '\\' && command[1] != '\\') {
			if (firstime == 0)
				printf("? ");
			continue;
		}
		if (firstime == 0) {
			all_command = strdup(command);
			firstime = 1;
		} else
			all_command = my_strdupcat(all_command, command);
		len = strlen(command);
		if (len <= 3 && firstime == 1)
			return (all_command);
	} while ((len <= 3 && command[len - 2] == '\\')
		|| (command[len - 2] == '\\' && command[len - 3] != '\\'));
	return (all_command);
}
