/*
** EPITECH PROJECT, 2018
** path
** File description:
** minishell
*/

#include "minishell.h"
//#include "builtins.h"
#include "str.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

static int match(char const *s1, char const *s2)
{
	int i = 0;
	int j = 0;

	while (s1[i] != '\0') {
		if (s1[i] == s2[i] || s2[i] == '?')
			j++;
		i++;
	}
	if (j == i)
		return (1);
	else
		return (0);
}

static int change_arg(dot_int_t *my_info, DIR **dir, command_t *command)
{
	struct dirent *entry;

	entry = readdir(*dir);
	if (entry == NULL)
		return (-1);
	if (entry->d_type == DT_DIR && my_strlen(entry->d_name) == my_info->idx
	&& entry->d_name[0] != '.') {
		command->node->data[my_info->pos_arg]
		= my_strdup(entry->d_name);
		my_info->pos_arg += 1;
	}
	return (0);
}

static int change_arg_match(dot_int_t *my_info, DIR **dir
, command_t *command, char *src)
{
	struct dirent *entry;

	entry = readdir(*dir);
	if (entry == NULL)
		return (-1);
	if (entry->d_type == DT_DIR && my_strlen(entry->d_name) == my_info->idx
	&& entry->d_name[0] != '.' && match(entry->d_name, src) == 1) {
		command->node->data[my_info->pos_arg]
		= my_strdup(entry->d_name);
		my_info->pos_arg += 1;
	}
	return (0);
}

static void loop_change_arg(command_t *command, int idx, char *src, int mode)
{
	char *cwd = malloc(sizeof(char) * 4096);
	DIR *dir;
	dot_int_t my_info;

	my_info.pos_arg = 1;
	my_info.idx = idx;
	if (cwd == NULL)
		exit(84);
	cwd = getcwd(cwd, 4096);
	dir = opendir(cwd);
	if (dir == NULL)
		exit(84);
	while (1) {
		if (mode == 0) {
			if (change_arg(&my_info, &dir, command) == -1)
				break;
		}
		else {
			if (change_arg_match(&my_info, &dir
			, command, src) == -1)
				break;
		}
	}
	closedir(dir);
}

void interro_dot(command_t *command)
{
	int nbr_letter = 0;

	for (int i = 1; command->node->data[i] != NULL; i++) {
		for (int j = 0; j != my_strlen(command->node->data[i])
		; j++) {
			if (command->node->data[i][j] == '?')
				nbr_letter++;
		}
		if (nbr_letter == my_strlen(command->node->data[i])) {
			loop_change_arg(command, nbr_letter
			, command->node->data[i], 0);
			break;
		}
		else if (nbr_letter != 0) {
			loop_change_arg(command
			, my_strlen(command->node->data[i])
			, command->node->data[i], 1);
			break;
		}
	}
}
