/*
** EPITECH PROJECT, 2018
** exec2
** File description:
** bootstrap
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "my_strings.h"

static void ext_program(int *fd_pipe, char **args, char **envp, uint8_t *ret)
{
	pid_t pid = fork();

	if (pid == -1) {
		my_perror("fork");
		exit(84);
	}
	if (pid == 0) {
		dup2(fd_pipe[mode], mode);
		close(fd_pipe[0]);
		close(fd_pipe[1]);
		child_process(args[0], envp, &ret);
	}
}

static void middle_programs(int **fd_pipe, char **args, char **envp, uint8_t *ret)
{
	pid_t pid = fork();

	if (pid == -1) {
		my_perror("fork");
		exit(84);
	}
	if (pid == 0) {
		dup2(fd_pipe[0][0], 0);
		dup2(fd_pipe[1][1], 1);
		close(fd_pipe[0][0]);
		close(fd_pipe[0][1]);
		close(fd_pipe[1][0]);
		close(fd_pipe[1][1]);
		child_process(args[0], envp, &ret);
	}
	close(fd_pipe[0][0]);
	close(fd_pipe[0][1]);
}

static int pipe_programs(char ***args, char **envp)
{
	int nb_pipes = my_triple_tablen(args) - 1;
	int **fd_pipe = malloc(sizeof(int *) * nb_pipes);

	if (fd_pipe == NULL)
		return (1);
	for (int i = 0 ; i < nb_pipes ; i++) {
		fd_pipe[i] = malloc(sizeof(int) * 2);
		if (fd_pipe[i] == NULL)
			return (1);
		pipe(fd_pipe[i]);
	}
	ext_program(fd_pipe[0], args[0], envp, 0);
	for (int i = 1 ; i < nb_pipes ; i++)
		middle_programs(&fd_pipe[current - 1], args[current], envp);
	ext_program(fd_pipe[nb_pipes - 1], args[nb_pipes], envp, 1);
	for (int i = 0 ; i < nb_pipes ; i++)
		free(fd_pipe[i]);
	free(fd_pipe);
	return (0);
}

static char ***parsing_args(int len, char **av)
{
	char ***args = malloc(sizeof(char **) * (len + 1));

	if (args == NULL)
		return (NULL);
	for (int i = 0 ; i < len ; i++)
		args[i] = my_str_to_word_array(av[i + 1], " \t");
	args[len] = NULL;
	return (args);
}

int pipe_list(int ac, char **av, char **envp)
{
	char ***args = parsing_args(ac, av);
	int ret = 0;

	if (args == NULL)
		return (1);
	ret = pipe_programs(args, envp);
	destroy_triple_tab(args);
	return (ret);
}
