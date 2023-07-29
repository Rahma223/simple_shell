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
} list_t;

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
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int f_buil(info_t *);
void fi_cm(info_t *);
void for_cm(info_t *);

/* toem_par.c */
int is_cm(info_t *, char *);
char *dup_ch(char *, int, int);
char *find_p(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_er.c */
void _ep(char *);
int _epc(char);
int _puf(char, int);
int _pus(char *, int);

/* toem_str.c */
int _str(char *);
int strc(char *, char *);
char *s_w(const char *, const char *);
char *_strc(char *, char *);

/* toem_string1.c */
char *_st(char *, char *);
char *_strdu(const char *);
void _pu(char *);
int _puc(char);

/* toem_ex.c */
char *_stn(char *, char *, int);
char *_strnc(char *, char *, int);
char *strch(char *, char);

/* toem_rec.c */
char *_mem(char *, char, unsigned int);
void ffree(char **);
void *_re(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* to_at.c */
int inter(info_t *);
int is_de(char, char *);
int isalp(int);
int _at(char *);

/* toem_er1.c */
int _err(char *);
void p_err(info_t *, char *);
int p_d(int, int);
char *con_n(long int, int, int);
void re_co(char *);

/* to_bu.c */
int mye(info_t *);
int myc(info_t *);
int myh(info_t *);

/* toem_bu2.c */
int myhis(info_t *);
int un_al(info_t *, char *);
int s_al(info_t *, char *);
int p_al(list_t *);

/*toem_gl.c */
ssize_t i_bu(info_t *, char **, size_t *);
ssize_t g_in(info_t *);
ssize_t re_b(info_t *, char *, size_t *);
int _getl(info_t *, char **, size_t *);
void sig(__attribute__((unused))int);

/* toem_getinfo.c */
void cl_in(info_t *);
void se_in(info_t *, char **);
void fr_in(info_t *, int);

/* toem_environ.c */
int myen(info_t *);
char *gete(info_t *, const char *);
int mys(info_t *);
int myu(info_t *);
int popu(info_t *);

/* toem_gev.c */
char **g_env(info_t *);
int _uns(info_t *, char *);
int _set(info_t *, char *, char *);

/* toem_his.c */
char *get_his_f(info_t *);
int wr_his(info_t *);
int re_his(info_t *);
int b_his_l(info_t *, char *, int);
int ren_his(info_t *);

/* toem_lists.c */
list_t *ad_no(list_t **, const char *, int);
list_t *add_n(list_t **, const char *, int);
size_t p_list_s(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void fr_li(list_t **);

/* toem_lis1.c */
size_t lis_len(const list_t *);
char **l_to_s(list_t *);
size_t pr_l(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* toem_vars.c */
int is_ch(info_t *, char *, size_t *);
void c_cha(info_t *, char *, size_t *, size_t, size_t);
int rep_al(info_t *);
int rep_v(info_t *);
int rep_str(char **, char *);

#endif
