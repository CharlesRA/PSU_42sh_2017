/*
** EPITECH PROJECT, 2018
** setenv
** File description:
** minishell
*/

#include "shell.h"
#include "str.h"
#include "define.h"

int overwrite_env(char *envp, shell_t *tcsh)
{
	int i = 0;
	int size = my_strlen(envp);
	char *str = malloc(sizeof(char) * size + 1);
	int result = 0;

	if (str == NULL)
		exit(84);
	while (envp[i] != '=' && envp[i] != '\0') {
		str[i] = envp[i];
		i++;
	}
	str[i] = '\0';
	result = my_strcmp(str, tcsh->different_command[0][1]);
	free(str);
	return (result);
}

int check_invalid_char(char *str)
{
	for (int i = 0; str[i]; i++) {
		if ((str[i] < 'A' || str[i] > 'Z')
		&& (str[i] < 'a' || str[i] > 'z')
		&& (str[i] < '0' || str[i] > '9')
		&& str[i] != '_')
			return (1);
	}
	return (0);
}

char **set_env_arg(int i, shell_t *tcsh, char **envp, int overwrite)
{
	if (overwrite == 0) {
		my_realloc_char_star(&envp, 1);
		envp[i + 1] = NULL;
	}
	tcsh->different_command[0][1]
	= my_strdupcat(tcsh->different_command[0][1], "=");
	if (tcsh->different_command[0][2] == NULL)
		envp[i] = my_strdupcat(NULL, tcsh->different_command[0][1]);
	else
		envp[i] = my_strdupcat(tcsh->different_command[0][1]
		, tcsh->different_command[0][2]);
	return (envp);
}

int set_env_error(shell_t *tcsh, char **envp)
{
	if (check_invalid_char(tcsh->different_command[0][1]) == 1) {
		tcsh->return_value = 1;
		my_putstr("setenv: Variable name must contain"
		" alphanumeric characters.\n");
		return (1);
	}
	if (tcsh->different_command[0][2] != NULL) {
		if (tcsh->different_command[0][3] != NULL) {
			tcsh->return_value = 1;
			my_putserr("setenv: Too many arguments.\n");
			return (1);
		}
	}
	return (0);
}

char **set_env(shell_t *tcsh, char **envp)
{
	int i = 0;
	int overwrite = 0;

	if (set_env_error(tcsh,envp) == 1)
		return (envp);
	while (envp[i] != NULL) {
		if (overwrite_env(envp[i], tcsh) == 0) {
			overwrite = 1;
			break;
		}
		i++;
	}
	envp = set_env_arg(i, tcsh,envp, overwrite);
	return (envp);
}
