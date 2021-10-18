/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:42 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/18 16:22:08 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	is_nl(char *opt)
{
	if (opt && opt[0] == '-' && opt[1] == 'n')
		return (1);
	return (0);
}

int	ft_echo(char *str, int fd)
{
	char	**split;
	int		nl;
	int		i;
	int		j;

	split = ft_split(str, ' ');
	if (split == NULL)
		return (0);
	nl = 1;
	i = 0;
	while (is_nl(split[i]))
	{
		nl = 0;
		i++;
	}
	while (split[i])
	{
		j = 0;
		ft_putstr_fd(split[i++], fd);
		if (split[i])
			ft_putstr_fd(" ", fd);
	}
	if (nl)
		ft_putstr_fd("\n", fd);
	return (1);
}
