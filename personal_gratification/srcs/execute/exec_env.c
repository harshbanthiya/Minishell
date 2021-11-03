/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:18:54 by cbaek             #+#    #+#             */
/*   Updated: 2021/02/01 12:11:51 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(t_cmd *cmd, t_list **env_list)
{
	int exit_status;

	exit_status = 0;
	if (cmd->argc == 1)
		print_env_list(*env_list);
	else
	{
		ft_putstr_fd("env: too many arguments\n", 1);
		exit_status = 1;
	}
	return (exit_status);
}
