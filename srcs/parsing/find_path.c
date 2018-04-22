/*
** EPITECH PROJECT, 2018
** path
** File description:
** minishell
*/

#include "shell.h"
#include "builtins.h"
#include "str.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

char *get_the_command(shell_t *new)
{
	char *command = NULL;
	size_t size = 0;
	char **array;

	if (getline(&command, &size, stdin) == -1)
		exit(new->return_value);
	if ((size = my_strlen(command)) == 1)
		return (NULL);
	array = my_str_to_word_array(command, ' ');
	if (array == NULL
	|| priority_array(command, new) == 84
	|| error_operator(new->priority) == 1
	|| non_sence_command(array[0]) == 1) {
		new->return_value = 1;
		return (NULL);
	}
	new->different_command = array_command(array);
	return (command);
}

char *choose_command(shell_t *new, int *i, char **envp)
{
	char *command = NULL;

	new->path = check_redirection(new, i);
	if (skip_redirection(new, i) == 1)
		return (NULL);
	command = path_to_binaries(envp, new, *(new->different_command)[0]);
	if (command == NULL) {
		new->return_value = 1;
		return (NULL);
	}
	return (command);
}

char *check_access_command(shell_t *new, char *command)
{
	for (int i = 0; new->binaries[i] != NULL; i++)
		new->binaries[i] = my_strdupcat(new->binaries[i], "/");
	for (int i = 0; new->binaries[i] != NULL; i++) {
		new->binaries[i] = my_strdupcat(new->binaries[i], command);
		if (access(new->binaries[i], X_OK) == 0)
			return (new->binaries[i]);
	}
	new->return_value = 1;
	error_command(command);
	return (NULL);
}

char *find_variable_path(char **envp, char *command, shell_t *new)
{
	int i = 0;

	while (envp[i] != NULL) {
		if (my_strstr(envp[i], "PATH=") == 1) {
			str_to_word_binaries(envp[i], new);
			break;
		}
		i++;
	}
	if (envp[i] == NULL) {
		new->return_value = 1;
		error_command(command);
		return (NULL);
	}
}

char *path_to_binaries(char **envp, shell_t *new, char *command)
{
	if (my_strcmp(command, "setenv") == 0
	&& new->different_command[0][1] == NULL) {
		new->different_command[0][0] = my_strdup("env");
		return (new->different_command[0][0]);
	}
	for (int i = 0; tab[i].builtin != NULL; i++)
		if (my_strcmp(command, tab[i].builtin) == 0)
			return (new->different_command[0][0]);
	if (access(command, F_OK) == 0)
		return (command);
	if (find_variable_path(envp, command, new) == NULL)
		return (NULL);
	return (check_access_command(new, command));
}
