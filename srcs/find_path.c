/*
** EPITECH PROJECT, 2018
** path
** File description:
** minishell
*/

#include "shell.h"
#include "bultin.h"
#include "str.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int case_command_and_or(shell_t *data, int *i)
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

char *choose_command(shell_t *data, int *i, char **envp)
{
	char *command = NULL;

	for (int j = 0 ; data->different_command[0][j] != NULL ; j++) {
		if (strstr(data->different_command[0][j], "$") != NULL) {
			data->different_command[0][j] =
			replace_variable(data->variables, envp,
					data->different_command[0][j]);
		}
	}
	if (data->different_command[0][0] == NULL)
		return (NULL);
	replace_alias(data);
	if (globing(data) == -1) {
		my_putserr(data->different_command[0][0]);
		my_putserr(": No match.\n");
		data->return_value = 1;
		return (NULL);
	}
	data->path = check_redirecion(data, i);
	if (skip_redirecion(data, i) == 1 || case_command_and_or(data, i) == 1)
		return (NULL);
	command = path_to_binaries(envp, data, data->different_command[0][0]);
	if (command == NULL) {
		data->return_value = 1;
		return (NULL);
	}
	return (command);
}

char *check_access_command(shell_t *data, char *command)
{
	char *bin = my_strdupcat("/bin/", command);

	if (bin == NULL)
		return (NULL);
	if (access(bin, X_OK) == 0)
		return (bin);
	if (data->binaries != NULL)
		for (int i = 0 ; data->binaries[i] != NULL ; i++) {
			data->binaries[i] = my_strdupcat(data->binaries[i], "/");
			data->binaries[i] = my_strdupcat(data->binaries[i], command);
			if (access(data->binaries[i], X_OK) == 0)
				return (data->binaries[i]);
		}
	if (strlen(command) >= 2 && command[0] == '.' && command[1] == '/'
	&& access(command, F_OK) == 0)
		return (command);
	return (NULL);
}

char *find_variable_path(char **envp, char *command, shell_t *data)
{
	int i = 0;

	while (envp[i] != NULL) {
		if (my_strstr(envp[i], "PATH=") == 1) {
			data->binaries = my_str_to_word_array(envp[i] + 5, ':');
			return (command);
		}
		i++;
	}
	data->binaries = NULL;
	return (command);
}

char *path_to_binaries(char **envp, shell_t *data, char *command)
{
	char *temp = NULL;

	if (my_strcmp(command, "setenv") == 0
	&& data->different_command[0][1] == NULL) {
		data->different_command[0][0] = my_strdup("env");
		return (data->different_command[0][0]);
	}
	for (int i = 0 ; tab[i].builtin != NULL ; i++)
		if (my_strcmp(command, tab[i].builtin) == 0)
			return (data->different_command[0][0]);
	if (find_variable_path(envp, command, data) == NULL)
		return (NULL);
	temp = check_access_command(data, command);
	if (temp == NULL) {
		data->return_value = 1;
		fprintf(stderr, "%s: Command not found.\n", command);
		return (NULL);
	}
	return (temp);
}
