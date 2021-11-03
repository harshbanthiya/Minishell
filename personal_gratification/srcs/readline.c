/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 08:05:03 by sucho             #+#    #+#             */
/*   Updated: 2021/02/01 00:26:34 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_char(char *org, char c)
{
	const int	l = ft_strlen(org);
	char *const	ret = ft_calloc(l + 2, 1);

	ft_memcpy(ret, org, l);
	ret[l] = c;
	ret[l + 1] = 0;
	if (org)
		free(org);
	return (ret);
}

void	ctrl_d_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

char	*readline(void)
{
	char	buf[1];
	char	*out;
	int		result;
	bool	ctrld;

	out = ft_calloc(1, sizeof(char));
	ctrld = true;
	while (ctrld)
	{
		ctrld = false;
		while ((result = read(0, buf, 1)) > 0)
		{
			if (*buf == '\n')
				break ;
			out = append_char(out, *buf);
		}
		if (!result)
		{
			if (!ft_strlen(out))
				ctrl_d_exit();
			else
				ft_putstr_fd("  \b\b", 1);
			ctrld = true;
		}
	}
	return (out);
}
