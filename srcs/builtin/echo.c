/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:42 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/16 11:29:42 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

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

int	ft_echo(char **argv)
{
	int		nl;
	int		i;
	int		j;

	nl = 1;
	i = 0;
	while (is_nl(argv[i]))
	{
		nl = 0;
		i++;
	}
	while (argv[i])
	{
		j = 0;
		ft_putstr_fd(argv[i++], 1);
		if (argv[i])
			ft_putstr_fd(" ", 1);
	}
	if (nl)
		ft_putstr_fd("\n", 1);
	return (0);
}
