/*
** EPITECH PROJECT, 2017
** my_strings.h
** File description:
** contains the header of all string-related functions
*/

#ifndef MY_STRINGS_H_
#define MY_STRINGS_H_

int my_get_check_nbr(char const *str, int *n);
int my_getnbr(char const *str);
int my_itoa(int nb, char **str);
int my_long_putnbr_base(long long nb, char const *base);
int my_printf(char const *str, ...);
void my_putchar(char c);
void my_puterror(char const *str);
int my_putnbr_base(int nb, char const *base);
int my_put_nbr(int nb);
void my_putstr(char const *str);
char *my_revstr(char *str);
int my_show_word_array(char * const *tab);
char *my_strcapitalize(char *str);
char *my_strcat(char *dest, char const *src);
int my_strcmp(char const *s1, char const *s2);
char *my_strcpy(char *dest, char const *src);
char *my_strdup(char const *src);
int my_str_isalpha(char const *str);
int my_str_isnum(char const *str);
int my_strlen(char const *str);
char *my_strlowcase(char *str);
char *my_strncat(char *dest, char const *src, int nb);
int my_strncmp(char const *s1, char const *s2, int n);
char *my_strncpy(char *dest, char const *src, int n);
char *my_strstr(char const *str, char const *to_find);
void destroy_tab(char **tab);
void destroy_triple_tab(char ***tab);
int my_tablen(char **tab);
int my_triple_tablen(char ***tab);
char **my_tabdup(char **tab);
char ***my_triple_tab_dup(char ***tab);
int is_digit(char c);

#endif
