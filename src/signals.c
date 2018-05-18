/*
** EPITECH PROJECT, 2018
** signals
** File description:
** all signals functions
*/

#include "minishell.h"

void prompt_int(int a)
{
	(void) a;
	my_putchar('\n');
	display_prompt();
}

void ignore(int a)
{
	(void) a;
	return;
}
