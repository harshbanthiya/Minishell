/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:24:11 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/06 15:15:56 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *temp;

	if (!*lst || !lst || !del)
		return ;
	while (*lst != 0)
	{
		temp = (*lst)->next;
		(*del)((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}
