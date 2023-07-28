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
int hsh(info_t *in, char **v);
int f_buil(info_t *in);
void fi_cm(info_t *in);
void for_cm(info_t *in);

/* toem_par.c */
int is_cm(info_t *in, char *p);
char *dup_ch(char *p, int st, int sp);
char *find_p(info_t *in, char *p, char *cm);

/* loophsh.c */
int loophsh(char **);

/* toem_er.c */
void _ep(char *s);
int _epc(char ca);
int _puf(char ca, int f);
int _pus(char *s, int f);

/* toem_str.c */
int _str(char *sa);
int strc(char *s1a, char *s2a);
char *s_w(const char *hay, const char *ne);
char *_strc(char *de, char *sr);

/* toem_string1.c */
char *_st(char *de, char *sr);
char *_strdu(const char *st);
void _pu(char *st);
int _puc(char ca);

/* toem_ex.c */
char *_st(char *d, char *sa, int na);
char *_strc(char *d, char *s, int na);
char *strch(char *sa, char ca);

/* toem_rec.c */
char *_mem(char *sa, char ba, unsigned int na);
void ffree(char **p);
void *_re(void *pt, unsigned int o_size, unsigned int n_size);

/* toem_memory.c */
int bfree(void **p);

/* to_at.c */
int inter(info_t *in);
int is_de(char ca, char *de);
int isalp(int ca);
int _at(char *sa);

/* toem_er1.c */
int _err(char *sa);
void p_err(info_t *in, char *es);
int p_d(int in, int f);
char *con_n(long int nu, int b, int f);
void re_co(char *b);

/* to_bu.c */
int mye(info_t *in);
int myc(info_t *in);
int myh(info_t *in);

/* toem_bu2.c */
int myhis(info_t *in);
int un_al(info_t *in, char *s);
int s_al(info_t *in, char *s);
int p_al(list_t *n);

/*toem_gl.c */
ssize_t i_bu(info_t *in, char **b, size_t *l);
ssize_t g_in(info_t *in);
ssize_t re_b(info_t *in, char *b, size_t *ia);
int _getl(info_t *in, char **p, size_t *l);
void sig(__attribute__((unused))int s_n);

/* toem_getinfo.c */
void cl_in(info_t *in);
void se_in(info_t *in, char **a);
void fr_in(info_t *in, int al);

/* toem_environ.c */
int myen(info_t *in);
char *gete(info_t *in, const char *na);
int mys(info_t *in);
int myu(info_t *in);
int popu(info_t *in);

/* toem_gev.c */
char **g_env(info_t *in);
int _uns(info_t *in, char *v);
int _set(info_t *in, char *v, char *val);

/* toem_his.c */
char *get_his_f(info_t *in);
int wr_his(info_t *in);
int re_his(info_t *in);
int b_his_l(info_t *in, char *b, int lin);
int ren_his(info_t *in);

/* toem_lists.c */
list_t *ad_no(list_t **h, const char *s, int n);
list_t *add_n(list_t **h, const char *s, int n);
size_t p_list_s(const list_t *ha);
int delete_node_at_index(list_t **h, unsigned int in);
void fr_li(list_t **h_ptr);

/* toem_lis1.c */
size_t lis_len(const list_t *ha);
char **l_to_s(list_t *h);
size_t pr_l(const list_t *ha);
list_t *node_starts_with(list_t *n, char *pre, char ca);
ssize_t get_node_index(list_t *h, list_t *n);

/* toem_vars.c */
int is_ch(info_t *in, char *bu, size_t *Pa);
void c_cha(info_t *in, char *bu, size_t *pa, size_t ia, size_t len);
int rep_al(info_t *in);
int rep_v(info_t *in);
int rep_str(char **o, char *n);

#endif
