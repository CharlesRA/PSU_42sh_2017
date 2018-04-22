/*
** EPITECH PROJECT, 2018
** cd
** File description:
** minishell
*/

#include <stdio.h>
#include "shell.h"
#include "define.h"
#include "str.h"
#include "builtins.h"

char **change_pwd(char **envp)
{
	char *cwd = malloc(sizeof(char) * 4096);
	int i = 0;

	if (cwd == NULL)
		exit(84);
	cwd = getcwd(cwd, 4096);
	if (getcwd(cwd, 4096) != NULL) {
		i = find_correct_line_env(envp, "PWD=");
		envp[i] = my_strdupcat("PWD=", cwd);
		return (envp);
	}
	else
		perror("getcwd() error");
	return (NULL);
}

char **change_old_pwd(char **envp)
{
	char *cwd = malloc(sizeof(char) * 4096);
	int i = 0;

	if (cwd == NULL)
		exit(84);
	if (getcwd(cwd, 4096) == NULL) {
		perror("getcwd() error");
		return (envp);
	}
	cwd = getcwd(cwd, 4096);
	i = find_correct_line_env(envp, "OLDPWD=");
	if (i != -1)
		envp[i] = my_strdupcat("PWD=", cwd);
	else {
		i = my_array_len(envp);
		envp[i] = my_strdupcat("OLDPWD=", cwd);
		my_realloc_char_star(&envp, 1);
		envp[i + 1] = NULL;
	}
	free(cwd);
	return (envp);
}

int change_directory_part_two(shell_t *new, char **env)
{
	char *home;
	int dir = 0;

	if (new->different_command[0][1] != NULL)
		dir = chdir(new->different_command[0][1]);
	if (new->different_command[0][1] == NULL
	|| my_strcmp(new->different_command[0][1], "~") == 0) {
		home = find_home(env);
		if (home == NULL)
			return (84);
		dir = chdir(home);
		if (dir != -1)
			free(home);
	}
	if (dir == -1) {
		new->return_value = 1;
		my_printf(ERROR_CD, new->different_command[0][1]);
		return (84);
	}
	return (0);
}

char *compare_cd(shell_t *new, char *cwd, char **env)
{
	int dir = 0;

	if (my_strcmp(new->different_command[0][1], "-") == 0
	&& cwd != NULL) {
		dir = chdir(cwd);
		cwd = getcwd(cwd, 4096);
		if (dir == -1) {
			new->return_value = 1;
			my_printf(ERROR_CD
			, new->different_command[0][1]);
			return (NULL);
		}
	}
	if (my_strcmp(new->different_command[0][1], "-") != 0) {
		cwd = getcwd(cwd, 4096);
		change_directory_part_two(new, env);
		return (cwd);
	}
	return (cwd);
}

char **change_directory(shell_t *new, char **env)
{
	static char *cwd = NULL;
	char *temp;

	env = change_old_pwd(env);
	if (new->different_command[0][1] != NULL) {
		temp = compare_cd(new, cwd, env);
		if (temp == NULL)
			return (NULL);
		cwd = temp;
	}
	else {
		if (change_directory_part_two(new, env) == 84)
			return (NULL);
	}
	env = change_pwd(env);
	return (env);
}
