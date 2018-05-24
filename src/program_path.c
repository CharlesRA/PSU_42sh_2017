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
	int i = 0;

	if (access(command->node->data[0], F_OK) == 0)
		return (my_strdup(command->node->data[0]));
	command->binaries = env_var(command->env, "PATH=");
	if (command->env[i] == NULL)
		return (NULL);
	for (int i = 0; command->binaries[i] != NULL; i++) {
		command->binaries[i] = my_strdupcat(command->binaries[i], "/");
		command->binaries[i] = my_strdupcat(command->binaries[i], command->node->data[0]);
		if (access(command->binaries[i], X_OK) == 0)
			return (command->binaries[i]);
	}
	my_puterror(command->node->data[0]);
	my_puterror(": Command not found.\n");
	destroy_tab(command->binaries);
	return (NULL);
}
