/*
** EPITECH PROJECT, 2017
** flags_S
** File description:
** printf
*/

#include "str.h"

int verif_ascii3(char const *str, int i)
{
	if (str[i] >= 127) {
		my_putchar('\\');
		my_printoctale(str[i]);
	}
	return (i);

}

int verif_ascii2(char const *str, int i)
{
	if (str[i] >= 8 && str[i] < 32) {
		my_putchar('\\');
		my_putstr("0");
		my_printoctale(str[i]);
		i++;
	}
	return (i);

}

int verif_ascii1(char const *str, int i)
{
	if (str[i] <= 7) {
		my_putchar('\\');
		my_putstr("00");
		my_printoctale(str[i]);
		i++;
	}
	return (i);
}

void flag_caps_s(char const *str)
{
	int i = 0;

	while (str[i] != '\0') {
		i = verif_ascii1(str, i);
		i = verif_ascii2(str, i);
		i = verif_ascii3(str, i);
		my_putchar(str[i]);
		i = i + 1;
	}
}
