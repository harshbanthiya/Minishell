/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:08:23 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/19 21:36:46 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		last = *lst;
		while (last->next != 0)
			last = last->next;
		last->next = new;
	}
}
