/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:42 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/05 18:02:43 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	is_nl(char *opt)
{
	int	i;

	i = 0;
	if (opt && opt[i] == '-')
	{
		i++;
		while (opt[i])
		{
			if (opt[i++] != 'n')
				return (0);
		} 
		return (1);
	}
	return (0);
}

int	ft_echo(t_cmd *cmd, t_dlist **lst)
{
	char	**args;
	int		nl;
	int		i;
	int		j;

	lst = NULL;
	args = &cmd->argv[1];
	nl = 1;
	i = 0;
	while (is_nl(args[i]))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		j = 0;
		ft_putstr_fd(args[i++], 1);
		if (args[i])
			ft_putstr_fd(" ", 1);
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
