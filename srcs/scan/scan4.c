/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 01:20:39 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/16 14:51:53 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/ms_parse.h"

void	scan_get_lt_gt(t_parse_buffer *buff, t_token *result, int ch)
{
	if (ch == '<')
	{
		ch = scan_getc(buff);
		if (ch == '<')
			result->type = TOKTYPE_HEREDOCUMENT;
		else
		{
			scan_ungetc(buff);
			result->type = TOKTYPE_INPUT_REDIRECTION;
		}
		result->length = 0;
	}
	else
	{
		ch = scan_getc(buff);
		if (ch == '>')
			result->type = TOKTYPE_OUTPUT_APPENDING;
		else
		{
			result->type = TOKTYPE_OUTPUT_REDIRECTION;
			if (ch != EOF)
				scan_ungetc(buff);
		}
		result->length = 1;
	}
}
