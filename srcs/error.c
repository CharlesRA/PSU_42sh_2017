/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** error.c
*/

#include "shell.h"
#include "str.h"
#include "signals.h"
#include "define.h"
#include <sys/types.h>
#include <sys/wait.h>

int non_sence_command(char *str)
{
	if (my_strcmp(str, "|") == 0
	|| my_strcmp(str, "<") == 0
	|| my_strcmp(str, "<<") == 0
	|| my_strcmp(str, ">") == 0
	|| my_strcmp(str, ">>") == 0) {
		my_printf(NULL_COMMAND);
		return (1);
	}
	return (0);
}

int error_operator(char *str)
{
	for (int i = 0; str[i] != '\0'; i++) {
		if ((str[i] == PIPE && str[i + 1] == TWO_LEFT)
		|| (str[i] == ONE_LEFT && str[i + 1] == TWO_LEFT)
		|| (str[i] == PIPE && str[i + 1] == ONE_LEFT)
		|| (str[i] == ONE_RIGHT && str[i + 1] == TWO_RIGHT)
		|| (str[i] == TWO_RIGHT && str[i + 1] == TWO_RIGHT)
		|| (str[i] == ONE_RIGHT && str[i + 1] == TWO_RIGHT)
		|| (str[i] == ONE_RIGHT && str[i + 1] == ONE_RIGHT)
		|| (str[i] == ONE_LEFT && str[i + 1] == ONE_LEFT)) {
			my_printf(AMBIGUOUS);
			return (1);
		}
	}
	return (0);
}

void error_status(int wstatus, shell_t *new)
{
	new->return_value = WEXITSTATUS(wstatus);
	for (int i = 0; i != 31; i++) {
		if (WTERMSIG(wstatus) == i + 1) {
			wstatus = wstatus < 128 ? wstatus += 128 : wstatus;
			new->return_value = wstatus;
			my_putserr(err[i].message);
			my_putserr("\n");
		}
	}
}
