/*
** EPITECH PROJECT, 2018
** main
** File description:
** minishell
*/

#include "shell.h"
#include "define.h"
#include <sys/ioctl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "str.h"
#include <curses.h>
#include <term.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

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

void *add_data(circular_dll_t *list, char *read)
{
	complete_t *data = malloc(sizeof(complete_t));

	data->file = strdup(read);
	data->valid = "\0";
	add_back(list, data);
}

void read_file_for_complete(DIR * rep, circular_dll_t *list)
{
	struct dirent* data = NULL;

	if (rep == NULL)
		return;
	while ((data = readdir(rep)) != NULL) {
		add_data(list, data->d_name);
	}
}

void *generate_auto_complete(circular_dll_t *list, char **envp)
{
	circular_dll_t *temp = list->go_to[NEXT];
	DIR *rep = NULL;
	int i = find_correct_line_env(envp, "PATH=");
	char **path = NULL;

	if (i == -1)
		return (NULL);
	path = my_str_to_word_array(envp[i] + 5, ':');
	if (path == NULL)
		return (NULL);
	for (int i = 0; path[i]; i++) {
		rep = opendir(path[i]);
		read_file_for_complete(rep, list);
	}
	rep = opendir(".");
	read_file_for_complete(rep, list);
}

int init_ncurses(char **envp, circular_dll_t *list)
{
	int err = 0;
	char *term = NULL;
	int i = 0;

	if (isatty(0) == 1) {
		i = find_correct_line_env(envp, "TERM=");
		if (i == -1)
			setupterm("xterm", 1, &err);
		else  {
			term = envp[i];
			setupterm(term + 5, 1, &err);
		}
		if (err < 1 || non_canonic_mode(0) == EXIT_FAIL)
			return (EXIT_FAIL);
		generate_auto_complete(list, envp);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	shell_t new;
	circular_dll_t *list = create_list();

	new.variables = create_list();
	new.history = create_list();
	new.return_value = 0;
	new.alias = create_list();
	if (list == NULL
	|| new.alias == NULL
	|| new.variables == NULL
	|| new.history == NULL
	|| init_ncurses(envp, list) == EXIT_FAIL)
		return (EXIT_FAIL);
	loop(&new, envp, list);
	if (non_canonic_mode(1) == 84)
		return (EXIT_FAIL);
	return (EXIT_NORMAL);
}
