/*
** EPITECH PROJECT, 2017
** my_long_putnbr_base
** File description:
** displays a decimal number into a number in given base
*/

#include "my_strings.h"

int my_long_putnbr_base(long long nb, char const *base)
{
	int bytes = 0;
	int len = my_strlen(base);
	long long rec = nb / len;
	int calc = nb % len;

	if (nb < 0) {
		rec *= -1;
		calc *= -1;
	}
	if (rec != 0)
		bytes += my_long_putnbr_base(rec, base);
	my_putchar(base[calc]);
	bytes++;
	return (bytes);
}
