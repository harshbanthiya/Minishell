#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include <fcntl.h>


/* Globals and constants made for ease of testing remove later */
list    *global_current_token_node;
int     *global_pipe_pid;
int     global_pipe_index;
int     global_pipe_test;
int     global_exit_code;

#define STRING 1
#define EXIT_FAIL 1
#define EXIT_SUCCESS 0
#define SPACE 32
#define SEMICOLON 58
#define LESS 60
#define PIPE 124
#define SQUOTE 39
#define DQUOTE 34
#define BACKSLASH 92 
#define BUFF_SIZE 4096


typedef struct tree_node
{
  int           type;
  char          *data;
  tree_node     *left_child;
  tree_node     *right_child;
} tree_node;

typedef enum type
{
  NODE_PIPE = 100,
  NODE_REDIRECT_IN,
  NODE_REDIRECT_OUT,
  NODE_CMDPATH,
  NODE_ARGUMENT,
  NODE_REDIRECT_DOUBLEOUT,
  NODE_REDIRECT_DOUBLEIN,
  NODE_DATA,
  NODE_SEQ,
} node_type;

typedef struct token
{
  char      type;
  char      *data;
  token     *next;
} token;

typedef struct  scan_quote
{
    int     s_quote;
    int     d_quote;
}scan_quote;

typedef struct  env_kv_pair
{
    char    *key;
    char    *val;
}env_kv_pair;

typedef struct  pipe
{
    bool    stdin_pipe;
    bool    stdout_pipe;
    int     read_pipe;
    int     write_pipe;
}ppipe;

typedef struct  cmd
{
    int         argc;
    int         has_path;
    char        **argv;
    ppipe        *pipe;
    tree_node   *redir;
}cmd;

/* T list from libft for env linked list and other temp linked lists, point the void pointer to env (kv pair)*/
typedef struct list
{
   void     *content;
   list     *next;
}list;

#endif