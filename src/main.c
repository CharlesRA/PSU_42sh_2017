/*
** EPITECH PROJECT, 2018
** main
** File description:
** main minishell function
*/

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	if (ac != 1) {
		(void) av;
		return (1);
	}
	return (minishell(envp));
}
