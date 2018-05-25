/*
** EPITECH PROJECT, 2018
** program
** File description:
** executes a program
*/

#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include "minishell.h"
#include "glob.h"
#include "str.h"

static int is_globing(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
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

	for (; *my_args != NULL; my_args++) {
		if (is_globing(*my_args) == 0) {
			count++;
			add_back(new_args, my_strdup(*my_args));
		}
	}
	return (count);
}

static void apply_new_args(circular_dll_t *new_args, command_t *command)
{
	int size_list = list_len(new_args);
	char **my_new_args = malloc(sizeof(char *) * (size_list + 1));
	circular_dll_t *temp = new_args->go_to[	NEXT];

	for (int i = 0; temp != new_args; i++) {
		my_new_args[i] = (char *)temp->data;
		temp = temp->go_to[NEXT];
	}
	my_new_args[size_list] = NULL;
	command->node->data = my_new_args;
}

static void add_in_list_new_arg(glob_t *globbuf
, circular_dll_t *new_args, command_t *command)
{
	int end = globbuf->gl_pathc + globbuf->gl_offs;

	for (int i = globbuf->gl_offs; i != end; i++)
		add_back(new_args, my_strdup(globbuf->gl_pathv[i]));
	apply_new_args(new_args, command);
}

void globing(command_t *command)
{
	glob_t globbuf;
	circular_dll_t *new_args = create_list();
	int start = 0;

	if (new_args == NULL)
		exit(84);
	globbuf.gl_offs = take_none_glob(new_args, command->node->data);
	globbuf.gl_pathc = 0;
	for (int i = 1; i != my_array_len(command->node->data); i++) {
		if (is_globing(command->node->data[i]) == 0)
			continue;
		if (start == 0) {
			glob(command->node->data[i], GLOB_DOOFFS
			, NULL, &globbuf);
			start = 1;
		} else
			glob(command->node->data[i]
			, GLOB_DOOFFS | GLOB_APPEND, NULL, &globbuf);
	}
	add_in_list_new_arg(&globbuf, new_args, command);
}
