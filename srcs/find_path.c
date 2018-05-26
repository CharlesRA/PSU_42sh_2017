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

char *get_the_command_gtl(shell_t *data, char *command, int firstime
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
	for (int i = 0 ; data->binaries[i] != NULL ; i++) {
		data->binaries[i] = my_strdupcat(data->binaries[i], "/");
		data->binaries[i] = my_strdupcat(data->binaries[i], command);
		if (access(data->binaries[i], X_OK) == 0)
			return (data->binaries[i]);
	}
	if (access(command, F_OK) == 0)
		return (command);
	return (NULL);
}

char *find_variable_path(char **envp, char *command, shell_t *data)
{
	int i = 0;

	while (envp[i] != NULL) {
		if (my_strstr(envp[i], "PATH=") == 1) {
			data->binaries = my_str_to_word_array(envp[i] + 5, ':');
			break;
		}
		i++;
	}
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
		error_command(command);
		return (NULL);
	}
	return (temp);
}
