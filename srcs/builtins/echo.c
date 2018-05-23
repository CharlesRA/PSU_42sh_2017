/*
** EPITECH PROJECT, 2018
** charles.raimbault@epitech.eu
** File description:
** echo.c
*/

void echo(char ***command)
{
	for (int i = 1; command[0][i] != NULL; i++) {
		my_putstr(command[0][i]);
		if (command[0][i + 1] != NULL)
			my_putstr(" ");
	}
	my_putstr("\n");
}
