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
#include "str.h"
#include <string.h>

void display_prompt(void)
{
	if (signal(SIGINT, prompt_int) == SIG_ERR)
		my_perror("signal");
	my_putstr("42sh: $> ");
}

int prompt(command_t *command)
{
	char *cmd = NULL;
	int value = 0;
	size_t size = 0;

	do {
		if (cmd)
			free(cmd);
		if (isatty(0))
			display_prompt();
		//cmd = get_next_line(0);
		if (getline(&cmd, &size, stdin) == -1)
			exit_shell(command->ret);
		cmd[strlen(cmd) - 1] = '\0';
		if (cmd == NULL) {
			destroy_tab(command->env);
			exit_shell(command->ret);
		}
	} while (cmd[0] == 0);
	value = create_tree(&(command->node), cmd);
	free(cmd);
	return (value);
}
