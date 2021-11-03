/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:30:32 by cbaek             #+#    #+#             */
/*   Updated: 2021/02/01 13:43:14 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_valid_env_key(char *env_key)
{
	int idx;

	idx = 0;
	if (*env_key == '_' || ft_isalpha(env_key[idx]))
	{
		idx++;
		while (env_key[idx] != '\0')
		{
			if (!ft_isalnum(env_key[idx]) && env_key[idx] != '_')
				return (FALSE);
			idx++;
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

int			execute_internal_in_child(t_cmd *cmd, t_list **env_list)
{
	int	ret;

	ret = -1;
	if (cmd->pipe->stdin_pipe || cmd->pipe->stdout_pipe)
		if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0] + 1)))
			ret = exec_exit(cmd);
	if (ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = exec_echo(cmd);
	else if (ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = exec_pwd(cmd);
	else if ((ft_strncmp(cmd->argv[0], "export", \
			ft_strlen(cmd->argv[0]) + 1) == 0) && (cmd->argc == 1))
		ret = exec_export(cmd, env_list);
	else if (ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = exec_env(cmd, env_list);
	return (ret);
}

int			execute_internal_in_parent(t_cmd *cmd, t_list **env_list)
{
	int	ret;

	ret = -1;
	if (ft_strncmp(cmd->argv[0], "cd", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = exec_cd(cmd, *env_list);
	else if (ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = exec_exit(cmd);
	else if (ft_strncmp(cmd->argv[0], "unset", \
			ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = exec_unset(cmd, env_list);
	else if ((ft_strncmp(cmd->argv[0], "export", \
			ft_strlen(cmd->argv[0]) + 1) == 0) && (cmd->argc > 1))
		ret = exec_export(cmd, env_list);
	return (ret);
}
