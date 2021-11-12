#ifndef SCANNER_H
#define SCANNER_H

enum e_token_type
{
    CHAR_GENERAL    = -1,
    CHAR_PIPE       = '|',
    CHAR_SQUOTE     = '\'',
    CHAR_DQUOTE     = '\"',
    CHAR_SEMICOLON  = ';',
    CHAR_WHITESPACE = ' ',
    CHAR_ESCAPESEQ  = '\\',
    CHAR_TAB        = '\t',
    CHAR_NEWLINE    = '\n',
    CHAR_GREATER    = '>',
    CHAR_LESSER     = '<',
    CHAR_HEREDOC    = -2,
    CHAR_DBLGRT     = -3,
    CHAR_NULL       = 0,
    TOKEN           = -1,
}t_token_type;

enum state 
{
    STATE_IN_DQUOTE,
    STATE_IN_SQUOTE,
    STATE_IN_ESCAPESEQ,
    STATE_GENERAL,
}t_state;

typedef struct token t_token;
typedef struct token_list t_token_list; 
struct token
{
    char            *data;
    int             type;
    struct token    *next;
};

struct  token_list
{
    t_token     *tokenlist;
    int         ntokens;
};

int     build_token_list(char *line, int size, t_token_list *token_buff);
void    destroy_token_list(t_token_list* tokbuf);
#endif 