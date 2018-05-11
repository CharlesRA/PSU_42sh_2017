/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** PSU
*/

#ifndef SHELL_H
#define SHELL_H
#include <unistd.h>

enum OPERATOR {
	PIPE = 49,
	SEMICOLON,
	ONE_LEFT,
	TWO_LEFT,
	ONE_RIGHT,
	TWO_RIGHT,
	AND,
	OR,
};


typedef struct s_alias
{
	char *shortcut;
	char *value;
} alias_t;


typedef struct s_shell
{
	int return_value;
	int row;
	char **binaries;
	char *priority;
	char ***different_command;
	char *path;
	char *command;
	alias_t *alias;
} shell_t;


/*_____________________________PARSING________________________________________*/
char *path_to_binaries(char *envp[], shell_t *tcsh, char *command);
int check_lines_envp(char *envp);
int check_env(char **envp);
int find_correct_line_env(char **env, char *to_find);
char *path_to_binaries(char *envp[], shell_t *tcsh, char *command);

/*____________________________________________________________________________*/

/*____________________________WAIT_AND_ERROR__________________________________*/
void error_status(int wstatus, shell_t *tcsh, char *command);
void wait_process(int *nbr, shell_t *tcsh, char ***skip);
void error_execve(char *command);
void waitpid_and_error(pid_t pid, shell_t *tcsh, char *command);
int error_operator_command(char **str);
int non_sence_command(char *str);

/*____________________________________________________________________________*/


int loop(shell_t *tcsh, char **envp);
void error_command(char *message);
void destroy_array(shell_t *tcsh);
int priority_array(char *str, shell_t *tcsh);
char ***array_command(char **command);
int operator_pipe_redirect_file(shell_t *tcsh, int i, int *pipe, char *path);
char *choose_command(shell_t *tcsh, int *i, char **envp);
int change_fdin(int *pipe_fd, shell_t *tcsh);
char *get_the_command(shell_t *tcsh);
int opertor_builtin(char *command, shell_t *tcsh
, char **envp, int i, int fd_in, int *pipe_fd);
int string_is_operator(char *command);
int char_is_an_operator(char const *str, int *i, int mod);
int operator(char c);
int error_operator(char *str);
int skip_redirection(shell_t *tcsh, int *i);
int case_fork(int temp, int *pipe_fd, shell_t *tcsh, char **envp);
int case_builtin(int *proc, shell_t *tcsh, char **envp, char ***skip);
void str_to_word_binaries(char *str, shell_t *tcsh);
char *check_redirection(shell_t *tcsh, int *i);
char *check_alias(shell_t *tcsh);


#endif
