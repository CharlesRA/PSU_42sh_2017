/*
** EPITECH PROJECT, 2018
** main
** File description:
** main minishell function
*/

#include "minishell.h"
#include <sys/ioctl.h>
#include <curses.h>
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


int main(int ac, char **av, char **envp)
{
	int i = find_correct_line_env(envp , "TERM=");
	int err;
	int ret = 0;

	setupterm(envp[i] + 5, 1, &err);
	if (isatty(0) && non_canonic_mode(0) == 84)
		return (84);
	ret = minishell(envp);
	return (ret);
}
