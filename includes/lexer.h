/*
** EPITECH PROJECT, 2018
** lexer
** File description:
** header
*/

#ifndef LEXER_H_
#define LEXER_H_

#include "minishell.h"

int lexing(node_t **root, char *cmd);

int add_command(char **cmd, node_t *last, int *i);
int add_separator(char *cmd, node_t *last);

int is_quote(char c);
int is_word(char c);
int is_bracket(char c);
int is_parenthesis(char c);

#endif
