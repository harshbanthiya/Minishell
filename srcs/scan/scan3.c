/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 00:47:33 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 11:29:13 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ms_parse.h"
#include <stdio.h>
#include "../../libft/libft.h"

int	scan_check_redirection_with_fd(t_parse_buffer *buff, t_token *result)
{
	int 	i;
	int 	ch;
	int 	fd;

	i = 0;
	while (i < result->length)
	{
		if (!ft_isdigit(result->text[i]))
			return (0);
		i++;
	}	
	result->text[i] = '\0';
	ch = scan_getc(buff);
	if ((ch == '<' || ch == '>') && !is_int_overflow(result->text, 1))
	{
		fd = ft_atoi(result->text);
		scan_get_symbols(buff, result, ch);
		result->length = fd;
	}
	else 
		scan_ungetc(buff);
	return (1);
}

int	scan_escaped(t_parse_buffer *buf, t_token *result)
{
	char	ch;

	ch = scan_getc(buf);
	if (ch == '\\')
	{
		ch = scan_getc(buf);
		if (ch != '\n'
			&& (buf->scan_state == SCANSTATE_NORMAL
				|| (buf->scan_state == SCANSTATE_DOUBLE_QUOTED
					&& ft_strchr("$\"\'\\`", ch))))
		{
			result->text[0] = ch;
			result->length = 1;
			result->type = TOKTYPE_NON_EXPANDABLE;
			return (1);
		}
		scan_ungetc(buf);
		result->text[0] = '\\';
		result->length = 1;
		result->type = TOKTYPE_NON_EXPANDABLE;
		return (1);
	}
	scan_ungetc(buf);
	return (0);
}

int		scan_get_eof(t_token *result, int ch)
{
	if (ch == EOF)
	{
		result->type = TOKTYPE_EOF;
		return (1);
	}
	return (0);
}

int     scan_init_token(t_token *result)
{
    result->max_length = 1024;
    result->text = malloc(result->max_length);
    if (!result->text)
    {
        printf("malloc token buffer failed");
        exit(1);
    }
    result->length = 0;
    result->type = TOKTYPE_PARSE_ERROR;
    return (0);
}

int 	scan_expand_text_buffer(t_token *result)
{
	char 	*old_text;

	old_text = result->text;
	result->text = malloc(result->max_length * 2);
	if (!result->text)
	{
		printf("exapnd token buffer failed\n");
		exit(1);
	}
	ft_memcpy(result->text, old_text, result->max_length);
	result->max_length = result->max_length * 2;
	free(old_text);
	return (0);
}