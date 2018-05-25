/*
** EPITECH PROJECT, 2018
** main
** File description:
** minishell
*/

#include "shell.h"

int main(int ac, char **av, char **envp)
{
	shell_t new;

	new.variables = create_list();
	new.history = create_list();
	new.return_value = 0;
	loop(&new, envp);
	return (0);
}
