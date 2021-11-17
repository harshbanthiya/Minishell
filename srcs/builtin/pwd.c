/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:49 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 15:49:27 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

void	set_pwd(char *pwd)
{
	if (g_shell.pwd != NULL)
		ft_free(g_shell.pwd);
	g_shell.pwd = pwd;
}

char	*get_pwd(void)
{
	return (g_shell.pwd);
}

int	ft_pwd(char **argv)
{
	char	*pwd;

	if (argv[0])
	{
		error_builtin("pwd", NULL, "too many arguments");
		return (1);
	}
	pwd = get_pwd();
	if (pwd != NULL)
	{
		ft_putendl_fd(pwd, 1);
	}
	else
	{
		error_builtin("pwd", NULL, "pwd not declared");
		return (2);
	}
	return (0);
}
