/*
** EPITECH PROJECT, 2017
** flag_d
** File description:
** PSU
*/

#include "str.h"

int my_put_nbr_d(int nb)
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
