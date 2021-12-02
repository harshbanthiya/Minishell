/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:36 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/02 13:00:48 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/minishell.h"
#include "../../includes/ms_builtin.h"
#include "../../includes/ms_environment.h"
#include "../../libft/libft.h"
/*
static void	put_exit_errmsg_and_ret(char *exit_status)
{
	char	*tmp;

	tmp = ft_strjoin(exit_status, ": numeric argument required");
	check_malloc_success("exit", tmp);
	put_minish_err_msg_and_exit(255, "exit", tmp);
}
*/
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
	{
		g_shell.exit_flag = 255;
		return (put_minish_err_msg_and_ret(255, "exit",
						"numeric argument required"));
	}
	while (ft_isdigit(*nptr))
		num = num * 10 + (*nptr++ - '0');
	skip_whitespace(&nptr);
	if (*nptr)
	{
		g_shell.exit_flag = 255;
		return (put_minish_err_msg_and_ret(255, "exit",
								"numeric argument required"));
	}
	g_shell.exit_flag = ((sign * num) & 255);
	return (g_shell.exit_flag);
}

int	ft_exit(char **argv)
{
	int	argv_len;

	argv_len = ptrarr_len((void **)argv);
	if (argv_len >= 2 && !ft_isnum(argv[1]))
	{
		g_shell.exit_flag = 255;
		return (put_minish_err_msg_and_ret(255, "exit", 
							"numeric argument required"));
	}
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
