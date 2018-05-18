/*
** EPITECH PROJECT, 2017
** my_printf_tools
** File description:
** auxiliary functions to my_printf
*/

#include <stdlib.h>
#include "my_printf.h"
#include "my_strings.h"

list_t *init_list(char conv)
{
	list_t *element = malloc(sizeof(*element));

	element->conv = conv;
	for (int i = 0 ; i < 4 ; i++)
		element->flags[i] = 'e';
	element->flags[4] = 0;
	element->precision = -1;
	element->length_mod = 0;
	element->nb_bytes = 0;
	return (element);
}

int num_len(long long nb, char const *base)
{
	int base_len = my_strlen(base);
	int len = 0;

	if (nb == 0)
		return (++len);
	if (nb < 0)
		nb *= -1;
	while (nb != 0) {
		nb /= base_len;
		len++;
	}
	return (len);
}

int put_zeros(char c)
{
	int nb = 0;

	if (c < 8) {
		my_putchar('0');
		nb++;
	}
	if (c < 32) {
		my_putchar('0');
		nb++;
	}
	return (nb);
}

int check_flag(list_t *elmt, char c)
{
	int i = 0;

	while (elmt->flags[i] != 'e' && elmt->flags[i] != 'f') {
		if (elmt->flags[i] == c)
			return (1);
		i++;
	}
	return (0);
}
