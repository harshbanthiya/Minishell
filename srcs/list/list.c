/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:23:16 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 15:00:05 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	lst_add_front(t_dlist **lst, t_dlist *node)
{
	if (*lst == NULL)
		*lst = node;
	else
	{
		(*lst)->prev = node;
		*lst = node;
	}
}

void	lst_add_back(t_dlist **lst, t_dlist *node)
{
	t_dlist	*temp;

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

void	*lst_clear(t_dlist *lst, void *(del)(void *))
{
	if (lst == NULL)
		return (NULL);
	lst_clear(lst->next, del);
	if (del != NULL)
		del(lst->content);
	ft_free(lst);
	return (NULL);
}

t_dlist	*lst_dup(t_dlist *lst, void *(iter)(void *), void *(del)(void *))
{
	t_dlist	*new_lst;
	t_dlist	*new_node;
	void	*content;

	new_lst = NULL;
	if (lst == NULL)
		return (NULL);
	while (lst != NULL && lst->content != NULL)
	{
		content = iter(lst->content);
		if (content == NULL)
			return (lst_clear(new_lst, del));
		new_node = lst_new_node(content);
		lst_add_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
