/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** prepare_auto_complete.c
*/

#include <dirent.h>
#include <term.h>
#include <string.h>
#include "shell.h"

static void add_data(circular_dll_t *list, char *read)
{
	complete_t *data = malloc(sizeof(complete_t));

	data->file = strdup(read);
	data->valid = "\0";
	add_back(list, data);
}

static void read_file_for_complete(DIR * rep, circular_dll_t *list)
{
	struct dirent* data = NULL;

	if (rep == NULL)
		return;
	data = readdir(rep);
	while (data != NULL) {
		add_data(list, data->d_name);
		data = readdir(rep);
	}
}

static void generate_auto_complete(circular_dll_t *list, char **envp)
{
	circular_dll_t *temp = list->go_to[NEXT];
	DIR *rep = NULL;
	int i = find_correct_line_env(envp, "PATH=");
	char **path = NULL;

	if (i == -1)
		return;
	path = my_str_to_word_array(envp[i] + 5, ':');
	if (path == NULL)
		return;
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
	return (EXIT_NORMAL);
}
