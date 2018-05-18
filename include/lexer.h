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

int add_command(char *cmd, int *curs, node_t *root);
int add_separator(char *cmd, int *curs, node_t *root);

int is_quote(char c);
int is_word(char c);
int is_bracket(char c);
int is_parenthesis(char c);

#endif
