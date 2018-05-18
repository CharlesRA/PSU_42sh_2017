/*
** EPITECH PROJECT, 2018
** printf
** File description:
** auxiliary file
*/

#include "my_printf.h"

list_t *auxiliary_modulo(list_t *elmt, char const *str, int *i)
{
	elmt = init_list(check_conversion(str, *i));
	i[0]++;
	add_flags(elmt, str, i);
	add_field_width(elmt, str, i);
	add_precision(elmt, str, i);
	add_length(elmt, str, i);
	return (elmt);
}
