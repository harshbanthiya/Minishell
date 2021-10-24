/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:42 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/24 16:01:41 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	is_nl(char *opt)
{
	if (opt && opt[0] == '-' && opt[1] == 'n')
		return (1);
	return (0);
}

int	ft_echo(char **tokens, int fd)
{
	int		nl;
	int		i;
	int		j;

	if (tokens == NULL)
		return (0);
	nl = 1;
	i = 0;
	while (is_nl(tokens[i]))
	{
		nl = 0;
		i++;
	}
	while (tokens[i])
	{
		j = 0;
		ft_putstr_fd(tokens[i++], fd);
		if (tokens[i])
			ft_putstr_fd(" ", fd);
	}
	if (nl)
		ft_putstr_fd("\n", fd);
	return (1);
}
