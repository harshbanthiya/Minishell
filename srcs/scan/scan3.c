/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 00:47:33 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/09 02:18:42 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"

int     scan_escaped(t_parse_buffer *buff, t_token *result)
{
    char    ch;
    
    ch = scan_getc(buff);
    if (ch == '\\')
    {
        ch = scan_getc(buff);
        if (ch != '\n' 
            && (buff->scan_state == SCANSTATE_NORMAL 
                || (buff->scan_state == SCANSTATE_DOUBLE_QUOTED 
                    && ft_strchr("$\"\'\\`", ch))))
        {
            result->text[0] = ch;
            result->length = 1;
            result->type = TOKTYPE_NON_EXPANDABLE;
            return (1);
        }
        scan_ungetc(buff);
        result->text[0] = '\\';
        result->length = 1;
        result->type = TOKTYPE_NON_EXPANDABLE;
        return (1);
    }
    scan_ungetc(buff);
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