/*
** EPITECH PROJECT, 2018
** env
** File description:
** handles environment var
*/

#include <unistd.h>
#include <sys/wait.h>
#include "commands.h"

int display_env(command_t *command)
{
	pid_t child;

	if (command->env == NULL)
		return (0);
	child = fork();
	if (child == -1) {
		my_perror("fork");
		return (-1);
	} else if (child == 0) {
		change_input_output(command);
		for (int i = 0 ; command->env[i] ; i++)
			my_printf("%s\n", command->env[i]);
		exit(0);
	}
	if (waitpid(child, NULL, 0) == -1) {
		my_perror("waitpid");
		exit_shell(1);
	}
	return (0);
}

char **env_var(char **envp, char const *var)
{
	int len = my_strlen(var);

	if (envp == NULL)
		return (NULL);
	for (int i = 0 ; envp[i] ; i++)
		if (my_strncmp(envp[i], var, len) == 0)
			return (my_str_to_word_array(&envp[i][len], ":"));
	return (NULL);
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
