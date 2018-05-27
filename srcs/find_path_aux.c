/*
** EPITECH PROJECT, 2018
** auxiliary functions for path
** File description:
** 42sh
*/

#include <string.h>
#include "shell.h"
#include "variables.h"

static int case_command_and_or(shell_t *data, int *i)
{
	if (data->priority[*i] == AND && data->return_value != 0)
		return (1);
	if (data->priority[*i] == OR && data->return_value == 0)
		return (1);
	return (EXIT_NORMAL);
}

char *get_the_command(shell_t *data, circular_dll_t *list)
{
	char *all_command = NULL;
	char *command = get_the_command_cpy(data, NULL, NULL, list);
	size_t size = 0;

	if (command == NULL)
		return (NULL);
	command = remove_backslash(command);
	if (strstr(command, "!!") != NULL)
		command = history_handling(data->history, command);
	data->array = my_str_to_word_array(command, ' ');
	if (data->array == NULL
	|| priority_array(command, data) == 84
	|| error_operator(data->priority) == 1
	|| non_sence_command(data->array[0]) == 1) {
		data->return_value = 1;
		return (NULL);
	}
	data->different_command = array_command(data->array);
	return (command);
}

static int check_globing(shell_t *data)
{
	if (globing(data) == -1) {
		my_putserr(data->different_command[0][0]);
		my_putserr(": No match.\n");
		data->return_value = 1;
		return (1);
	}
	return (0);
}

static void check_variables_to_replace(shell_t *data, char **envp)
{
	for (int j = 0 ; data->different_command[0][j] != NULL ; j++)
		if (strstr(data->different_command[0][j], "$") != NULL)
			data->different_command[0][j] =
			replace_variable(data->variables, envp,
					data->different_command[0][j]);
}

char *choose_command(shell_t *data, int *i, char **envp)
{
	char *command = NULL;

	check_variables_to_replace(data, envp);
	if (data->different_command[0][0] == NULL)
		return (NULL);
	replace_alias(data);
	if (check_globing(data) == 1)
		return (NULL);
	data->path = check_redirection(data, i);
	if (skip_redirection(data, i) == 1 || case_command_and_or(data, i) == 1)
		return (NULL);
	command = path_to_binaries(envp, data, data->different_command[0][0]);
	if (command == NULL) {
		data->return_value = 1;
		return (NULL);
	}
	handle_special_var(data, envp);
	return (command);
}
