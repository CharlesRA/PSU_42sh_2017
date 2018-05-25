/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** history handling functions ('!')
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

static char *new_len(char *prev_command, char *terminal_str)
{
	int len = strlen(terminal_str);
	char *new_str;
	int no = 0;

	if (strlen(prev_command) <= 2)
		no = 1;
	for (int i = 0; terminal_str[i] && no == 0; i++) {
		if (terminal_str[i] == '!' && terminal_str[i + 1] == '!') {
			len += strlen(prev_command);
			i++;
		}
	}
	new_str = calloc(len, sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);
	return (new_str);
}

char *history_handling(circular_dll_t *history_list, char *terminal_str)
{
	char *prev_command = (char *)history_list->go_to[PREV]->data;
	char *new_str;
	char *copy;

	if (prev_command == NULL)
		prev_command = strdup("exit\n");
	else
		prev_command = strdup(prev_command);
	for (int i = 0; prev_command[i]; i++)
		if (prev_command[i] == '\n')
			prev_command[i] = '\0';
	new_str = new_len(prev_command, terminal_str);
	if (new_str == NULL)
		return (NULL);
	copy = new_str;
	for (int i = 0; terminal_str[i]; i++, new_str++) {
		while (terminal_str[i] == '!' && terminal_str[i + 1] == '!') {
			new_str = strcpy(new_str, prev_command);
			new_str += strlen(prev_command);
			i += 2;
		}
		*new_str = terminal_str[i];
	}
	free(terminal_str);
	printf("%s\n", copy);
	fflush(stdout);
	return (copy);
}
