/*
** EPITECH PROJECT, 2018
** my_itoa
** File description:
** creates a string from an int
*/

#include <stdlib.h>
#include "my_strings.h"

int my_nblen(int nb)
{
	int cnt = 0;

	if (nb <= 0) {
		++cnt;
		nb *= -1;
	}
	while (nb) {
		nb /= 10;
		++cnt;
	}
	return (cnt);
}

int my_itoa(int nb, char **str)
{
	int len = my_nblen(nb);
	int i = 0;
	int neg = (nb < 0 ? 1 : 0);

	str[0] = malloc(len + 1);
	if (str[0] == NULL)
		return (-1);
	if (neg) {
		str[0][i++] = '-';
		nb *= -1;
	}
	for ( ; i < len ; i++) {
		str[0][i] = (nb % 10) + '0';
		nb /= 10;
	}
	str[0][i] = 0;
	my_revstr((neg ? &str[0][1] : str[0]));
	return (0);
}
