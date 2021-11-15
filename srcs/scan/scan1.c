/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:02:51 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:43:15 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../../includes/ms_parse.h"
#include "../../libft/libft.h"

int	scan_getc(t_parse_buffer *buf)
{
	if (buf->getc)
		return (buf->getc(buf));
	if (buf->cur_pos == buf->size)
		return (EOF);
	return (buf->buffer[buf->cur_pos++]);
}

void	scan_ungetc(t_parse_buffer *buf)
{
	if (buf->ungetc)
	{
		buf->ungetc(buf);
		return ;
	}
	buf->cur_pos--;
}

int     scan_get_symbols(t_parse_buffer *buff, t_token *result, int ch)
{
    if (ch == ';')
        result->type = TOKTYPE_SEMICOLON;
    else if (ch == '|')
        result->type = TOKTYPE_PIPE;
    else if (ch == '<' || ch == '>')
        scan_get_lt_gt(buff, result, ch);
    else 
        return (0);
    return (1);
}

int     scan_get_quotes(t_parse_buffer *buff, t_token *result, int ch)
{
    if (buff->scan_state != SCANSTATE_NORMAL)
       parse_die();
    if (ch == '"')
    {
        buff->scan_state = SCANSTATE_DOUBLE_QUOTED;
        result->type = TOKTYPE_EXPANDABLE_QUOTED;
        return(scan_read_double_quotes(buff, result));
    }
    else if (ch == '\'')
    {
        buff->scan_state = SCANSTATE_SINGLE_QUOTED;
        result->type = TOKTYPE_NON_EXPANDABLE;
        return (scan_read_single_quotes(buff, result));
    }
    return (0);
}

int     scan_get_token(t_parse_buffer *buff, t_token *result)
{
    int     ch;

    if (buff->scan_state == SCANSTATE_NORMAL)
    {
        ch = scan_getc(buff);
        if (scan_get_spaces(buff, result, ch)
            || scan_get_symbols(buff, result, ch)
            || scan_get_quotes(buff, result, ch)
            || scan_get_eof(result, ch))
            return (1);
        result->type = TOKTYPE_EXPANDABLE;
        scan_ungetc(buff);
        return (scan_read_word(buff, result) 
                && (scan_check_redirection_with_fd(buff, result) || 1));
    }
    if (buff->scan_state == SCANSTATE_DOUBLE_QUOTED)
    {
        result->type = TOKTYPE_EXPANDABLE_QUOTED;
        return (scan_read_double_quotes(buff, result));
    }
    result->type = TOKTYPE_NON_EXPANDABLE;
    return (scan_read_single_quotes(buff, result));
}