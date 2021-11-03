/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:18:30 by cbaek             #+#    #+#             */
/*   Updated: 2021/02/01 11:49:51 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env		*create_env(char *str, int idx)
{
	t_env	*env;
	int		len;

	len = ft_strlen(str);
	if ((env = (t_env *)malloc(sizeof(t_env))) == 0)
		return (0);
	env->key = ft_strndup(str, idx);
	env->val = ft_strndup(&(str[idx + 1]), len - (idx + 1));
	return (env);
}

void		export_sort_and_print(t_list *env_list)
{
	t_list *env_head;

	env_head = env_list;
	sort_env(env_head);
	while (env_head)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(((t_env *)(env_head->content))->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd(((t_env *)(env_head->content))->val, 1);
		ft_putstr_fd("\"", 1);
		ft_putstr_fd("\n", 1);
		env_head = env_head->next;
	}
}

int			exec_export(t_cmd *cmd, t_list **env_list)
{
	int		idx;
	int		sub_idx;
	int		len;
	t_env	*env;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	if (cmd->argc == 1)
	{
		export_sort_and_print(*env_list);
		return (exit_status = EXIT_SUCCESS);
	}
	env = 0x0;
	idx = 1;
	while (idx < cmd->argc)
	{
		len = ft_strlen(cmd->argv[idx]);
		sub_idx = 0;
		if ((ft_strncmp(cmd->argv[idx], "=", 1) == 0) || \
				(('0' <= cmd->argv[idx][0]) &&
				(cmd->argv[idx][0] <= '9')))
		{
			ft_putstr_fd("bash: export: `", 1);
			ft_putstr_fd(cmd->argv[idx], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			exit_status = EXIT_FAILURE;
			idx++;
			continue;
		}
		while (sub_idx < len)
		{
			if ((cmd->argv[idx])[sub_idx] == '=')
			{
				exit_status = EXIT_FAILURE;
				break ;
			}
			sub_idx++;
		}
		if (sub_idx == 0 || sub_idx == len)
		{
			exit_status = EXIT_FAILURE;
			idx++;
			continue;
		}
		env = create_env(cmd->argv[idx], sub_idx);
		set_env_one(env_list, env);
		idx++;
	}
	return (exit_status);
}
