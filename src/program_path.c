/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** checks if program exists, or if it doesn't, checks in PATH var
*/

#include <unistd.h>
#include "minishell.h"
#include "str.h"

char *strcat_del(char const *path, char const *prog, char del)
{
	char *ret = NULL;
	int len = my_strlen(path) + my_strlen(prog) + 2;
	int n = 0;

	ret = malloc(len);
	if (ret == NULL)
		return (NULL);
	if (path)
		for (int i = 0 ; path[i] ; i++)
			ret[n++] = path[i];
	ret[n++] = del;
	if (prog)
		for (int i = 0 ; prog[i] ; i++)
			ret[n++] = prog[i];
	ret[n] = 0;
	return (ret);
}

char *get_command_line(command_t *command)
{
	char **path = NULL;
	char *tmp = NULL;

	if (access(command->node->data[0], F_OK) == 0)
		return (my_strdup(command->node->data[0]));
	path = env_var(command->env, "PATH=");
	if (path == NULL)
		return (NULL);
	for (int n = 0 ; path[n] ; n++) {
		tmp = strcat_del(path[n], command->node->data[0], '/');
		if (tmp == NULL)
			break;
		if (access(tmp, F_OK) == 0) {
			destroy_tab(path);
			return (tmp);
		}
		free(tmp);
	}
	my_puterror(command->node->data[0]);
	my_puterror(": Command not found.\n");
	destroy_tab(path);
	return (NULL);
}
