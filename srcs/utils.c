/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** utils.c
*/

#include "shell.h"
#include "str.h"
#include <sys/wait.h>
#include "bultin.h"

void wait_process(int *nbr, shell_t *new, char ***skip)
{
	int status = 0;

	for (int i = 0; i != *nbr; i++) {
		if (check_builtin(new, skip[0][0]) == 1
		&& my_strcmp(skip[0][0], "env") != 0) {
			*nbr -= 1;
			skip++;
			continue;
		}
		wait(&status);
		error_status(status, new, skip[0][0]);
		skip++;
	}
	*nbr = 0;
}

int change_fdin(int *pipe_fd, shell_t *new)
{
	int fd_in = 1;

	close(pipe_fd[1]);
	fd_in = pipe_fd[0];
	new->different_command++;
	return (fd_in);
}

int operator(char c)
{
	if (c == ';'
	|| c == '|'
	|| c == '<'
	|| c == '>')
		return (1);
	return (0);
}

int char_is_an_operator(char const *str, int *i, int mod)
{
	if ((str[*i] == ';'
	|| str[*i] == '|'
	|| (str[*i] == '<' && str[*i + 1] == '<')
	|| (str[*i] == '>' && str[*i + 1] == '>')
	|| (str[*i] == '<' && str[*i + 1] != '<')
	|| (str[*i] == '>' && str[*i + 1] != '>')) && mod == 1) {
		if ((str[*i] == '<' && str[*i + 1] != '<')
		|| (str[*i] == '>' && str[*i + 1] != '>'))
			i+= 1;
		return (1);
	}
	return (0);
}

char *find_home(char **env)
{
	char *str = NULL;
	int i = 0;
	int j = 0;
	int k = 5;

	i = find_correct_line_env(env, "HOME=");
	if (i != -1) {
		str = malloc(sizeof(char) * my_strlen(env[i]));
		if (str == NULL)
			exit(84);
		while (env[i][k] != '\0')
			str[j++] = env[i][k++];
	}
	return (str);
}
