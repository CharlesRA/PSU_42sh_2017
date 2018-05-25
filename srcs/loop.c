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

int builtin_to_be_fork(char *command)
{
	for (int i = 0; tab[i].builtin != NULL; i++)
		if (strcmp(command, tab[i].builtin) == 0
		&& tab[i].to_be_fork == 1) {
			return (1);
		}
	return (0);
}

int wait_process_semicolon(shell_t *tcsh, int i, int *proc)
{
	if (tcsh->priority[i] == SEMICOLON
	|| tcsh->priority[i] == OR
	|| tcsh->priority[i] == AND)
		wait_process(proc, tcsh);
	get_index(i, 1);
	return (0);
}

int apply_command(shell_t *tcsh, char **envp, int *proc)
{
	int  pipe_fd[2] = {0, 0};
	int temp = -1;

	for (int i = 0; tcsh->priority[i] != '\0'; i++) {
		wait_process_semicolon(tcsh, i, proc);
		if ((tcsh->command = choose_command(tcsh, &i, envp)) == NULL) {
			tcsh->different_command++;
			continue;
		}
		if (check_builtin(tcsh->command) == 1
		&& builtin_to_be_fork(tcsh->command) == 0)
			case_builtin(proc, tcsh, envp);
		else {
			*proc += 1;
			temp = case_fork(temp, pipe_fd, tcsh, envp);
		}
		tcsh->different_command++;
	}
	return (0);
}

char **loop_command(shell_t *tcsh, char **envp)
{
	int proc = 0;

	apply_command(tcsh, envp, &proc);
	wait_process(&proc, tcsh);
	return (envp);
}

int loop(shell_t *tcsh, char **envp)
{
	char *command = NULL;

	while (1) {
		if (isatty(0) == 1)
			my_putstr("$> : ");
		command = get_the_command(tcsh);
		if (command == NULL)
			continue;
		if (strcmp(command, "exit") == 0)
			return (0);
		if (strstr(command, "!!") != NULL) {
			command = history_handling(tcsh->history, command);
		}
		if (command == NULL)
			continue;
		add_back(tcsh->history, command);
			envp = loop_command(tcsh, envp);
	}
	return (0);
}
