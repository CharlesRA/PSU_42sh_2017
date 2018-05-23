/*
** EPITECH PROJECT, 2017
** arguments
** File description:
** module file for my_printf with int conversion arguments
*/

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include "my_printf.h"
#include "my_strings.h"

static void add_zeros(int str, int *bytes, list_t *elmt)
{
	while (str < elmt->precision) {
		my_putchar('0');
		bytes[0]++;
		str++;
	}
}

int base_min(long long nb, char const *base, list_t *elmt)
{
	int str = num_len(nb, base);
	int bytes = 0;

	if (nb < 0) {
		my_putchar('-');
		bytes++;
	} else if (nb >= 0 && check_flag(elmt, '+') == 1) {
		my_putchar('+');
		bytes++;
	}
	if (nb != 0 && elmt->conv == 'o' && check_flag(elmt, '#')) {
		my_putchar('0');
		bytes++;
		str++;
	}
	if (nb == 0 && elmt->precision == 0)
		return (0);
	add_zeros(str, &bytes, elmt);
	return (bytes + my_long_putnbr_base(nb, base));
}

int length_modifier(va_list ap, list_t *elmt, char *str)
{
	switch (elmt->length_mod) {
	case 1:
		return (base_min((unsigned short) va_arg(ap, unsigned int),
				str, elmt));
	case 2:
		return (base_min(va_arg(ap, unsigned long), str, elmt));
	case 3:
		return (base_min(va_arg(ap, uintmax_t), str, elmt));
	case 4:
		return (base_min(va_arg(ap, size_t), str, elmt));
	case 5:
		return (base_min(va_arg(ap, ptrdiff_t), str, elmt));
	case 6:
		return (base_min((unsigned char) va_arg(ap, unsigned int),
				str, elmt));
	case 7:
		return (base_min(va_arg(ap, unsigned long long), str, elmt));
	default:
		return (base_min(va_arg(ap, unsigned int), str, elmt));
	}
}

int unsigned_argument(va_list ap, list_t *element, char *str)
{
	if (check_flag(element, '#') == 1)
		if (element->conv == 'x' || element->conv == 'X') {
			my_putchar('0');
			my_putchar(element->conv);
			element->nb_bytes += 2;
		}
	return (length_modifier(ap, element, str));
}

int signed_argument(va_list ap, list_t *elmt)
{
	char *str = "0123456789";

	switch (elmt->length_mod) {
	case 1:
		return (base_min((short) va_arg(ap, int), str, elmt));
	case 2:
		return (base_min(va_arg(ap, long), str, elmt));
	case 3:
		return (base_min(va_arg(ap, intmax_t), str, elmt));
	case 4:
		return (base_min(va_arg(ap, ssize_t), str, elmt));
	case 5:
		return (base_min(va_arg(ap, ptrdiff_t), str, elmt));
	case 6:
		return (base_min((char) va_arg(ap, int), str, elmt));
	case 7:
		return (base_min(va_arg(ap, long long), str, elmt));
	default:
		return (base_min(va_arg(ap, int), str, elmt));
	}
}
