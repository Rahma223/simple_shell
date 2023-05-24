#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} lis_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	lis_t *env;
	lis_t *history;
	lis_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} i_tt;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/* toem_error.c */
void put_t(char *);
int put_ch(char);
int put_fd(char s, int fd);
int put_str(char *ss, int fd);

/* toem_exits.c */
char *str_cp(char *, char *, int);
char *str_ca(char *, char *, int);
char *str_ch(char *, char);

/* toem_atoi.c */
int inter(i_tt *);
int is_d(char, char *);
int is_alph(int);
int atoi_t(char *);

/* toem_error2.c */
int err_t(char *);
void print_e(i_tt *, char *);
int print_dd(int, int);
char *conv_num(long int, int, int);
void rem_c(char *);

/* toem_bil.c */
int exit_t(i_tt *);
int cd_t(i_tt *);
int help_t(i_tt *);

/* toem_bil2.c */
int hist_t(i_tt *i);
int uns(i_tt *i, char *);
int set_t(i_tt *i, char *);
int print_t(lis_t *n);
int ali(i_tt *i);

/* toem_environ.c */
char *get_env(i_tt *, const char *);
int env_t(i_tt *);
int set_env(i_tt *);
int unset_env(i_tt *);
int pop_env(i_tt *);

#endif

