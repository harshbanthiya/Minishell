/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:17:07 by cbaek             #+#    #+#             */
/*   Updated: 2021/02/01 14:00:06 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_exit(t_cmd *cmd)
{
	int	exit_status;

	exit_status = EXIT_FAILURE;
	printf("cmd->argc counter: %d\n", cmd->argc);
	if (cmd->argc == 1)
		exit(exit_status = EXIT_SUCCESS);
	else if (cmd->argc == 2)
	{
		exit_status = ft_atoi(cmd->argv[1]);
		exit(exit_status);
	}
	else
	{
		ft_putstr_fd("exit: too many arguments\n", 1);
		exit_status = 1;
	}
	return (exit_status);
}
///bash: exit: 123456789765432456789765432: numeric argument required
