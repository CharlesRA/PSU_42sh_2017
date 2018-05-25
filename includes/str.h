/*
** EPITECH PROJECT, 2018
** str.h
** File description:
** proto
*/

#ifndef STR_H
#define STR_H

#include "linked_list.h"
#include <unistd.h>
#include <stdlib.h>

typedef struct info_t {
	int nbr_word;
	char *nbr_char;
} info_t;

int my_str_isspace_num(char *str);
int my_char_isalpha_num(char alpha);
char **my_array_dup(char **map);
char *get_next_line(int fd);
char *my_revstr(char *str);
int my_strlen(char const *str);
char *my_strdupcat(char *str1, char *str2);
char *my_strdup(char const *src);
void write_nbr(int nb);
void my_printf(const char *format, ...);
int my_getnbr(char const *str);
int is_num(char const *str);
int my_strstr(char *str, char const *to_find);
void my_printbinaire(int nbr);
int my_strcmp(char const *s1, char const *s2);
int my_putstr(char const *str);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strdupcat(char *str1, char *str2);
int my_array_len(char **array);
void my_putchar(char c);
void my_printf(const char *format, ...);
int find_correct_line_env(char **env, char const *to_find);
char **my_str_to_word_array(char *str, char extra);
void my_print_percent(const char *str);
void my_printhexa_caps(int nbr);
void my_printhexa_nocaps(int nbr);
void my_printpointers(long long nbr);
void flag_caps_s(char const *str);
void my_printoctale(int nbr);
int my_put_nbr_d(int nb);
int my_put_unsignednbr(unsigned int nb);
int my_put_nbr_i(int nb);
int my_putserr(char *str);
void my_realloc_char(void *ptr, int size);
void my_realloc_char_star(void *ptr, int size);
long long count_malloc(long long nbr);
int string_is_operator(char *command);
char *get_next_word(char **end, char *str, char extra, int *indice);
int operator(char c);
int char_is_an_operator(char const *str, int *i, int mod);
int calcul_len(char const *str, char extra);

#endif
