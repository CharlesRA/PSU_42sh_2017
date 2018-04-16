/*
** EPITECH PROJECT, 2018
** set_unsetenv.c
** File description:
** set and unset var from env
*/

#include "commands.h"

char **add_line_to_env(char **envp, char *line, int n)
{
	char **new_env = malloc(sizeof(char *) * (n + 2));

	if (new_env == NULL)
		return (NULL);
	for (int i = 0 ; i < n ; i++)
		new_env[i] = my_strdup(envp[i]);
	new_env[n] = my_strdup(line);
	new_env[n + 1] = NULL;
	destroy_tab(envp);
	return (new_env);
}

char **rm_line_to_env(char **envp, int n)
{
	char **new_env;
	int k = 0;
	int len = 0;

	if (envp[n] == NULL)
		return (envp);
	len = my_tablen(envp);
	new_env = malloc(sizeof(char *) * len);
	if (new_env == NULL)
		return (NULL);
	for (int i = 0 ; envp[i] ; i++)
		if (i != n)
			new_env[k++] = my_strdup(envp[i]);
	new_env[k] = NULL;
	destroy_tab(envp);
	return (new_env);
}

static char **unset_env(char **envp, char *cmd, int len)
{
	if (is_letter(cmd[0]) == 0 || is_alphanum(cmd) == 0) {
		my_puterror("unsetenv: Variable name must contain ");
		my_puterror("alphanumeric characters.\n");
		return (envp);
	}
	for (int i = 0 ; envp[i] ; i++)
		if (my_strncmp(envp[i], cmd, len) == 0) {
			envp = rm_line_to_env(envp, i);
			return (envp);
		}
	return (envp);
}

static char **set_env(char **envp, char **cmd)
{
	char *tmp = NULL;
	int len = my_strlen(cmd[0]);
	int i;

	if (is_letter(cmd[0][0]) == 0) {
		my_puterror("setenv: Variable name must begin ");
		my_puterror("with a letter.\n");
		return (envp);
	} else if (is_alphanum(cmd[0]) == 0) {
		my_puterror("setenv: Variable name must contain ");
		my_puterror("alphanumeric characters.\n");
		return (envp);
	}
	for (i = 0 ; envp[i] ; i++)
		if (my_strncmp(envp[i], cmd[0], len) == 0)
			break;
	tmp = strcat_del(cmd[0], cmd[1], '=');
	if (envp[i]) {
		free(envp[i]);
		envp[i] = my_strdup(tmp);
	} else
		envp = add_line_to_env(envp, tmp, i);
	free(tmp);
	return (envp);
}

int change_env(command_t *command, char **cmd, int type)
{
	int len = 0;

	if (type == 1)
		for (int n = 0 ; cmd[n] ; n++) {
			len = my_strlen(cmd[n]);
			command->env = unset_env(command->env, cmd[n], len);
		}
	else
		command->env = set_env(command->env, cmd);
	return (0);
}
