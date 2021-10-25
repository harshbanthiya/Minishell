/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:23:16 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/11 17:47:33 by sfournie         ###   ########.fr       */
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

t_list	*lst_unlink_node(t_list **lst, t_list *node)
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
