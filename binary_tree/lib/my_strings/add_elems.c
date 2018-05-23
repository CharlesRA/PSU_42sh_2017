
/*
** EPITECH PROJECT, 2017
** add_elems
** File description:
** fill the my_printf struct
*/

#include "my_printf.h"
#include "my_strings.h"

void add_flags(list_t *element, char const *str, int *i)
{
	char *flags = "#0- +";

	for (int j = 0 ; flags[j] ; j++) {
		if (str[*i] == flags[j]) {
			i[0]++;
			add_flag_to_elem(element, flags[j]);
			j = -1;
		}
	}
}

void add_flag_to_elem(list_t *elmt, char c)
{
	static int index;

	if (elmt->flags[3] == 'e') {
		index = -1;
		elmt->flags[3] = 'f';
	}
	for (int i = 0 ; elmt->flags[i] != 'e' ; i++) {
		if (elmt->flags[i] == c || (elmt->flags[i] == '-' && c == '0')
		|| (elmt->flags[i] == '+' && c == ' '))
			return;
		if (elmt->flags[i] == '0' && c == '-') {
			elmt->flags[i] = c;
			return;
		}
		if (elmt->flags[i] == ' ' && c == '+') {
			elmt->flags[i] = c;
			return;
		}
	}
	elmt->flags[++index] = c;
}

void add_field_width(list_t *element, char const *str, int *i)
{
	int nb = 0;

	if (is_digit(str[*i])) {
		nb = my_getnbr(&str[*i]);
		while (is_digit(str[*i]))
			i[0]++;
		element->field = nb;
	}
}

void add_precision(list_t *element, char const *str, int *i)
{
	int pre = 0;

	if (str[*i] != '.')
		return;
	i[0]++;
	if (str[*i] == '0') {
		element->precision = 1;
		i[0]++;
	}
	if (str[*i] == '-') {
		i[0] -= 2;
		element->conv = 0;
		return;
	}
	pre = (is_digit(str[*i]) ? my_getnbr(&str[*i]) : 0);
	while (is_digit(str[*i]))
		i[0]++;
	element->precision = pre;
}

void add_length(list_t *element, char const *str, int *i)
{
	char *len = "hljzt";

	for (int j = 0 ; len[j] ; j++)
		if (len[j] == str[*i]) {
			element->length_mod = j + 1;
			i[0]++;
			break;
		}
	if (str[*i] == 'h' || str[*i] == 'l') {
		element->length_mod += 5;
		i[0]++;
	}
}
