/*
** EPITECH PROJECT, 2017
** flag_i
** File description:
** PSU
*/

#include "str.h"

void write_nbr(int nb)
{
	int x = 0;

	x = nb % 10;
	nb = nb / 10;
	my_put_nbr_i(nb);
	my_putchar(x + 48);
}
int my_put_nbr_i(int nb)
{
	if (nb < 0) {
		my_putchar('-');
		nb = nb * -1;
	}
	if (nb < 10) {
		my_putchar(nb + 48);
	}
	if (nb >= 10) {
		write_nbr(nb);
	}
	return (0);
}
