/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_shell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 22:22:08 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/08 23:12:20 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_invalid_input_str(char *input_str)
{
	while (*input_str)
	{
		if (*input_str & 0x80 || (unsigned char)*input_str > ' ')
			return (true);
		input_str++;
	}
	return (false);
}

void	show_parse_err(char *input_str)
{
	if (is_invalid_input_str(input_str))
	{
		put_err_msg("Parse error.");
		set_status(1);
	}
}
