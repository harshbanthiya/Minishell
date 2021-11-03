/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 22:04:56 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/31 22:57:34 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	ft_dictswap(t_list *env_head)
{
	char	*tmp_key;
	char	*tmp_val;

	if (!(tmp_key = ft_strdup(((t_env *)env_head->content)->key)))
		return (0);
	free(((t_env *)env_head->content)->key);
	((t_env *)env_head->content)->key = ((t_env *)env_head->next->content)->key;
	((t_env *)env_head->next->content)->key = tmp_key;
	if (!(tmp_val = ft_strdup(((t_env *)env_head->content)->val)))
		return (0);
	free(((t_env *)env_head->content)->val);
	((t_env *)env_head->content)->val = ((t_env *)env_head->next->content)->val;
	((t_env *)env_head->next->content)->val = tmp_val;
	return (1);
}

int			sort_env(t_list *env_head)
{
	t_list	*head_save;
	int		i;
	int		j;

	head_save = env_head;
	i = ft_lstsize(env_head);
	while (--i > 0)
	{
		j = i + 1;
		env_head = head_save;
		while (--j > 0)
		{
			if (ft_strncmp(((t_env *)env_head->content)->key,\
					((t_env *)env_head->next->content)->key,\
				ft_strlen(((t_env *)env_head->content)->key) + 1) > 0)
				if (!(ft_dictswap(env_head)))
					return (-1);
			env_head = env_head->next;
		}
	}
	env_head = head_save;
	return (0);
}
