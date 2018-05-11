/*
** EPITECH PROJECT, 2018
** path$
** File description:
** minishell
*/

#include "shell.h"
#include <stdlib.h>

char *count_row_path(char *str, shell_t *tcsh)
{
	int i = 5;

	tcsh->row = 1;
	while (str[i] != '\0') {
		if (str[i] == ':')
			tcsh->row++;
		i++;
	}
	tcsh->binaries = malloc(sizeof(char *) * (tcsh->row + 1));
	if (tcsh->binaries == NULL)
		return (NULL);
}

void count_lines_path(char *str, shell_t *tcsh)
{
	int i = 5;
	int mod = 0;
	int k = 0;
	int lines = 0;

	while (str[i] != '\0') {
		if (str[i] == ':') {
			tcsh->binaries[k] = malloc(sizeof(char) * (lines + 1));
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
	tcsh->binaries[k] = malloc(sizeof(char) * (lines));
}

void string_to_binaries(char *str, shell_t *tcsh)
{
	int i = 5;
	int k = 0;
	int mod = 1;
	int j = 0;

	while (str[i] != '\0') {
		if (str[i] == ':' && mod == 0) {
			tcsh->binaries[k][j] = '\0';
			k++;
			j = 0;
			mod = 1;
		}
		else {
			tcsh->binaries[k][j] = str[i];
			j++;
			mod = 0;
		}
		i++;
	}
	tcsh->binaries[k] = NULL;
}

void str_to_word_binaries(char *str, shell_t *tcsh)
{
	count_row_path(str, tcsh);
	count_lines_path(str, tcsh);
	string_to_binaries(str, tcsh);
}
