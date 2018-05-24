/*
** EPITECH PROJECT, 2018
** path$
** File description:
** minicommand
*/

#include "minishell.h"
#include <stdlib.h>

char *count_row_path(char *str, command_t *new)
{
	int i = 5;

	new->row = 1;
	while (str[i] != '\0') {
		if (str[i] == ':')
			new->row++;
		i++;
	}
	new->binaries = malloc(sizeof(char *) * (new->row + 1));
	if (new->binaries == NULL)
		return (NULL);
}

void count_lines_path(char *str, command_t *new)
{
	int i = 5;
	int mod = 0;
	int k = 0;
	int lines = 0;

	while (str[i] != '\0') {
		if (str[i] == ':') {
			new->binaries[k] = malloc(sizeof(char) * (lines + 1));
			k++;
			lines = 0;
			mod = 1;
		}
		else {
			lines++;
			mod = 0;
		}
		i++;
	}
	new->binaries[k] = malloc(sizeof(char) * (lines));
}

void string_to_binaries(char *str, command_t *new)
{
	int i = 5;
	int k = 0;
	int mod = 1;
	int j = 0;

	while (str[i] != '\0') {
		if (str[i] == ':' && mod == 0) {
			new->binaries[k][j] = '\0';
			k++;
			j = 0;
			mod = 1;
		}
		else {
			new->binaries[k][j] = str[i];
			j++;
			mod = 0;
		}
		i++;
	}
	new->binaries[k] = NULL;
}

void str_to_word_binaries(char *str, command_t *new)
{
	count_row_path(str, new);
	count_lines_path(str, new);
	string_to_binaries(str, new);
}
