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
#include <stdio.h>

int wait_process_semicolon(shell_t *tcsh, int i, char ***skip, int *proc)
{
	get_index(i, 1);
	if (tcsh->priority[i] == SEMICOLON || tcsh->priority[i] == AND || tcsh->priority[i] == OR) {
		wait_process(proc, tcsh,skip);
		if (tcsh->priority[i] == AND && tcsh->return_value != 0)
			return (1);
		else if (tcsh->priority[i] == OR && tcsh->return_value == 0)
			return (1);
	}
	return (0);
}

int apply_command(shell_t *tcsh, char **envp, char ***skip, int *proc)
{
	int  pipe_fd[2] = {0, 0};
	int temp = -1;

	for (int i = 0; tcsh->priority[i] != '\0'; i++) {
		if ((tcsh->command = choose_command(tcsh,&i, envp)) == NULL) {
			tcsh->different_command++;
			continue;
		}
		if (wait_process_semicolon(tcsh,i, skip, proc) == 1)
			continue;
		if (check_builtin(tcsh,tcsh->command) == 1
		&& my_strcmp(tcsh->command, "env") != 0)
			case_builtin(proc, tcsh,envp, skip);
		else {
			*proc += 1;
			temp = case_fork(temp, pipe_fd, tcsh,envp);
		}
		tcsh->different_command++;
	}
	return (0);
}

char **loop_command(shell_t *tcsh, char **envp, char ***skip)
{
	int proc = 0;

	apply_command(tcsh,envp, skip, &proc);
	wait_process(&proc, tcsh,skip);
	fflush(stdout);
	return (envp);
}

int loop(shell_t *tcsh, char **envp)
{
	char *command = NULL;
	char ***skip = NULL;

	while (1) {
		if (isatty(0) == 1)
			my_putstr("$> : ");
		command = get_the_command(tcsh);
		if (command == NULL)
			continue;
		if (my_strcmp(command, "exit\n") == 0)
			return (0);
		skip = tcsh->different_command;
		envp = loop_command(tcsh,envp, skip);
	}
	return (0);
}
