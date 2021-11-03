/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 20:20:47 by sucho             #+#    #+#             */
/*   Updated: 2021/01/31 21:04:59 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_path_arr(t_list *env_path)
{
	char	*path_env;
	char	**path_arr;

	path_env = NULL;
	while (env_path)
	{
		if (ft_strnstr( ((t_env *)(env_path->content))->key, "PATH",
			ft_strlen("PATH") + 1))
			path_env = ((t_env *)(env_path->content))->val;
		env_path = env_path->next;
	}
	if (!path_env)
		return (0);
	path_arr = ft_split(path_env, ':');
	return (path_arr);
}

void
	free_path_arr(char **path_arr)
{
	int i;

	i = 0;
	while (path_arr[i])
	{
		free(path_arr[i]);
		i++;
	}
	free(path_arr);
}

void
	free_tmp_env(char **env)
{
	int i;

	i = 0;
	if (env)
	{
		while (env[i])
			free(env[i++]);
		free(env);
	}
}

void
	exec_with_path(t_cmd *cmd, char **path_arr, t_list *env_list)
{
	char	*path_cmd1;
	char	*path_cmd2;
	char	**tmp_env;
	int		i;

	i = 0;
	while (path_arr[i])
	{
		path_cmd1 = ft_strjoin(path_arr[i], "/");
		path_cmd2 = ft_strjoin(path_cmd1, cmd->argv[0]);
		tmp_env = env_list_to_envp(env_list);
		execve(path_cmd2, cmd->argv, tmp_env);
		free_tmp_env(tmp_env);
		free(path_cmd1);
		free(path_cmd2);
		i++;
	}
}
