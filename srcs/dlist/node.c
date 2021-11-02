/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:23:16 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 15:00:07 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_dlist	*lst_new_node(void *content)
{
	t_dlist	*node;

	node = (t_dlist *)malloc(sizeof(t_dlist));
	if (node == NULL)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	lst_remove_node(t_dlist *node, void *(del)(void *))
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

t_dlist	*lst_unlink_node(t_dlist **lst, t_dlist *node)
{
	if (lst != NULL && *lst == node)
		*lst = (*lst)->next;
	if (node == NULL)
		return (node);
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}
