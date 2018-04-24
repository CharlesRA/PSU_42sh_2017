/*
** EPITECH PROJECT, 2018
** program
** File description:
** executes a program
*/

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
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

char *strcat_del(char const *path, char const *prog, char del)
{
	int len = my_strlen(path) + my_strlen(prog) + 2;
	char *ret = malloc(len);
	int n = 0;

	if (ret == NULL)
		return (NULL);
	if (path)
		for (int i = 0 ; path[i] ; i++)
			ret[n++] = path[i];
	ret[n++] = del;
	if (prog)
		for (int i = 0 ; prog[i] ; i++)
			ret[n++] = prog[i];
	ret[n] = 0;
	return (ret);
}

void execute_prog(char **cmd, char **envp, uint8_t *ret)
{
	char **path = env_var(envp, "PATH=");
	char *path_test = NULL;

	if (path == NULL) {
		ret[0] = 1;
		return;
	}
	for (int n = 0 ; path[n] ; n++) {
		path_test = strcat_del(path[n], cmd[0], '/');
		if (path_test == NULL)
			break;
		if (access(path_test, F_OK) != -1) {
			ret[0] = 0;
			destroy_tab(path);
			execve(path_test, cmd, envp);
		}
		free(path_test);
	}
	ret[0] = 1;
	destroy_tab(path);
	my_puterror(cmd[0]);
	my_puterror(": Command not found.\n");
}

void child_process(char **cmd, char **envp, uint8_t *ret)
{
	struct stat buff;

	if (cmd[0][0] == '.' || cmd[0][0] == '/') {
		if (stat(cmd[0], &buff) == -1) {
			my_perror(cmd[0]);
			ret[0] = 1;
			return;
		}
		if (access(cmd[0], F_OK) == 0 && S_ISDIR(buff.st_mode) == 0) {
			execve(cmd[0], cmd, envp);
		} else {
			errno = EACCES;
			my_perror(cmd[0]);
			ret[0] = 1;
		}
	} else {
		if (access(cmd[0], F_OK) != -1) {
			ret[0] = 0;
			execve(cmd[0], cmd, envp);
		}
		execute_prog(cmd, envp, ret);
	}
	exit(*ret);
}

int launch_program(char **cmd, char **envp)
{
	pid_t child;
	int wstatus = 0;
	uint8_t ret = 0;

	if (signal(SIGINT, ignore) == SIG_ERR)
		my_perror("signal");
	child = fork();
	if (child == -1) {
		my_perror("fork");
		return (1);
	} else if (child == 0)
		child_process(cmd, envp, &ret);
	else {
		if (waitpid(child, &wstatus, 0) == -1) {
			my_perror("waitpid");
			exit_shell_cmd(cmd, 1);
		}
		ret = check_signal(wstatus);
	}
	return (ret);
}
