/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:18:04 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/31 23:48:21 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_echo_no_argv(void)
{
	ft_putstr_fd("\n", 1);
	return (EXIT_SUCCESS);
}

static int	exec_echo_only_n_opt(void)
{
	ft_putstr_fd("", 1);
	return (EXIT_SUCCESS);
}

int			exec_echo(t_cmd *cmd)
{
	int idx;
	int n_opt;
	int	exit_status;

	n_opt = FALSE;
	idx = 1;
	if (cmd->argc == 1)
		return (exit_status = exec_echo_no_argv());
	if (ft_strncmp(cmd->argv[idx], "-n", 3) == 0)
	{
		if (cmd->argc == 2)
			return (exit_status = exec_echo_only_n_opt());
		n_opt = TRUE;
		idx++;
	}
	while (idx < cmd->argc)
	{
		ft_putstr_fd(cmd->argv[idx], 1);
		if ((idx + 1) < cmd->argc)
			ft_putstr_fd(" ", 1);
		idx++;
	}
	if (!n_opt)
		ft_putstr_fd("\n", 1);
	return (exit_status = EXIT_SUCCESS);
}
