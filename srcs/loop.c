/*
** EPITECH PROJECT, 2018
** loop
** File description:
** minishell
*/

#include <string.h>
#include <unistd.h>
#include "shell.h"
#include "str.h"
#include "nbr.h"
#include "bultin.h"

int wait_process_semicolon(shell_t *new, int i, int *proc)
{
	if (new->priority[i] == SEMICOLON
	|| new->priority[i] == OR
	|| new->priority[i] == AND)
		wait_process(proc, new);
	get_index(i, 1);
	return (0);
}

int apply_command(shell_t *new, char **envp, int *proc)
{
	int  pipe_fd[2] = {0, 0};
	int temp = -1;

	for (int i = 0; new->priority[i] != '\0'; i++) {
		wait_process_semicolon(new, i, proc);
		if ((new->command = choose_command(new, &i, envp)) == NULL) {
			new->different_command++;
			continue;
		}
		if (check_builtin(new, new->command) == 1
		&& my_strcmp(new->command, "env") != 0
		&& my_strcmp(new->command, "echo") != 0)
			case_builtin(proc, new, envp);
		else {
			*proc += 1;
			temp = case_fork(temp, pipe_fd, new, envp);
		}
		new->different_command++;
	}
	return (0);
}

char **loop_command(shell_t *new, char **envp)
{
	int proc = 0;

	apply_command(new, envp, &proc);
	wait_process(&proc, new);
	return (envp);
}

int loop(shell_t *new, char **envp)
{
	char *command = NULL;

	while (1) {
		if (isatty(0) == 1)
			my_putstr("$> : ");
		command = get_the_command(new);
		if (command == NULL)
			continue;
		if (strcmp(command, "exit") == 0)
			return (0);
		add_back(new->history, command);
			envp = loop_command(new, envp);
	}
	return (0);
}
