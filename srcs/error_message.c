/*
** EPITECH PROJECT, 2018
** error_msg
** File description:
** minishell
*/

#include "str.h"
#include "define.h"
#include <errno.h>
#include <stdio.h>

void error_execve(char *command)
{
	if (errno == 13)
		my_printf(PERM_DENIED, command);
	if (errno == 8)
		my_printf(WRONG_ARCHITECTURE, command);
}

int error_pid(int pid)
{
	return (pid == -1 ? EXIT_FAIL : EXIT_NORMAL);
}
