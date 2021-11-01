/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 15:33:32 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DLIST_H
# define DLIST_H
# include "minishell.h"

/* Node for generic double chained list */
typedef struct s_dlist
{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}				t_dlist;

t_dlist	*lst_new_node(void *content);
void	lst_remove_node(t_dlist *node, void *(del)(void *));

void	lst_add_front(t_dlist **lst, t_dlist *node);
void	lst_add_back(t_dlist **lst, t_dlist *node);

/* Unlink a node from a list and return it */
t_dlist	*lst_unlink_node(t_dlist **lst, t_dlist *node);

t_dlist	*lst_dup(t_dlist *lst, void *(iter)(void *), void *(del)(void *));

void	*lst_clear(t_dlist *lst, void *(del)(void *));

#endif