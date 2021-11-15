/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:01:47 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:44:26 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


void	put_err_msg(char *str)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
}

