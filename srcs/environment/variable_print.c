/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:01:18 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/18 16:07:31 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

void	print_var(int fd, t_var *var)
{
	if (var->key != NULL && var->value != NULL)
	{
		ft_putstr_fd(var->key, fd);
		ft_putchar_fd('=', fd);
		ft_putstr_fd(var->value, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	print_var_extra(int fd, t_var *var)
{
	if (var->key != NULL)
	{
		// ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(var->key, fd);
		if (var->value != NULL)
		{
			ft_putchar_fd('=', fd);
			ft_putchar_fd('\"', fd);
			ft_putstr_fd(var->value, fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
	}
}
