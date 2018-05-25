/*
** EPITECH PROJECT, 2017
** my_printf
** File description:
** header
*/

#ifndef MY_PRINTF_H_
#define MY_PRINTF_H_

#include <stdarg.h>

typedef struct list {
	char flags[5];
	int field;
	int precision;
	int length_mod;
	char conv;
	int nb_bytes;
} list_t;

int my_putstr(char const *str);
int check_if_regular(char c);
char check_conversion(char const *str, int i);
int display_element(va_list ap, list_t *element);
int do_modulo(va_list ap, char const *str, int *i);
int my_printf(char const *str, ...);

list_t *auxiliary_modulo(list_t *elmt, char const *str, int *i);

int base_min(long long nb, char const *base, list_t *elmt);
int length_modifier(va_list ap, list_t *elmt, char *str);
int unsigned_argument(va_list ap, list_t *element, char *str);
int signed_argument(va_list ap, list_t *elmt);

list_t *init_list(char conv);
int num_len(long long nb, char const *base);
int put_zeros(char c);
int check_flag(list_t *elmt, char c);

void add_flag_to_elem(list_t *element, char c);
void add_flags(list_t *element, char const *str, int *i);
void add_field_width(list_t *element, char const *str, int *i);
void add_precision(list_t *element, char const *str, int *i);
void add_length(list_t *element, char const *str, int *i);

int flag_char(va_list ap, list_t *element);
int non_print_str(char *str);
int flag_str(va_list ap, list_t *element);
int flag_int(va_list ap, list_t *element);
int flag_basenum(va_list ap, list_t *element);

#endif
