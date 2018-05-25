/*
** EPITECH PROJECT, 2018
** error_msg
** File description:
** minishell
*/

#include "str.h"
#include "define.h"
#include <errno.h>

void error_command(char *message)
{
	my_putserr(message);
	my_putserr(": Command not found.\n");
}

void error_execve(char *command)
{
	if (errno == 13)
		my_printf(PERM_DENIED, command);
	if (errno == 8)
		my_printf(WRONG_ARCHITECTURE, command, command);
}

int error_pid(int pid)
{
	return (pid == -1 ? 84 : 0);
}
