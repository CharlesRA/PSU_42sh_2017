/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** globbing.c
*/

#include "linked_list.h"
#include <stdlib.h>
#include "str.h"
#include <glob.h>
#include "shell.h"

static int is_globing(char *str)
{
	for (int i = 0 ; str[i] != '\0' ; i++) {
		if (str[i] == '['
		|| str[i] == ']'
		|| str[i] == '*'
		|| str[i] == '?') {
			return (1);
		}
	}
	return (0);
}

static int take_none_glob(circular_dll_t *new_args, char **my_args)
{
	int count = 0;

	for ( ; *my_args != NULL ; my_args++) {
		if (is_globing(*my_args) == 0) {
			count++;
			add_back(new_args, my_strdup(*my_args));
		}
	}
	return (count);
}

static void apply_new_args(circular_dll_t *new_args, shell_t *tcsh)
{
	int size_list = list_len(new_args);
	char **my_new_args = malloc(sizeof(char *) * (size_list + 1));
	circular_dll_t *temp = new_args->go_to[	NEXT];

	for (int i = 0 ; temp != new_args ; i++) {
		my_new_args[i] = (char *) temp->data;
		temp = temp->go_to[NEXT];
	}
	my_new_args[size_list] = NULL;
	tcsh->different_command[0] = my_new_args;
}

static void add_in_list_new_arg(glob_t *globbuf
, circular_dll_t *new_args, shell_t *tcsh)
{
	int end = globbuf->gl_pathc + globbuf->gl_offs;

	for (int i = globbuf->gl_offs; i != end; i++)
		add_back(new_args, my_strdup(globbuf->gl_pathv[i]));
	if (list_len(new_args) == 0)
		add_back(new_args, my_strdup(tcsh->different_command[0][0]));
	apply_new_args(new_args, tcsh);
}

void globing(shell_t *tcsh)
{
	glob_t globbuf;
	circular_dll_t *new_args = create_list();
	int start = 0;

	if (new_args == NULL)
		exit(84);
	globbuf.gl_offs = take_none_glob(new_args, tcsh->different_command[0]);
	globbuf.gl_pathc = 0;
	for (int i = 0 ; i != my_array_len(tcsh->different_command[0]) ; i++) {
		if (is_globing(tcsh->different_command[0][i]) == 0)
			continue;
		if (start == 0) {
			glob(tcsh->different_command[0][i], GLOB_DOOFFS
			, NULL, &globbuf);
			start = 1;
		} else
			glob(tcsh->different_command[0][i]
			, GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
	}
	add_in_list_new_arg(&globbuf, new_args, tcsh);
}
