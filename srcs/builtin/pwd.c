/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:49 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/02 16:45:14 by hbanthiy         ###   ########.fr       */
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

	if (argv[1])
		return (error_builtin("pwd", NULL, "too many arguments", 1));
	pwd = get_pwd();
	if (pwd != NULL)
		ft_putendl_fd(pwd, 1);
	else
		return (error_builtin("pwd", NULL, "pwd not declared", 2));
	return (0);
}
