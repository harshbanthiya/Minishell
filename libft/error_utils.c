/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:56:13 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 14:56:34 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_err_msg(char *str)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

int	put_err_msg_and_ret(char *str)
{
	put_err_msg(str);
	return (ERROR);
}

void	put_err_msg_and_exit(char *str)
{
	put_err_msg(str);
	exit(EXIT_FAILURE);
}
