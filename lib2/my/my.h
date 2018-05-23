/*
** EPITECH PROJECT, 2017
** str.h
** File description:
** my_printf
*/

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void utils(char *display);

int verif_ascii3(char const *str, int i);

int verif_ascii2(char const *str, int i);

int verif_ascii1(char const *str, int i);

void my_print_percent(char const *str);

void my_printpointers(long long nbr);

void unsignedwrite_nbr(unsigned int nb);

void flag_caps_s(char const *str);

char *binary_for_plus(int nbr, char *display);

char my_printbinaire(int nbr);

char *binary_for_less(int nbr, char *display);

void write_nbr(int nb);

void my_putchar_special(void);

int my_put_unsignednbr(unsigned int nb);

long long count_malloc(long long nbr);

void my_printoctale(int nbr);

void my_printhexa_caps(int nbr);

void my_printhexa_nocaps(int nbr);

void my_putchar(char c);

int my_put_nbr_d(int nb);

int my_put_nbr_i(int nb);

void my_putstr(char const *str);

int my_strlen(char const *str);

int my_getnbr(char const *str);

char *my_revstr(char *str);

char *my_strdup(char *src);
