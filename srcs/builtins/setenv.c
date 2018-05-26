/*
** EPITECH PROJECT, 2018
** setenv
** File description:
** minishell
*/

#include "shell.h"

int overwrite_env(char *envp, shell_t *new)
{
	int i = 0;
	int size = my_strlen(envp);
	char *str = malloc(sizeof(char) * size + 1);
	int result = 0;

	if (str == NULL)
		exit(EXIT_FAIL);
	while (envp[i] != '=' && envp[i] != '\0') {
		str[i] = envp[i];
		i++;
	}
	str[i] = '\0';
	result = my_strcmp(str, new->different_command[0][1]);
	free(str);
	return (result);
}

int check_invalid_char(char *str)
{
	for (int i = 0 ; str[i] ; i++) {
		if ((str[i] < 'A' || str[i] > 'Z')
		&& (str[i] < 'a' || str[i] > 'z')
		&& (str[i] < '0' || str[i] > '9')
		&& str[i] != '_')
			return (1);
	}
	return (0);
}

char **set_env_arg(int i, shell_t *new, char **envp, int overwrite)
{
	if (overwrite == 0) {
		my_realloc_char_star(&envp, 1);
		envp[i + 1] = NULL;
	}
	new->different_command[0][1]
	= my_strdupcat(new->different_command[0][1], "=");
	if (new->different_command[0][2] == NULL)
		envp[i] = my_strdupcat(NULL, new->different_command[0][1]);
	else
		envp[i] = my_strdupcat(new->different_command[0][1]
		, new->different_command[0][2]);
	return (envp);
}

int set_env_error(shell_t *new, char **envp)
{
	if (check_invalid_char(new->different_command[0][1]) == 1) {
		new->return_value = 1;
		my_putstr("setenv: Variable name must contain"
		" alphanumeric characters.\n");
		return (1);
	}
	if (new->different_command[0][2] != NULL) {
		if (new->different_command[0][3] != NULL) {
			new->return_value = 1;
			my_putserr("setenv: Too many arguments.\n");
			return (1);
		}
	}
	return (EXIT_NORMAL);
}

char **set_env(shell_t *new, char **envp)
{
	int i = 0;
	int overwrite = 0;

	if (set_env_error(new, envp) == 1)
		return (envp);
	while (envp[i] != NULL) {
		if (overwrite_env(envp[i], new) == 0) {
			overwrite = 1;
			break;
		}
		i++;
	}
	envp = set_env_arg(i, new, envp, overwrite);
	return (envp);
}
