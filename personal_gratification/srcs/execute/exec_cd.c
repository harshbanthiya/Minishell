/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:17:38 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/29 18:22:08 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(char *path, t_list *env_list)
{
	char	*home;
	char	*abs_path;
	int		len;

	home = get_env_val("HOME", env_list);
	if ((ft_strncmp(path, "~", 1) == 0))
	{
		len = ft_strlen(home) + (ft_strlen(path) - 1);
		if ((abs_path = (char *)malloc(sizeof(char) * len + 1)) == NULL)
			return (0);
		abs_path[len] = '\0';
		ft_memcpy(abs_path, home, ft_strlen(home));
		ft_memcpy(&(abs_path[ft_strlen(home)]), &(path[1]), \
				ft_strlen(path) - 1);
		free(home);
		return (abs_path);
	}
	return (path);
}

static int	chdir_with_home_path(t_cmd *cmd, t_list *env_list)
{
	char	*path;
	int		ret;

	ret = TRUE;
	path = 0x0;
	if (cmd->argc == 1)
		path = replace_home_path("~", env_list);
	else
		path = get_home_path(cmd->argv[1], env_list);
	if (chdir(path) == -1)
	{
		if (cmd->argc == 1)
			print_err(cmd->argv[0], "~");
		else
			print_err(cmd->argv[0], cmd->argv[1]);
		ret = FALSE;
	}
	free(path);
	return (ret);
}

int			exec_cd(t_cmd *cmd, t_list *env_list)
{
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	if (cmd->argc == 1 || ((cmd->argv[1] != 0x0) && \
			(ft_strncmp(cmd->argv[1], "~", 1) == 0)))
	{
		if (!(chdir_with_home_path(cmd, env_list)))
			exit_status = EXIT_FAILURE;
	}
	else if (cmd->argc > 1)
	{
		if (chdir(cmd->argv[1]) == -1)
		{
			print_err(cmd->argv[0], cmd->argv[1]);
			exit_status = EXIT_FAILURE;
		}
	}
	else
	{
		print_err(cmd->argv[0], cmd->argv[1]);
		exit_status = EXIT_FAILURE;
	}
	return (exit_status);
}
