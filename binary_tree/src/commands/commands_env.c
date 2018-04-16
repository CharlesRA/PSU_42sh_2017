/*
** EPITECH PROJECT, 2018
** env
** File description:
** handles environment var
*/

#include "commands.h"

char **env_var(char **envp, char const *var)
{
	char **ret = NULL;
	int len = my_strlen(var);

	if (envp == NULL)
		return (NULL);
	for (int i = 0 ; envp[i] ; i++)
		if (my_strncmp(envp[i], var, len) == 0) {
			ret = my_str_to_word_array(&envp[i][len], ":");
			break;
		}
	return (ret);
}

char **check_env_arguments(char **cmd, char **tmp, int *i)
{
	if (my_strcmp(cmd[0], "-i") == 0) {
		i[0]++;
		destroy_tab(tmp);
		return (NULL);
	}
	return (tmp);
}
