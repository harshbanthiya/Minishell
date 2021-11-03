/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:19:17 by cbaek             #+#    #+#             */
/*   Updated: 2021/02/01 12:16:36 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_unset(t_cmd *cmd, t_list **env_list)
{
	int		idx;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	idx = 1;
	if (cmd->argc > 1)
	{
		while (idx < cmd->argc)
		{
			if (is_valid_env_key(cmd->argv[idx]))
				unset_env_one(env_list, cmd->argv[idx]);
			else
			{
				ft_putstr_fd("bash: unset: `", 1);
				ft_putstr_fd(cmd->argv[idx], 1);
				ft_putstr_fd("': not a valid identifier\n", 1);
				exit_status = EXIT_FAILURE;
			}
			idx++;
		}
	}
	return (exit_status);
}
