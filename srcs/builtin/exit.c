/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:36 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/27 17:06:14 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../../includes/minishell.h"
#include "../../includes/ms_builtin.h"
#include "../../includes/ms_environment.h"
#include "../../libft/libft.h"

static void	put_exit_errmsg_and_exit(char *exit_status)
{
	char	*tmp;

	tmp = ft_strjoin(exit_status, ": numeric argument required");
	check_malloc_success("exit", tmp);
	put_minish_err_msg_and_exit(255, "exit", tmp);
}

static void	exit_atol(char *str)
{
	char	*nptr;
	long	num;
	int		sign;

	nptr = str;
	sign = 1;
	num = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f'
		|| *nptr == '\r' || *nptr == '\n' || *nptr == '\v')
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!ft_isdigit(*nptr) || is_long_overflow(nptr, sign))
		put_exit_errmsg_and_exit(str);
	while (ft_isdigit(*nptr))
		num = num * 10 + (*nptr++ - '0');
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f'
		|| *nptr == '\r' || *nptr == '\n' || *nptr == '\v')
		nptr++;
	if (*nptr)
		put_exit_errmsg_and_exit(str);
	exit((sign * num) & 255);
}

int	ft_exit(char **argv)
{
	int	argv_len;

	argv_len = ptrarr_len((void **)argv);
	if (argv_len >= 2 && !ft_isnum(argv[1]))
	{
		put_exit_errmsg_and_exit(argv[1]);
		return (255);
	}
	if (argv_len > 2)
		return (put_minish_err_msg_and_ret(1, "exit", "too many arguments"));
	else if (argv_len == 2)
	{
		parse_free_all_ast();
		free_shell();
		exit_atol(argv[1]);
	}	
	else
	{
		parse_free_all_ast();
		free_shell();
		exit(g_shell.status);
	}
	return (0);
}
