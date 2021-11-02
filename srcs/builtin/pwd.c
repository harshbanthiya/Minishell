/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:49 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/02 17:00:38 by sfournie         ###   ########.fr       */
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

int	ft_pwd(t_cmd *cmd, t_dlist **lst)
{
	char	*pwd;

	lst = NULL;
	if (cmd->argv[1])
		return (-1);
	pwd = get_pwd();
	if (pwd != NULL)
		ft_putendl_fd(pwd, 1);
	return (0);
}
