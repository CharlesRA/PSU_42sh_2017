/*
** EPITECH PROJECT, 2018
** signals
** File description:
** all signals functions
*/

#include <string.h>
#include <sys/wait.h>
#include "minishell.h"

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
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus)) {
		my_puterror(strsignal(WTERMSIG(wstatus)));
		if (WCOREDUMP(wstatus))
			my_puterror(" (core dumped)");
		my_puterror("\n");
	}
	return (wstatus);
}
