/*
** EPITECH PROJECT, 2017
** my_putbinaire
** File description:
** printf
*/

#include "str.h"

char *binary_for_plus(int nbr, char *display)
{
	int i = 0;
	int result = 0;

	display[0] = 0 + 48;
	while (nbr != 0) {
		result = nbr % 2;
		display[i] = result + 48;
		nbr = nbr / 2;
		i++;
	}
	return (display);
}

char *binary_for_less(int nbr, char *display)
{
	int i = 1;
	int result = 0;

	nbr = nbr * -1;
	display[0] = 1 + 48;
	while (nbr != 0)	{
		result = nbr % 2;
		if (result == 1)
			display[i] = 0 + 48;
		if (result == 0)
			display[i] = 1 + 48;
		nbr = nbr / 2;
		i++;
	}
	return (display);
}

char my_printbinaire(int nbr)
{
	char *display;
	int result = 0;
	int i = 1;
	int SizeInt = count_malloc(nbr);

	display = malloc(sizeof(char) * SizeInt * 3);
	if (nbr < 0)
		binary_for_less(nbr, display);
	if (nbr > 0)
		binary_for_plus(nbr, display);
	my_revstr(display);
	my_putstr(display);
}
