/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:36 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/03 09:48:34 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/minishell.h"
#include "../../includes/ms_builtin.h"
#include "../../includes/ms_environment.h"
#include "../../libft/libft.h"

static int	put_exit_errmsg_and_ret(int err_code)
{
	g_shell.exit_flag = err_code;
	return (put_minish_err_msg_and_ret(err_code, "exit",
			"numeric argument required"));
}

void	skip_whitespace(char **nptr)
{
	while (**nptr == ' ' || **nptr == '\t' || **nptr == '\f'
		|| **nptr == '\r' || **nptr == '\n' || **nptr == '\v')
		(*nptr)++;
}

static int	exit_atol(char *str)
{
	char	*nptr;
	long	num;
	int		sign;

	nptr = str;
	sign = 1;
	num = 0;
	skip_whitespace(&nptr);
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!ft_isdigit(*nptr) || is_long_overflow(nptr, sign))
		return (put_exit_errmsg_and_ret(255));
	while (ft_isdigit(*nptr))
		num = num * 10 + (*nptr++ - '0');
	skip_whitespace(&nptr);
	if (*nptr)
		return (put_exit_errmsg_and_ret(255));
	g_shell.exit_flag = ((sign * num) & 255);
	return (g_shell.exit_flag);
}

int	ft_exit(char **argv)
{
	int	argv_len;

	argv_len = ptrarr_len((void **)argv);
	if (argv_len >= 2 && !ft_isnum(argv[1]))
		return (put_exit_errmsg_and_ret(255));
	if (argv_len > 2)
	{
		g_shell.exit_flag = 1;
		return (put_minish_err_msg_and_ret(1, "exit", "too many arguments"));
	}
	else if (argv_len == 2)
		return (exit_atol(argv[1]));
	else
		g_shell.exit_flag = g_shell.status;
	return (0);
}
