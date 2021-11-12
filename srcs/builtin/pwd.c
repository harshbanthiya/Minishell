/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:49 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/12 14:41:56 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

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

int	ft_pwd(char **argv, t_dlist **lst)
{
	char	*pwd;

	lst = NULL;
	if (argv[0])
	{
		error_builtin("pwd", NULL, "too many arguments");
		return (2);
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
