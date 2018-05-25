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

char *get_the_command_gtl(shell_t *tcsh, char *command, int firstime
, circular_dll_t *list)
{
	size_t size = 0;

	if (firstime == 1)
		printf("? ");
	if (isatty(0) == 0) {
		if (getline(&command, &size, stdin) == -1)
			exit(tcsh->return_value);
		}
	else {
		command = get_next_line(0, list);
		if (command == NULL) {
			exit(tcsh->return_value);
		}
	}
	if (command)
		size = my_strlen(command);
	if (size == 0)
		return (NULL);
	return (command);
}

char *get_the_command_cpy(shell_t *tcsh, char *command, char *all_command
, circular_dll_t *list)
{
	int firstime = 0;
	size_t len = 0;

	do {
		command = get_the_command_gtl(tcsh, command, firstime, list);
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

int case_command_and_or(shell_t *tcsh, int *i)
{
	if (tcsh->priority[*i] == AND && tcsh->return_value != 0)
		return (1);
	if (tcsh->priority[*i] == OR && tcsh->return_value == 0)
		return (1);
	return (EXIT_NORMAL);
}

char *get_the_command(shell_t *tcsh, circular_dll_t *list)
{
	char *all_command = NULL;
	char *command = get_the_command_cpy(tcsh, NULL, NULL, list);
	size_t size = 0;

	if (command == NULL)
		return (NULL);
	command = remove_backslash(command);
	if (strstr(command, "!!") != NULL)
		command = history_handling(tcsh->history, command);
	tcsh->array = my_str_to_word_array(command, ' ');
	if (tcsh->array == NULL
	|| priority_array(command, tcsh) == 84
	|| error_operator(tcsh->priority) == 1
	|| non_sence_command(tcsh->array[0]) == 1) {
		tcsh->return_value = 1;
		return (NULL);
	}
	tcsh->different_command = array_command(tcsh->array);
	return (command);
}

char *choose_command(shell_t *tcsh, int *i, char **envp)
{
	char *command = NULL;

	for (int j = 0 ; tcsh->different_command[0][j] != NULL ; j++) {
		if (strstr(tcsh->different_command[0][j], "$") != NULL) {
			tcsh->different_command[0][j] =
			replace_variable(tcsh->variables, envp,
					tcsh->different_command[0][j]);
		}
	}
	if (tcsh->different_command[0][0] == NULL)
		return (NULL);
	replace_alias(tcsh);
	if (globing(tcsh) == -1) {
		my_putserr(tcsh->different_command[0][0]);
		my_putserr(": No match.\n");
		tcsh->return_value = 1;
		return (NULL);
	}
	tcsh->path = check_redirecion(tcsh, i);
	if (skip_redirecion(tcsh, i) == 1 || case_command_and_or(tcsh, i) == 1)
		return (NULL);
	command = path_to_binaries(envp, tcsh, tcsh->different_command[0][0]);
	if (command == NULL) {
		tcsh->return_value = 1;
		return (NULL);
	}
	return (command);
}

char *check_access_command(shell_t *tcsh, char *command)
{
	for (int i = 0 ; tcsh->binaries[i] != NULL ; i++) {
		tcsh->binaries[i] = my_strdupcat(tcsh->binaries[i], "/");
		tcsh->binaries[i] = my_strdupcat(tcsh->binaries[i], command);
		if (access(tcsh->binaries[i], X_OK) == 0)
			return (tcsh->binaries[i]);
	}
	if (access(command, F_OK) == 0)
		return (command);
	tcsh->return_value = 1;
	error_command(command);
	return (NULL);
}

char *find_variable_path(char **envp, char *command, shell_t *tcsh)
{
	int i = 0;

	while (envp[i] != NULL) {
		if (my_strstr(envp[i], "PATH=") == 1) {
			tcsh->binaries = my_str_to_word_array(envp[i] + 5, ':');
			break;
		}
		i++;
	}
	if (envp[i] == NULL) {
		tcsh->return_value = 1;
		error_command(command);
		return (NULL);
	}
}

char *path_to_binaries(char **envp, shell_t *tcsh, char *command)
{
	if (my_strcmp(command, "setenv") == 0
	&& tcsh->different_command[0][1] == NULL) {
		tcsh->different_command[0][0] = my_strdup("env");
		return (tcsh->different_command[0][0]);
	}
	for (int i = 0 ; tab[i].builtin != NULL ; i++)
		if (my_strcmp(command, tab[i].builtin) == 0)
			return (tcsh->different_command[0][0]);
	if (find_variable_path(envp, command, tcsh) == NULL)
		return (NULL);
	return (check_access_command(tcsh, command));
}
