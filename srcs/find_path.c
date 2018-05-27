/*
** EPITECH PROJECT, 2018
** path
** File description:
** minishell
*/

#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "bultin.h"
#include "variables.h"

static char *check_access_command(shell_t *data, char *command)
{
	if (access(command, F_OK) == 0)
		return (access(command, X_OK) == 0 ? command : NULL);
	if (data->binaries != NULL)
		for (int i = 0 ; data->binaries[i] != NULL ; i++) {
			data->binaries[i]
			= my_strdupcat(data->binaries[i], "/");
			data->binaries[i]
			= my_strdupcat(data->binaries[i], command);
			if (access(data->binaries[i], F_OK) == 0)
				return (access(data->binaries[i], X_OK) == 0 ?
					data->binaries[i] : NULL);
		}
	return (NULL);
}

static char *find_variable_path(char **envp, char *command, shell_t *data)
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
