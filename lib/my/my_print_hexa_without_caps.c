/*
** EPITECH PROJECT, 2017
** my_putbinaire
** File description:
** printf
*/

#include "str.h"

void my_printhexa_nocaps(int nbr)
{
	char *display;
	int result = 0;
	int i = 0;
	int SizeInt = count_malloc(nbr);

	display = malloc(sizeof(char) * (SizeInt + 1));
	while (nbr != 0) {
		result = nbr % 16;
		if (result >= 10) {
			result = result % 10;
			display[i] = result + 97;
		}
		else
			display[i] = result + 48;
		nbr = nbr / 16;
		i++;
	}
	my_revstr(display);
	my_putstr(display);
}
