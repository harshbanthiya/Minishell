/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:23:16 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/11 17:38:12 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	lst_add_front(t_list **lst, t_list *node)
{
	if (*lst == NULL)
		*lst = node;
	else
	{
		(*lst)->prev = node;
		*lst = node;
	}
}

void	lst_add_back(t_list **lst, t_list *node)
{
	t_list	*temp;

	if (*lst == NULL)
		*lst = node;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
		node->prev = temp;
	}
}

void	*lst_clear(t_list *lst, void *(del)(void *))
{
	if (lst == NULL)
		return (NULL);
	lst_clear(lst->next, del);
	if (del != NULL)
		del(lst->content);
	ft_free(lst);
	return (NULL);
}

t_list	*env_lst_dup(t_list *lst, void *(del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;
	t_var	*var;
	t_var	*new_v;

	new_lst = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL && lst->content != NULL)
	{
		var = (t_var *)lst->content;
		new_v = new_var(ft_strdup(var->key), ft_strdup(var->value));
		if (new_v == NULL)
			return (lst_clear(new_lst, del));
		new_node = lst_new_node(new_v);
		lst_add_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
