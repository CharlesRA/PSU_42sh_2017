/*
** EPITECH PROJECT, 2018
** my_files
** File description:
** header
*/

#ifndef MY_FILES_H_
#define MY_FILES_H_

#ifndef READ_SIZE
#define READ_SIZE (1)
#endif

char *get_next_line(int fd);
char **load_2d_arr_from_file(char const *filepath, int nb_rows, int nb_cols);
char *load_file_in_mem(char const *filepath);
char **mem_alloc_2d_array(int nb_rows, int nb_cols);
char *mem_alloc(char const *a, char const *b);
char **mem_dup_2d_array(char **arr, int nb_rows, int nb_cols);
char **my_str_to_word_array(char const *str, char const *d);
char **parse_file(char const *filepath, char const *parsing);
char **parse_cmd(int fd, char const *parsing);

#endif
