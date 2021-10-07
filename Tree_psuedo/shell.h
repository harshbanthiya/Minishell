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

typedef struct tree_node
{
  int           type;
  char          *data;
  tree_node     *left_child;
  tree_node     *right_child;
} tree_node;

typedef enum type
{
  NODE_PIPE = 0,
  NODE_REDIRECT_IN = 6,
  NODE_REDIRECT_OUT = 8,
  NODE_CMDPATH = 10,
  NODE_ARGUMENT = 12,
  NODE_DATA = 14,
} node_type;

typedef struct token
{
  char      type;
  char      *data;
  token     *next;
} token;

typedef enum token_type
{
 CHAR_GENERAL = -1,
 CHAR_PIPE  = '|',
 CHAR_AND   = '&',
 CHAR_QUOTE = '\'',
 CHAR_DQUOTE = '\"',
 CHAR_WHITESPC = ' ',
 CHAR_SEMICOLON = ';',
 CHAR_TAB = '\t',
 CHAR_ESCAPE = '\\',
 CHAR_NEWLINE = '\n',
 CHAR_GREATER = '>',
 CHAR_LESS   = '<',
 CHARL_NULL = 0,
 TOKEN_NULL = -1,
}token_type;



struct command
{
    simple_cmd *cmd;
    redirection *rd;
    
}

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
}pipe;

typedef struct  cmd
{
    int         argc;
    int         has_path;
    char        **argv;
    pipe        *pipe;
    tree_node   *redir;
}cmd;

/* T list from libft for env linked list and other temp linked lists, point the void pointer to env (kv pair)*/
typedef struct list
{
   void     *content;
   list     *next;
}list;

#endif