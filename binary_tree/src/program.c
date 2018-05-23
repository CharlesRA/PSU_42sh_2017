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

void check_if_pipe_and_dup(command_t *command)
{
	if (command->pipe_fd[0] == 0) {
		change_input_output(command);
		return;
	}
	if (command->fd_tmp == -1) {
		dup2(command->pipe_fd[1], 1);
		close(command->pipe_fd[0]);
		close(command->pipe_fd[1]);
	} else {
		dup2(command->fd_tmp, 0);
		if (command->node->parent->parent->type == PIPE)
			dup2(command->pipe_fd[1], 1);
		else if (command->output != 1)
			dup2(command->output, 1);
	}
}

static uint8_t execute_process(char const *path, command_t *command)
{
	char **cmd = command->node->data;
	pid_t child = fork();
	int wstatus = 0;

	if (child == -1) {
		my_perror("fork");
		return (1);
	} else if (child == 0) {
		check_if_pipe_and_dup(command);
		if (execve(path, cmd, command->env) == -1)
			exit(1);
	}
	if (command->pipe_fd[0] == 0) {
		if (waitpid(child, &wstatus, 0) == -1) {
			my_perror("waitpid");
			exit_shell(1);
		}
		return (check_signal(wstatus));
	}
	return (0);
}

static uint8_t check_and_execute_process(char *path, command_t *command)
{
	if (access(path, X_OK) == 0)
		return (execute_process(path, command));
	my_perror(command->node->data[0]);
	return (1);
}

uint8_t launch_program(command_t *command)
{
	char *cmd_path = get_command_line(command);

	if (signal(SIGINT, ignore) == SIG_ERR)
		my_perror("signal");
	if (cmd_path == NULL)
		return (1);
	return (check_and_execute_process(cmd_path, command));
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
