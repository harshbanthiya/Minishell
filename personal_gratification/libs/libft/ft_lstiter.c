/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:34:54 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/06 15:07:21 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *temp;

	temp = lst;
	if (!lst || !f)
		return ;
	while (temp != 0)
	{
		(*f)(temp->content);
		temp = temp->next;
	}
}
