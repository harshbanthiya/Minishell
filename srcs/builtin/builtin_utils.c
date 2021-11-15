/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:15:44 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 15:48:23 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

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

t_builtin_cmd	*get_builtin_func(char *cmd_name)
{
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(cmd_name, "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(cmd_name, "pwd") == 0)
		return (ft_pwd);
	if (ft_strcmp(cmd_name, "env") == 0)
		return (ft_env);
	if (ft_strcmp(cmd_name, "export") == 0)
		return (ft_export);
	if (ft_strcmp(cmd_name, "unset") == 0)
		return (ft_unset);
	if (ft_strcmp(cmd_name, "exit") == 0)
		return (ft_exit);
	return (NULL);
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
