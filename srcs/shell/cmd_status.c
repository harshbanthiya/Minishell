/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 22:47:53 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/16 15:05:19 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Get command exit status.
 */
int	get_status(void)
{
	return (g_shell.status);
}

/*
 * Set command exit status.
 */
void	set_status(int status_value)
{
	g_shell.status = status_value;
}

int	set_status_and_ret(int status_value, int ret_value)
{
	g_shell.status = status_value;
	return (ret_value);
}
