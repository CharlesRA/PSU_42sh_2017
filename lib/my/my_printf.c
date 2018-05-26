/*
** EPITECH PROJECT, 2017
** my_printf
** File description:
** PSU
*/

#include "str.h"
#include <stdarg.h>

struct s_flags {
	char flag;
	void *function;
};

static struct s_flags tab[] = {
	{ '!', &my_putstr},
	{ '%', &my_print_percent },
	{ 's', &my_putstr},
	{ 'S', &flag_caps_s},
	{ 'c', &my_putchar},
	{ 'o', &my_printoctale },
	{ 'd', &my_put_nbr_d },
	{ 'i', &my_put_nbr_i},
	{ 'x', &my_printhexa_nocaps },
	{ 'X', &my_printhexa_caps },
	{ 'b', &my_printbinaire },
	{ 'u', &my_put_unsignednbr },
	{ 'p', &my_printpointers },
	{ 'n', &my_put_unsignednbr },
	{ 'm', &my_put_unsignednbr },
};

void print_char(const char *str, int i)
{
	if ((str[i] != '%') && (str[i - 1] != '%'))
		my_putchar(str[i]);
}

int verif_flag_percent(const char *str, int i, int j)
{
	int size = my_strlen(str);

	if (str[i + 1] == tab[j].flag && j == 1) {
		if (i != size - 2)
		my_putchar(str[i]);
		i = i + 1;
	}
	return (i);
}

int verif_flag(const char *str, int i, int j, va_list ap)
{
	void (*pointeurSurFonction)(long long);

	if (str[i + 1] == tab[j].flag && j >= 2) {
		pointeurSurFonction = tab[j].function;
		pointeurSurFonction(va_arg(ap, long long));
		i = i + 1;
	}
	return (i);
}

void my_printf(const char *format, ...)
{
	int j = 0;
	int i = 0;
	va_list ap;

	va_start(ap, format);
	for (i = 0 ;format[i]; i++) {
		while ((format[i] == '%' && format[i + 1] != tab[j].flag)) {
			j++;
			i = verif_flag(format, i, j, ap);
			i = verif_flag_percent(format, i, j);
		}
		print_char(format, i);
		j = 0;
	}
	va_end(ap);
}
