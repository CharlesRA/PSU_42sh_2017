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
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int non_canonic_mode(int i)
{
	static struct termios old;
	static struct termios new;

	if (i == 0) {
		if (ioctl(0 , TCGETS, &old) == -1
		|| ioctl(0 , TCGETS, &new) == -1)
			return (84);
		new.c_lflag &= ~ECHO;
		new.c_lflag &= ~ICANON;
		ioctl(0, TCSETS, &new);
	}
	if (i == 1) {
		ioctl(0, TCSETS, &old);
	}
	return (0);
}

void wait_process(int *nbr, shell_t *new)
{
	int status = 0;

	for (int i = 0; i != *nbr; i++) {
		wait(&status);
		error_status(status, new);
	}
	*nbr = 0;
}

int operator(char c)
{
	if (c == ';'
	|| c == '|'
	|| c == '&'
	|| c == '<'
	|| c == '>')
		return (1);
	return (0);
}

int char_is_an_operator(char const *str, int *i, int mod)
{
	if ((str[*i] == '|'
	|| str[*i] == '<'
	|| str[*i] == '>'
	|| (str[*i] == ';'  && str[*i + 1] != ';')
	|| (str[*i] == '&'  && str[*i + 1] == '&')) && mod == 1) {
		if ((str[*i] == '<' && str[*i + 1] != '<')
		|| (str[*i] == '>' && str[*i + 1] != '>'))
			i += 1;
		return (1);
	}
	return (0);
}

char *find_home(char **env)
{
	char *str = NULL;
	int j = 0;
	int k = 5;
	int i = find_correct_line_env(env, "HOME=");

	if (i != -1) {
		str = malloc(sizeof(char) * my_strlen(env[i]));
		if (str == NULL)
			exit(84);
		while (env[i][k] != '\0')
			str[j++] = env[i][k++];
	}
	str[j] = '\0';
	return (str);
}
