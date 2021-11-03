/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 23:10:47 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/31 23:14:03 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_exist_key(char *key, t_list *env_list)
{
	int		len;
	int		len_find;
	int		len_exist;

	len_find = ft_strlen(key);
	len_exist = ft_strlen((char *)((t_env *)env_list->content)->key);
	if (len_find > len_exist)
		len = len_find;
	else
		len = len_exist;
	if (ft_strncmp(key, ((t_env *)env_list->content)->key, len) == 0)
		return (1);
	return (0);
}

void		unset_env_one(t_list **env_head, char *key)
{
	t_list *head;
	t_list *delete;

	head = *env_head;
	if (is_exist_key(key, head))
	{
		*env_head = head->next;
		free_env((t_env *)head->content);
		free(head);
		return ;
	}
	while (head->next)
	{
		if (is_exist_key(key, head->next))
		{
			delete = head->next;
			if (delete->next != NULL)
				head->next = delete->next;
			else
				head->next = NULL;
			free_env((t_env *)delete->content);
			free(delete);
			return ;
		}
		head = head->next;
	}
}
