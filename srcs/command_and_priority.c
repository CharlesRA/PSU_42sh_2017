/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** command_and_priority.c
*/

#include "shell.h"
#include "str.h"

int condition_priority_redirection(shell_t *new, int *i, int *j, char *str)
{
	if (str[*i] == '<') {
		if (str[*i + 1] == '<') {
			new->priority[(*j)++] = TWO_LEFT;
			*i += 1;
		} else
			new->priority[(*j)++] = ONE_LEFT;
	} else if (str[*i] == '>') {
		if (str[*i + 1] == '>') {
			new->priority[(*j)++] = TWO_RIGHT;
			*i += 1;
		} else
			new->priority[(*j)++] = ONE_RIGHT;
	} else if (str[*i] == '&' && str[*i + 1] == '&') {
		new->priority[(*j)++] = AND;
		*i += 1;
	}
	return (EXIT_NORMAL);
}

int condition_priority(shell_t *new, int *i, int *j, char *str)
{
	if (str[*i] == '|') {
		if (str[*i + 1] == '|') {
			new->priority[(*j)++] = OR;
			*i += 1;
		} else
			new->priority[(*j)++] = PIPE;
	} else if (str[*i] == ';' && str[*i + 1] != ';')
		new->priority[(*j)++] = SEMICOLON;
	condition_priority_redirection(new, i, j, str);
	return (EXIT_NORMAL);
}

int priority_array(char *str, shell_t *new)
{
	int len = my_strlen(str) + 1;
	int j = 1;

	new->priority = malloc(sizeof(char) * len + 1);
	if (new->priority == NULL)
		return (EXIT_FAIL);
	new->priority[0] = '#';
	for (int i = 0 ; i < len ; i++)
		condition_priority(new, &i, &j, str);
	new->priority[j] = '\0';
	return (EXIT_NORMAL);
}

int fill_array(char ***array, char **command, int len)
{
	int j = 0;
	int k = 0;

	array[0] = malloc(sizeof(char *) * (len + 1));
	if (array[0] == NULL)
		return (EXIT_FAIL);
	for (int i = 0 ; command[i] != NULL ; i++) {
		array[j][k] = my_strdup(command[i]);
		if (string_is_operator(command[i]) == 1) {
			array[j][k] = NULL;
			k = 0;
			array[++j] = malloc(sizeof(char *) * (len + 1));
		} else
			k++;
	}
	array[j][k] = NULL;
	array[j + 1] = NULL;
	return (EXIT_NORMAL);
}

char ***array_command(char **command)
{
	int len = my_array_len(command) + 1;
	char ***array = malloc(sizeof(char *) * (len + 1));

	fill_array(array, command, len);
	return (array);
}
