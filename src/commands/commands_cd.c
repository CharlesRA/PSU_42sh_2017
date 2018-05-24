/*
** EPITECH PROJECT, 2018
** cd
** File description:
** cd command module
*/

#include <unistd.h>
#include <stdio.h>
#include "commands.h"

static int cd_in_cdpath(char **cdpath, char const *folder)
{
	char *path = NULL;

	for (int i = 0 ; cdpath[i] ; i++) {
		path = strcat_del(cdpath[i], folder, '/');
		if (path == NULL)
			return (1);
		if (access(path, F_OK) != -1) {
			chdir(path);
			free(path);
			return (0);
		}
		free(path);
	}
	return (1);
}

static char **create_old_pwd(void)
{
	char **change = malloc(sizeof(char *) * 3);

	if (change == NULL)
		return (NULL);
	change[0] = my_strdup("OLDPWD");
	change[1] = getcwd(NULL, 0);
	if (change[1] == NULL)
		return (NULL);
	change[2] = NULL;
	return (change);
}

static int special_cd(char **envp, char **var, char const *name)
{
	var = env_var(envp, name);
	if (var == NULL)
		return (1);
	return (chdir(var[0]) == -1 ? 1 : 0);
}

static void check_path(char *cmd, char **var, command_t *command)
{
	var = env_var(command->env, "CDPATH=");
	if (cmd[0] == '/' || var == NULL) {
		if (chdir(cmd) == -1) {
			command->ret = 1;
			my_perror(cmd);
		}
	} else {
		command->ret = cd_in_cdpath(var, cmd);
		if (command->ret == 1)
			my_perror(cmd);
	}
}

int do_cd(char *cmd, command_t *command)
{
	char **var = NULL;
	char **change;

	if (command->node->parent->type == PIPE)
		return (0);
	change = create_old_pwd();
	if (cmd == NULL || my_strcmp(cmd, "~") == 0) {
		command->ret = special_cd(command->env, var, "HOME=");
		if (command->ret == 1)
			return (1);
	} else if (my_strcmp(cmd, "-") == 0) {
		command->ret = special_cd(command->env, var, "OLDPWD=");
		if (command->ret == 1)
			return (1);
	} else
		check_path(cmd, var, command);
	if (change) {
		change_env(command, change, 0);
		destroy_tab(change);
	}
	destroy_tab(var);
	return (0);
}
