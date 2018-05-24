/*
** EPITECH PROJECT, 2018
** signals
** File description:
** all signals functions
*/

#include "str.h"
#include <string.h>
#include <sys/wait.h>
#include "minishell.h"
#include "signals.h"

void prompt_int(int a)
{
	my_putchar('\n');
	display_prompt();
}

void ignore(int a)
{
	return;
}

int check_signal(int wstatus)
{
	wstatus = WEXITSTATUS(wstatus);
	for (int i = 0; i != 31; i++) {
		if (WTERMSIG(wstatus) == i + 1) {
			wstatus = wstatus < 128 ? wstatus += 128 : wstatus;
			wstatus = wstatus;
			my_putserr(err[i].message);
			my_putserr("\n");
		}
	}
	return (wstatus);
}
