/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** header
*/

#ifndef MINISHELL_H_
#define MINISHELL_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "my_files.h"
#include "my_strings.h"
#include "linked_list.h"

#define WRONG_ARCH "%s: Exec format error. Wrong Architecture.\n"
#define PERM_DENIED "%s: Permission denied.\n"
#define AMBIGUOUS "Ambiguous output redirect.\n"
#define NULL_COMMAND "Invalid null command.\n"

typedef struct s_complete
{
	char *file;
	char *valid;
} complete_t;

typedef enum type {
	ROOT = 45,
	COMMAND,
	OPEN_PARENTHESIS,
	CLOSED_PARENTHESIS,
	PIPE,
	SEMICOLON,
	ONE_LEFT_BRACKET,
	TWO_LEFT_BRACKET,
	ONE_RIGHT_BRACKET,
	TWO_RIGHT_BRACKET,
	AND,
	OR,
	UNKNOWN,
} type_t;

typedef struct node {
	char **data;
	struct node *parent;
	struct node *left;
	struct node *right;
	type_t type;
} node_t;

typedef struct s_line
{
	char *command;
	circular_dll_t *arguments;
} line_t;

typedef struct list {
	node_t *node;
	struct list *next;
} list_t;

typedef struct command {
	node_t *node;
	char **env;
	int output;
	int input;
	int fd_tmp;
	int pipe_fd[2];
	uint8_t ret;
	char **binaries;
	int row;
} command_t;

typedef struct s_dot_int
{
	int pos_arg;
	int idx;
	char *src;
} dot_int_t;

void globing(command_t *command);

int check_builtin(command_t *command);

void change_input_output(command_t const *command);
int check_node(command_t *command);
int minishell(char **envp);

void display_prompt(void);
int prompt(command_t *command);

uint8_t launch_program(command_t *command);
int execute_command(command_t *command);

void pipe_node(command_t *command);

char *strcat_del(char const *path, char const *prog, char del);
char *get_command_line(command_t *command);

void change_input_output(command_t const *command);
void close_input_output(command_t const *command);
int get_output(node_t const *node, type_t type);
int get_input(node_t const *node, type_t type);

int display_env(command_t *command);
char **copy_env(char **envp);
char **env_var(char **envp, char const *var);
char **check_env_arguments(char **cmd, char **tmp, int *i);

char **check_replace_var(char **tab, char **envp, uint8_t ret);

void exit_shell_cmd(char **cmd, int status);
void exit_shell(int status);

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
void loop_replace_arg(command_t *command, circular_dll_t *my_letters
, char *src);
void interro_dot(command_t *command);
int check_signal(int wstatus);
int brackets(command_t *command);
void check_if_pipe_and_dup(command_t *command);
void str_to_word_binaries(char *str, command_t *new);

#endif
