/*
** EPITECH PROJECT, 2018
** path
** File description:
** minishell
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
//#include "builtins.h"
#include "str.h"
#include "linked_list.h"

static char *change_whitout_brackets(char *str)
{
	char *temp = str;

	while (*temp != '\0') {
		if (*temp == '[') {
			*temp = '\0';
			break;
		}
		temp++;
	}
	for (;*temp != ']'; temp++);
	*temp = '*';
	return (my_strdupcat(str, temp));
}

static int compare_to_list(char c, circular_dll_t *my_letters)
{
	circular_dll_t *temp = my_letters->go_to[NEXT];

	while (temp != my_letters) {
		if (c == *(char *)temp->data)
			return (1);
		temp = temp->go_to[NEXT];
	}
	return (0);
}

static int compare_str(const char *s1, const char *s2
, circular_dll_t *my_letters)
{
	for (;*s1 != '\0' && *s2 != '\0'; s1++, s2++) {
		if (*s1 != *s2 && *s2 != '*')
			return (0);
		if (*s2 == '*' && compare_to_list(*s1, my_letters) != 1)
			return (0);
	}
	if (*s1 == *s2)
		return (1);
	return (0);
}

static int change_arg(DIR **dir, command_t *command
, circular_dll_t *my_letters, dot_int_t *my_info)
{
	struct dirent *entry;

	entry = readdir(*dir);
	if (entry == NULL)
		return (-1);
	if (entry->d_type == DT_DIR && entry->d_name[0] != '.'
	&& compare_str(entry->d_name, my_info->src, my_letters) == 1) {
		command->node->data[my_info->pos_arg]
		= my_strdup(entry->d_name);
		my_info->pos_arg += 1;
	}
	return (0);
}

void loop_replace_arg(command_t *command, circular_dll_t *my_letters
, char *src)
{
	char *cwd = malloc(sizeof(char) * 4096);
	DIR *dir;
	dot_int_t my_info;

	my_info.pos_arg = 1;
	if (cwd == NULL)
		exit(84);
	cwd = getcwd(cwd, 4096);
	dir = opendir(cwd);
	if (dir == NULL)
		exit(84);
	src = change_whitout_brackets(src);
	my_info.src = src;
	while (1) {
		if (change_arg(&dir, command, my_letters, &my_info) == -1)
			break;
	}
	closedir(dir);
}
