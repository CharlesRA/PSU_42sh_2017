/*
** EPITECH PROJECT, 2018
** display
** File description:
** all display functions
*/

#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"

void display_env(char **env)
{
	if (env == NULL)
		return;
	for (int i = 0 ; env[i] ; i++)
		my_printf("%s\n", env[i]);
}

void display_prompt(void)
{
	char *str = NULL;

	if (signal(SIGINT, prompt_int) == SIG_ERR)
		my_perror("signal");
	str = getcwd(str, 0);
	if (str == NULL)
		my_perror(str);
	else {
		my_printf("mysh: %s $> ", str);
		free(str);
	}
}

int prompt(command_t *command)
{
	char *cmd = NULL;
	int value = 0;

	do {
		if (cmd)
			free(cmd);
		if (isatty(0))
			display_prompt();
		cmd = get_next_line(0);
		if (cmd == NULL) {
			destroy_tab(command->env);
			exit_shell(command->ret);
		}
	} while (cmd[0] == 0);
	value = create_tree(&(command->node), cmd);
	free(cmd);
	return (value);
}
