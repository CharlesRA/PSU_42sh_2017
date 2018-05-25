/*
** EPITECH PROJECT, 2017
** my_putbinaire
** File description:
** printf
*/

#include "str.h"

void utils(char *display)
{
	my_putstr("0x");
	my_revstr(display);
	my_putstr(display);

}

long long count_malloc(long long nbr)
{
	long long b = 0;

	while (nbr != 0) {
		nbr = nbr / 10;
		b++;
	}
	b = b + 1;
	return (b);
}

void my_printpointers(long long nbr)
{
	char *display;
	long long result = 0;
	long long i = 0;
	long long SizeInt = count_malloc(nbr);

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
	utils(display);
}
