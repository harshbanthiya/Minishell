/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:23:16 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/08 17:55:21 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_list	*lst_new_node(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

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

void	lst_remove_node(t_list *node, void *(del)(void *))
{
	if (node == NULL)
		return ;
	if (del != NULL)
		del(node->content);
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	ft_free(node);
}

void	lst_clear(t_list *lst, void *(del)(void *))
{
	if (lst == NULL)
		return ;
	lst_clear(lst->next, del);
	if (del != NULL)
		del(lst->content);
	ft_free(lst);
}
