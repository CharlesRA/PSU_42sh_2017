/*
** EPITECH PROJECT, 2018
** loop
** File description:
** minishell
*/

#include <string.h>
#include "shell.h"
#include "nbr.h"
#include "builtin.h"

static int builtin_to_be_fork(char *command)
{
	for (int i = 0 ; tab[i].builtin != NULL ; i++)
		if (strcmp(command, tab[i].builtin) == 0
		&& tab[i].to_be_fork == 1) {
			return (1);
		}
	return (EXIT_NORMAL);
}

static int wait_process_semicolon(shell_t *data, int i, int *proc)
{
	if (data->priority[i] == SEMICOLON
	|| data->priority[i] == OR
	|| data->priority[i] == AND)
		wait_process(proc, data);
	get_index(i, 1);
	return (EXIT_NORMAL);
}

static int apply_command(shell_t *data, char **envp, int *proc)
{
	int  pipe_fd[2] = {0, 0};
	int temp = -1;

	for (int i = 0 ; data->priority[i] != '\0' ; i++) {
		wait_process_semicolon(data, i, proc);
		data->command = choose_command(data, &i, envp);
		if (data->command == NULL) {
			data->different_command++;
			continue;
		}
		if (check_builtin(data->command) == 1
		&& builtin_to_be_fork(data->command) == 0)
			case_builtin(proc, data, envp);
		else {
			*proc += 1;
			temp = case_fork(temp, pipe_fd, data, envp);
		}
		data->different_command++;
	}
	return (EXIT_NORMAL);
}

static char **loop_command(shell_t *data, char **envp)
{
	int proc = 0;

	apply_command(data, envp, &proc);
	wait_process(&proc, data);
	return (envp);
}

int loop(shell_t *data, char **envp, circular_dll_t *list)
{
	char *command = NULL;

	while (1) {
		if (isatty(0) == 1)
			my_putstr("$> : ");
		command = get_the_command(data, list);
		if (command == NULL)
			continue;
		if (strcmp(command, "exit") == 0)
			return (EXIT_NORMAL);
		add_back(data->history, command);
		envp = loop_command(data, envp);
	}
	return (EXIT_FAIL);
}
