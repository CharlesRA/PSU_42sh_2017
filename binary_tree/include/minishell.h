/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** header
*/

#ifndef MINISHELL_H_
#define MINISHELL_H_

#include <stdint.h>
#include <stdlib.h>
#include "my_files.h"
#include "my_strings.h"

typedef enum type {
	ROOT,
	COMMAND,
	PIPE,
	SEMICOLON,
	OPEN_PARENTHESIS,
	CLOSED_PARENTHESIS,
	BRACKET
} type_t;

typedef struct node {
	char *data;
	type_t type;
	struct node *left;
	struct node *right;
} node_t;

typedef struct list {
	node_t *node;
	struct list *next;
} list_t;

typedef struct command {
	node_t *node;
	char **env;
	uint8_t ret;
} command_t;

int minishell(char **envp);

void display_env(char **env);
void display_prompt(void);
int prompt(command_t *command);

char **copy_env(char **envp);
char **env_var(char **envp, char const *var);
char **check_env_arguments(char **cmd, char **tmp, int *i);

char **check_replace_var(char **tab, char **envp, uint8_t ret);

void exit_shell_cmd(char **cmd, int status);
void exit_shell(int status);

char *strcat_del(char const *path, char const *prog, char del);
void execute_prog(char **cmd, char **envp, uint8_t *ret);
void child_process(char **cmd, char **envp, uint8_t *ret);
int launch_program(char **cmd, char **envp);

void prompt_int(int a);
void ignore(int a);

int create_tree(node_t **node, char *cmd);
void destroy_nodes(node_t *node);

int make_tree(node_t **root);

int list_to_rpn(node_t **node);

void destroy_node(node_t *node);
int is_left_associativity(node_t *data);
int precedence(node_t *data);

int is_letter(char c);
int is_alphanum(char const *str);
int my_perror(char const *str);

#endif
