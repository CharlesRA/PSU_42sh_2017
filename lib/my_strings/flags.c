/*
** EPITECH PROJECT, 2017
** flags
** File description:
** flags module of my_printf
*/

#include "my_printf.h"
#include "my_strings.h"

int flag_char(va_list ap, list_t *element)
{
	my_putchar(va_arg(ap, int));
	element->nb_bytes++;
	return (0);
}

int non_print_str(char *str)
{
	int bytes = 0;

	for (int i = 0 ; str[i]; i++) {
		if (str[i] < 32 || str[i] >= 127)
			bytes += my_printf("\\%.3o", str[i]);
		else {
			my_putchar(str[i]);
			bytes++;
		}
	}
	return (bytes);
}

int flag_str(va_list ap, list_t *element)
{
	int i = 0;
	int nb = element->precision;
	char *str = va_arg(ap, char*);

	if (str == 0) {
		my_putstr("(null)");
		return (6);
	}
	if (element->conv == 'S')
		return (non_print_str(str));
	if (nb == -1 || nb > my_strlen(str))
		nb = my_strlen(str);
	while (nb > 0) {
		my_putchar(str[i]);
		i++;
		nb--;
	}
	return (i);
}

int flag_int(va_list ap, list_t *element)
{
	return (signed_argument(ap, element));
}

int flag_basenum(va_list ap, list_t *element)
{
	long nb;
	char *s[5] = {"01", "01234567", "0123456789"};
	char *base_num = "bouxX";

	s[3] = "0123456789abcdef";
	s[4] = "0123456789ABCDEF";
	if (element->conv == 'p') {
		nb = va_arg(ap, long);
		if (nb == 0) {
			my_putstr("(nil)");
			return (5);
		}
		return (my_printf("%#lx", nb));
	}
	for (int i = 0 ; base_num[i] ; i++)
		if (element->conv == base_num[i])
			return (unsigned_argument(ap, element, s[i]));
	return (0);
}
