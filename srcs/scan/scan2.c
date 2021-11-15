/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:10:10 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:43:24 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ms_parse.h"
#include <stdio.h>

int     scan_is_special_char(char ch)
{
    if (ch == ' ' || ch == '\t' || ch == '\n' || ch == ';'
        || ch == '|' || ch == '>' || ch == '<' || ch == '"' || ch == '\'')
        return (1);
    return (0);
}

int     scan_read_word(t_parse_buffer *buff, t_token *result)
{
    int     pos;
    int     ch;
    
    if (scan_escaped(buff, result))
        return (1);
    pos = 0;
    while (1)
    {
        ch = scan_getc(buff);
        if (ch == EOF)
            break ;
        if (ch == '\\' || scan_is_special_char(ch) || (ch == '$' && pos > 0))
        {
            scan_ungetc(buff);
            break;
        }
        result->text[pos++] = ch;
        if (pos == result->max_length)
            scan_expand_text_buffer(result);
    }
    result->length = pos;
    return (1);
}

int     scan_read_double_quotes(t_parse_buffer *buff, t_token *result)
{
    int     pos;
    int     ch;

    if (scan_escaped(buff, result))
        return (1);
    pos = 0;
    while (1)
    {
        ch = scan_getc(buff);
        if (ch == '"' || ch == '\n' || ch == EOF)
            buff->scan_state = SCANSTATE_NORMAL;
        if (ch == '\n' || ch == EOF)
            result->type = TOKTYPE_PARSE_ERROR;
        if (ch == '\\' || ch == '\n' || ch == EOF || (ch == '$' && pos > 0))
            scan_ungetc(buff);
        if (ch == '\\' || ch == '"' || ch == '\n' || ch == EOF 
            || (ch == '$' && pos > 0))
            break ;
        result->text[pos++] = ch;
        if (pos == result->max_length)
            scan_expand_text_buffer(result);
    }
    result->length = pos;
    return (1);
}

int     scan_read_single_quotes(t_parse_buffer *buff, t_token *result)
{
    int     pos;
    int     ch;

    pos = 0;
    while (1)
    {
        ch = scan_getc(buff);
        if (ch == '\'' || ch == '\n' || ch == EOF)
            buff->scan_state = SCANSTATE_NORMAL;
        if (ch == '\n' || ch == EOF)
        {
            result->type = TOKTYPE_PARSE_ERROR;
            scan_ungetc(buff);
        }
        if (ch == '\'' || ch == '\n' || ch == EOF)
            break ;
        result->text[pos++] = ch;
        if (pos == result->max_length)
            scan_expand_text_buffer(result);
    }
    result->length = pos;
    return (1);
}


int     scan_get_spaces(t_parse_buffer *buff, t_token *result, int ch)
{
    if (ch == ' ' || ch == '\t')
    {
        while (1)
        {
            ch = scan_getc(buff);
            if (ch != ' ' && ch != '\t')
            {
                if (ch != EOF)
                    scan_ungetc(buff);
                result->type = TOKTYPE_SPACE;
                break ;
            }
        }
        return (1);
    }
    else if (ch == '\n')
    {
        result->type = TOKTYPE_NEWLINE;
        return (1);
    }
    return (0);
}