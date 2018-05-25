/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** PSU
*/

#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>
#include "alias.h"
#include "linked_list.h"

enum OPERATOR {
	PIPE = 49,
	SEMICOLON,
	ONE_LEFT,
	TWO_LEFT,
	ONE_RIGHT,
	TWO_RIGHT,
	OR,
	AND,
};

typedef struct s_shell
{
	int return_value;
	char **array;
	char **binaries;
	char *priority;
	char ***different_command;
	char *path;
	char *command;
	circular_dll_t *alias;
} shell_t;

char *path_to_binaries(char *envp[], shell_t *new, char *command);
int check_lines_envp(char *envp);
char *path_to_binaries(char *envp[], shell_t *new, char *command);
void error_status(int wstatus, shell_t *new);
char **change_directory(shell_t *new, char **env);
int loop(shell_t *new, char **envp);
int find_correct_line_env(char **env, char *to_find);
int check_env(char **envp);
void error_command(char *message);
void destroy_array(shell_t *new);
int priority_array(char *str, shell_t *new);
char ***array_command(char **command);
int operator_pipe_redirect_file(shell_t *new, int i, int *pipe, char *path);
char *check_redirecion(shell_t *new, int *i);
char *choose_command(shell_t *new, int *i, char **envp);
int change_fdin(int *pipe_fd, shell_t *new);
char *get_the_command(shell_t *new);
void waitpid_and_error(pid_t pid, shell_t *new, char *command);
int opertor_builtin(char *command, shell_t *new
, char **envp, int i, int fd_in, int *pipe_fd);
void error_execve(char *command);
int string_is_operator(char *command);
int char_is_an_operator(char const *str, int *i, int mod);
int operator(char c);
int error_operator_command(char **str);
int non_sence_command(char *str);
int error_operator(char *str);
void wait_process(int *nbr, shell_t *new);
int skip_redirecion(shell_t *new, int *i);
int case_fork(int temp, int *pipe_fd, shell_t *new, char **envp);
int case_builtin(int *proc, shell_t *new, char **envp);
void globing(shell_t *tcsh);

#endif
