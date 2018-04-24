/*
** EPITECH PROJECT, 2017
** my_printf
** File description:
** equivalent to printf
*/

#include <stdlib.h>
#include "my_printf.h"
#include "my_strings.h"

int check_if_regular(char c)
{
	char *possible = "dicsSp#0- +.hlbouxX123456789jzt";

	for (int i = 0 ; possible[i] ; i++)
		if (c == possible[i])
			return (1);
	my_putchar('%');
	return (0);
}

char check_conversion(char const *str, int i)
{
	int j = 0;
	char *conv = "dibouxXcsSp";

	while (str[i]) {
		j = 0;
		while (conv[j] != 0 && conv[j] != str[i]) {
			j++;
		}
		if (conv[j] == str[i])
			return (conv[j]);
		i++;
	}
	return (0);
}

int display_element(va_list ap, list_t *element)
{
	char *char_str = "dsciS";
	int (*fptr[3])(va_list, list_t*) = {&flag_int, &flag_str,
					&flag_char};

	for (int i = 0 ; char_str[i] ; i++)
		if (element->conv == char_str[i])
			return (fptr[i % 3](ap, element));
	return (flag_basenum(ap, element));
}

int do_modulo(va_list ap, char const *str, int *i)
{
	list_t *elmt = NULL;
	int n_bytes = 0;

	if (check_if_regular(str[*i + 1]) == 0) {
		i[0]++;
		if (str[*i] == '%')
			return (1);
		my_putchar(str[*i]);
		return (2);
	}
	elmt = auxiliary_modulo(elmt, str, i);
	if (elmt->conv == 0) {
		free(elmt);
		my_putchar('%');
		return (1);
	}
	n_bytes += (display_element(ap, elmt) + elmt->nb_bytes);
	free(elmt);
	return (n_bytes);
}

int my_printf(char const *str, ...)
{
	int nb_bytes = 0;
	va_list ap;

	va_start(ap, str);
	for (int i = 0 ; str[i] ; i++) {
		if (str[i] == '%' && str[i + 1] != 0)
			nb_bytes += do_modulo(ap, str, &i);
		else {
			my_putchar(str[i]);
			nb_bytes++;
		}
	}
	va_end(ap);
	return (nb_bytes);
}
