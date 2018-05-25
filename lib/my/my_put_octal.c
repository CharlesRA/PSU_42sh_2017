/*
** EPITECH PROJECT, 2018
** printf
** File description:
** PSU
*/

#include "str.h"

void my_printoctale(int nbr)
{
	char *display;
	int result = 0;
	int i = 0;
	int SizeInt = count_malloc(nbr);

	display = malloc(sizeof(char) * (SizeInt + 1));
	while (nbr != 0) {
		result = nbr % 8;
		display[i] = result + 48;
		nbr = nbr / 8;
		i++;
	}
	my_revstr(display);
	my_putstr(display);
}
