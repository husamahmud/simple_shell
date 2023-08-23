#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;
char *name;
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin cmds.
 * @name: The name of the builtin cmd.
 * @f: A function pointer to the builtin cmd's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **f);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @val: The val of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *val;
	struct alias_s *next;
} alias_t;

alias_t *aliases;

/* input/output */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

/* signal hdlr */
void sig_hdlr(int sig);

/* memory management */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* strings */
char **_strtok(char *line, char *delim);
size_t _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_itos(int num);

/* path/cmd */
char *get_loc(char *cmd);
list_t *get_path_dir(char *path);
char *fill_path_dir(char *path);
int exec(char **args, char **f);

/* arg hdlr */
void hdl_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);
void var_repl(char **args, const int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **f, int *exe_ret);
int run_args(char **args, char **f, int *exe_ret);
int hdl_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **f);
char **repl_aliases(char **args);

/* built-in cmds */
int (*get_builtin(char *cmd))(char **args, char **f);
int hsh_exit(char **args, char **f);
int hsh_env(char **args, char __attribute__((unused)) **f);
int hsh_setenv(char **args, char __attribute__((unused)) **f);
int hsh_unsetenv(char **args, char __attribute__((unused)) **f);
int hsh_cd(char **args, char __attribute__((unused)) **f);
int hsh_alias(char **args, char __attribute__((unused)) **f);
int hsh_hlp(char **args, char __attribute__((unused)) **f);

/* environment cmds */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* err handling */
int create_err(char **args, int err);
char *err_env(char **args);
char *err_1(char **args);
char *err_2_exit(char **args);
char *err_2_cd(char **args);
char *err_2_syntax(char **args);
char *err_126(char **args);
char *err_127(char **args);

/* alias */
alias_t *add_alias_end(alias_t **h, char *name, char *val);
void free_alias_list(alias_t *h);

/* linked list */
list_t *add_node_end(list_t **h, char *dir);
void free_list(list_t *h);

/* hlp function */
void hlp_all(void);
void hlp_alias(void);
void hlp_cd(void);
void hlp_exit(void);
void hlp_hlp(void);
void hlp_env(void);
void hlp_setenv(void);
void hlp_unsetenv(void);

/* file process */
int proc_file_cmds(char *file_path, int *exe_ret);

#endif
