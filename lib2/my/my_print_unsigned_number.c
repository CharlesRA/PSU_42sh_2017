/*
** EPITECH PROJECT, 2017
** my_putbinaire
** File description:
** printf
*/

#include "str.h"

void unsignedwrite_nbr(unsigned int nb)
{
	unsigned int x = 0;

	x = nb % 10;
	nb = nb / 10;
	my_put_nbr_d(nb);
	my_putchar(x + 48);
}

int my_put_unsignednbr(unsigned int nb)
{

	if (nb < 10) {
		my_putchar(nb + 48);
	}
	if (nb >= 10) {
		unsignedwrite_nbr(nb);
	}
	return (0);
}
