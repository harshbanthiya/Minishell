/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 00:15:20 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/16 14:55:46 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ms_parse.h"
#include <stdlib.h>

void	parse_die(void)
{
	int	*nullpoint;

	nullpoint = NULL;
	nullpoint[0] = 0xD1E;
}

void	parse_skip_spaces(t_parse_buffer *buff, t_token *tok)
{
	while (1)
	{
		if (tok->type != TOKTYPE_SPACE)
			break ;
		scan_get_token(buff, tok);
	}
}

/* Fail Early, Fail Loudly */
void	parse_fatal_error(void)
{
	exit(1);
}
