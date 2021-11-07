#include <glob.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"

void    token_init(t_token *tok, int datasize)
{
    tok->data = malloc(datasize + 1);
    tok->data[0] = 0;
    tok->type = CHAR_NULL;
    tok->next = NULL;
}

int     getchartype(char c)
{
    if (c == '\'')
        return (CHAR_SQUOTE);
    else if (c == '\"')
        return (CHAR_DQUOTE);
    else if (c == '|')
        return (CHAR_PIPE);
    else if (c == ' ')
        return (CHAR_WHITESPACE);
    else if (c == ';')
        return (CHAR_SEMICOLON);
    else if (c == '\\')
        return (CHAR_ESCAPESEQ);
    else if (c == '\t')
        return (CHAR_TAB);
    else if (c == '\n')
        return (CHAR_NEWLINE);
    else if (c == '>')
        return (CHAR_GREATER);
    else if (c == '<')
        return (CHAR_LESSER);
    else if (c == 0)
        return (CHAR_NULL);
    else 
        return (CHAR_GENERAL);
}

void    strip_quotes(char *src, char *dest)
{
    int     n;
    int     i;
    int     j;
    char    lastquote;
    char    c;

    n = strlen(src);
    if (n <= 1)
    {
        strcpy(dest, src);
        return ;
    }
    i = 0;
    j = 0;
    lastquote = 0;
    while (i < n)
    {
        c = src[i];
        if ((c == '\'' || c == '\"') && lastquote == 0) 
            lastquote = c;
        else if (c == lastquote)
            lastquote = 0;
        else 
            dest[j++] = c;
    }
    dest[j] = 0;
}

int build_token_list(char *line, int size, t_token_list *token_buff)
{
    t_token     *token;
    int         i;
    int         j;
    int         k;
    int         ntmp_tok;
    int         state;
    char        c;
    int         ch_type;

    if (token_buff == NULL)
        return (-1);
    if (size == 0)
    {
        token_buff->ntokens = 0;
        return (0);
    }
    token = token_buff->tokenlist;
    token_init(token, size);
    i = 0;
    j = 0;
    ntmp_tok = 0;
    state = STATE_GENERAL;
    c = line[i];
    while (c != '\0')
    {
        c = line[i];
        ch_type = getchartype(c);
        if (state == STATE_GENERAL)
        {
            if (ch_type == CHAR_SQUOTE)
            {
                state = STATE_IN_SQUOTE;
                token->data[j++] = CHAR_SQUOTE;
                token->type = TOKEN;
            }
            if (ch_type == CHAR_DQUOTE)
            {
                state = STATE_IN_DQUOTE;
                token->data[j++] = CHAR_DQUOTE;
                token->type = TOKEN;
            }
            if (ch_type == CHAR_ESCAPESEQ)
            {
                token->data[j++] = line[++i];
                token->type = TOKEN;
            }
            if (ch_type == CHAR_GENERAL)
            {
                token->data[j++] = c;
                token->type = TOKEN;
            }
            if (ch_type == CHAR_SEMICOLON || ch_type == CHAR_GREATER || ch_type == CHAR_LESSER || ch_type == CHAR_PIPE)
            {
                if (j > 0)
                {
                    token->data[j] = 0;
                    token->next = malloc(sizeof(t_token));
                    token = token->next;
                    token_init(token, size - i);
                    j = 0;
                }

                if (ch_type == CHAR_LESSER && (getchartype(line[i + 1])) == CHAR_LESSER)
                {
                    ch_type = CHAR_HEREDOC;
                    token->data[0] = CHAR_LESSER;
                    token->data[1] = CHAR_LESSER;
                    token->data[2] = 0;
                    token->type = ch_type;
                    i++;
                }
                if (ch_type == CHAR_GREATER && (getchartype(line[i + 1])) == CHAR_GREATER)
                {
                    ch_type = CHAR_DBLGRT;
                    token->data[0] = CHAR_GREATER;
                    token->data[1] = CHAR_GREATER;
                    token->data[2] = 0;
                    token->type = ch_type;
                    i++;
                }
                else 
                {
                    token->data[0] = ch_type;
                    token->data[1] = 0;
                    token->type = ch_type;
                }

                token->next = malloc(sizeof(t_token));
                token = token->next;
                token_init(token, size - i);
            }
        }
        else if (state == STATE_IN_DQUOTE)
        {
            token->data[j++] = c;
            if (ch_type == CHAR_DQUOTE)
                state = STATE_GENERAL;
        }
        else if (state == STATE_IN_SQUOTE)
        {
            token->data[j++] = c;
            if (ch_type == CHAR_SQUOTE)
                state = STATE_GENERAL;
        }
        if (ch_type == CHAR_NULL)
        {
            if (j > 0)
            {
                token->data[j] = 0;
                ntmp_tok++;
                j = 0;
            }
        }
        i++;
    }
    token = token_buff->tokenlist;
    k  = 0;
    while (token != NULL)
    {
        if (token->type == TOKEN)
        {
            glob_t globbuf;
            glob(token->data, GLOB_TILDE, NULL, &globbuf);
            if (globbuf.gl_pathc > 0)
            {
                k += globbuf.gl_pathc;
                t_token *saved = token->next; // save the next token to attach later
                free(token->data); // replace current token with the first one
                token->data = malloc(strlen(globbuf.gl_pathv[0]) + 1);
                strcpy(token->data, globbuf.gl_pathv[0]);

                i = 1;
                while(i < globbuf.gl_pathc)
                {
                    token->next = malloc(sizeof(t_token));
                    token_init(token->next, strlen(globbuf.gl_pathv[i]));
                    token = token->next;
                    token->type = TOKEN;
                    strcpy(token->data, globbuf.gl_pathv[i]);
                    i++;
                }
                token->next = saved;
            }
            else 
            {
                // token might be inside quotation marks or escape characters strip the quotes
                char    *stripped = malloc(strlen(token->data) + 1);
                strip_quotes(token->data, stripped);
                free(token->data);
                token->data = stripped;
                k++;
            }
        }
        token = token->next;
    }
    token_buff->ntokens = k;
    return (k);
}

void tok_destroy(t_token* tok) 
{
	if (tok != NULL) {
		free(tok->data);
		tok_destroy(tok->next);
		free(tok);
	}
}

void destroy_token_list(t_token_list* tokbuf)
{
	if (tokbuf == NULL)
		return;
	tok_destroy(tokbuf->tokenlist);
}
