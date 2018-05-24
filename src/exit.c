/*
** EPITECH PROJECT, 2018
** exit
** File description:
** module to exit shell and free memory allocated
*/

#include <unistd.h>
#include <stdlib.h>
#include "minishell.h"
#include "str.h"

void exit_shell_cmd(char **cmd, int status)
{
	destroy_tab(cmd);
	exit(status);
}

void exit_shell(int status)
{
	if (isatty(0))
		my_putstr("exit\n");
	//non_canonic_mode(1);
	exit(status);
}
