#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* pointer to pointer of strings named "environment" */
extern char **environ;

/**
 * struct data - struct of fundamental runtime data
 * @av: argument vector
 * @input: command from user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
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
} core_data;

/**
 * struct sep_list_s - singly linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct node_list_s - singly linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct node_list_s
{
	char *line;
	struct node_list_s *next;
} node_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(core_data *crdata);
} builtin_t;

/* list_operations.c */
sep_list *add_new_node_end(sep_list **head, char sep);
void free_sep_list(sep_list **head);
node_list *add_line_node_end(node_list **head, char *line);
void free_node_list(node_list **head);

/* list_operations_0.c */
r_var *add_rvar_node(r_var **head, int lvar, char *var, int lval);
void free_rvar_list(r_var **head);

/* string_functions */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* memory.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* string_manipulation.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* string_reverse.c */
void string_reverse(char *s);

/* if_syntax_error.c */
int repeated_char(char *input, int i);
int error_sep_op(char *input, int i, char last);
int first_char(char *input, int *i);
void print_syntax_error(core_data *crdata, char *input, int i, int bool);
int if_syntax_error(core_data *crdata, char *input);

/* run_shell.c */
char *trim_comment(char *str_in);
void run_shell(core_data *crdata);

/* read_stdin_line.c */
char *read_stdin_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int bool);
void add_new_nodes(sep_list **head_s, node_list **head_l, char *input);
void go_next(sep_list **list_s, node_list **list_l, core_data *crdata);
int split_commands(core_data *crdata, char *input);
char **tokenize(char *input);

/* rep_var.c */
void check_env(r_var **h, char *in, core_data *data);
int check_vars(r_var **h, char *in, char *st, core_data *data);
char *replaced_input(r_var **head, char *input, char *new_input, int nlen);
char *rep_var(char *input, core_data *crdata);

/*input_handling.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* classify_command */
int classify_command(core_data *crdata);

/* execute_commands.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(core_data *crdata);
int check_error_cmd(char *dir, core_data *crdata);
int execute_commands(core_data *crdata);

/* env_vars.c */
char *_getenv(const char *name, char **_environ);
int _env(core_data *crdata);

/* env_var_setters.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, core_data *crdata);
int _setenv(core_data *crdata);
int _unsetenv(core_data *crdata);

/* ch_dir0.c */
void cd_dot(core_data *crdata);
void cd_to(core_data *crdata);
void cd_previous(core_data *crdata);
void cd_to_home(core_data *crdata);

/* ch_dir.c */
int ch_dir(core_data *crdata);

/* fetch_builtin */
int (*fetch_builtin(char *cmd))(core_data *crdata);

/* exit_shell.c */
int is_valid_integer(char *str);
int exit_shell(core_data *crdata);

/* num_utils.c */
int get_len(int n);
char *aux_itoa(int n);
int _atoi(char *s);

/* error_handling.c */
char *strcat_cd(core_data *, char *, char *, char *);
char *error_get_cd(core_data *crdata);
char *error_not_found(core_data *crdata);
char *error_exit_shell(core_data *crdata);

/* error_handling0.c */
char *error_get_alias(char **args);
char *error_env(core_data *crdata);
char *error_syntax(char **args);
char *error_permission(char **args);
char *error_path_126(core_data *crdata);

/* catch_error.c */
int catch_error(core_data *crdata, int eval);

/* get_sigint.c */
void get_sigint(int signal_num);

/* help_functions.c */
void aux_help_env(void);
void aux_help_setenv(void);
void aux_help_unsetenv(void);
void aux_help_general(void);
void aux_help_exit(void);

/* help_functions0.c */
void aux_help(void);
void aux_help_alias(void);
void aux_help_cd(void);

/* give_help.c */
int give_help(core_data *crdata);

#endif

