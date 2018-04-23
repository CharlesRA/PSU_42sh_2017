/*
** EPITECH PROJECT, 2018
** loop
** File description:
** minishell
*/

#include <unistd.h>
#include "shell.h"
#include "str.h"
#include "nbr.h"
#include "builtins.h"

int wait_process_semicolon(shell_t *new, int i, char ***skip, int *proc)
{
	get_index(i, 1);
	if (new->priority[i] == SEMICOLON || new->priority[i] == AND || new->priority[i] == OR) {
		wait_process(proc, new, skip);
		if (new->priority[i] == AND && new->return_value != 0)
			return (1);
		else if (new->priority[i] == OR && new->return_value == 0)
			return (1);
	}
	return (0);
}

int apply_command(shell_t *new, char **envp, char ***skip, int *proc)
{
	int  pipe_fd[2] = {0, 0};
	int temp = -1;

	for (int i = 0; new->priority[i] != '\0'; i++) {
		if ((new->command = choose_command(new, &i, envp)) == NULL) {
			new->different_command++;
			continue;
		 }
		if (wait_process_semicolon(new, i, skip, proc) == 1)
			continue;
		if (check_builtin(new, new->command) == 1
		&& my_strcmp(new->command, "env") != 0)
			case_builtin(proc, new, envp, skip);
		else {
			*proc += 1;
			temp = case_fork(temp, pipe_fd, new, envp);
		}
		 new->different_command++;
	}
	return (0);
}

char **loop_command(shell_t *new, char **envp, char ***skip)
{
	int proc = 0;

	apply_command(new, envp, skip, &proc);
	wait_process(&proc, new, skip);
	return (envp);
}

int loop(shell_t *new, char **envp)
{
	char *command = NULL;
	char ***skip = NULL;

	while (1) {
		if (isatty(0) == 1)
			my_putstr("$> : ");
		command = get_the_command(new);
		if (command == NULL)
			continue;
		if (my_strcmp(command, "exit\n") == 0)
			return (0);
		skip = new->different_command;
		envp = loop_command(new, envp, skip);
	}
	return (0);
}
