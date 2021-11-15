/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:15:44 by sfournie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/15 13:13:46 by hbanthiy         ###   ########.fr       */
=======
/*   Updated: 2021/11/15 13:47:47 by sfournie         ###   ########.fr       */
>>>>>>> b989a1e3d66853e445a35926e61acde717994af0
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	is_builtin(char *name)
{
	if (name)
		return (0);
	if (!ft_strcmp(name, "export"))
		return (1);
	else if (!ft_strcmp(name, "unset"))
		return (1);
	else if (!ft_strcmp(name, "echo"))
		return (1);
	else if (!ft_strcmp(name, "env"))
		return (1);
	else if (!ft_strcmp(name, "exit"))
		return (1);
	else if (!ft_strcmp(name, "cd"))
		return (1);
	else if (!ft_strcmp(name, "pwd"))
		return (1);
	return (0);
}

void	error_builtin(char *builtname, char *str, char *msg)
{
	ft_putstr_fd("minishell", 2);
	if (builtname != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(builtname, 2);
	}
	if (str != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("\'", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\'", 2);
	}
	if (msg != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(msg, 2);
	}
}
