#ifndef MYMAIN_H
#define MYMAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings which is called the environment */
extern char **environ;


/**
 * struct data - struct that
 * contains all relevant data on run-time..
 *
 * @av: argument vector,..
 *
 * @input: command line written by the user,..
 * @args: tokens of the command line,..
 *
 * @status: last status of the shell,..
 * @counter: lines counter,..
 *
 * @_environ: environment variable,..
 *
 * @pid: process ID of the shell,..
 */

typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 *
 * @separator: ; | &
 *
 * @next: next node,..
 *
 * Description: single linked list -  to store separators
 */

typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list,..
 *
 * @line: command line,..
 *
 * @next: next node,..
 *
 * Description: single linked list -  to store command lines
 */

typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked - list...
 *
 * @len_var: length of the variable,..
 *
 * @val: value of the variable,..
 *
 * @len_val: length of the value,..,.
 *
 * @next: next node in...
 *
 * Description: single linked list -  to store variables,..
 */

typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command argumentss.,.
 *
 * @name: The name of the command builtin i.e cd, exit, environ,,.
 *
 * @f: data type pointer function,...
 */

typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* a_list1.c */
sep_list *add_sep_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_node_end(line_list **head, char *line);
void free_line_list(line_list **head);

/* a_list2.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* a_str_1 functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* a_memory.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* a_str_2.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* a_str_3.c */
void rev_string(char *s);

/* inspect_stx_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);

/* mymain_loop.c */
char *without_comment(char *in);
void shell_loop(data_shell *datash);

/* read_str_line.c */
char *read_line(int *i_eof);

/* break.c */
char *swap_char(char *input, int bool);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

/* rep_allvar.c */
void check_env(r_var **h, char *in, data_shell *data);
int check_vars(r_var **h, char *in, char *st, data_shell *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, data_shell *datash);

/* get_str_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* prompt_exec_line */
int exec_line(data_shell *datash);

/* unix_cmd.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);

/* environs1.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

/* environs2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _setenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* cdir_shell_instance.c */
void cd_dot(data_shell *datash);
void cd_to(data_shell *datash);
void cd_previous(data_shell *datash);
void cd_to_home(data_shell *datash);

/* cdir_shell.c */
int cd_shell(data_shell *datash);

/* get_builtin_shell */
int (*get_builtin(char *cmd))(data_shell *datash);

/* gate_shell.c */
int exit_shell(data_shell *datash);

/* a_std_lib.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* a_err1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);

/* a_err2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(data_shell *datash);


/* get_err.c */
int get_error(data_shell *datash, int eval);

/* get_sig_int.c */
void get_sigint(int sig);

/* a_help1.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* a_help2.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* get_help_shell.c */
int get_help(data_shell *datash);

#endif /*END OF  MYMAIN_H FILE*/
