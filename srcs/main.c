/*
** EPITECH PROJECT, 2018
** main
** File description:
** minishell
*/

#include "shell.h"
#include "define.h"

int main(int ac, char **av, char **envp)
{
	shell_t new;

	new.variables = create_list();
	new.history = create_list();
	new.return_value = 0;
	new.alias = create_list();
	if (new.alias == NULL)
		return (EXIT_FAIL);
	loop(&new, envp);
	return (EXIT_NORMAL);
}
