/*
** EPITECH PROJECT, 2018
** program
** File description:
** executes a program
*/

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "minishell.h"

int check_signal(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus)) {
		my_puterror(strsignal(WTERMSIG(wstatus)));
		if (WCOREDUMP(wstatus))
			my_puterror(" (core dumped)");
		my_puterror("\n");
	}
	return (wstatus);
}

static uint8_t execute_process(command_t *command)
{
	char **cmd = command->node->data;
	pid_t child = fork();
	int wstatus = 0;

	if (child == -1) {
		my_perror("fork");
		return (1);
	} else if (child == 0) {
		change_input_output(command);
		execve(cmd[0], cmd, command->env);
	}
	if (waitpid(child, &wstatus, 0) == -1) {
		my_perror("waitpid");
		exit_shell(1);
	}
	return (check_signal(wstatus));
}

static uint8_t check_and_execute_process(command_t *command)
{
	if (access(command->node->data[0], X_OK) == 0)
		return (execute_process(command));
	my_perror(command->node->data[0]);
	return (1);
}

uint8_t launch_program(command_t *command)
{
	if (signal(SIGINT, ignore) == SIG_ERR)
		my_perror("signal");
	if (get_command_line(command) == 1)
		return (1);
	return (check_and_execute_process(command));
}

int execute_command(command_t *command)
{
	if (command == NULL)
		return (0);
	if (check_builtin(command) == 0)
		return (0);
	command->ret = launch_program(command);
	return (0);
}
