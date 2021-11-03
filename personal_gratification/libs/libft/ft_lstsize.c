/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 23:55:50 by cbaek             #+#    #+#             */
/*   Updated: 2020/03/08 00:03:41 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t size;
	t_list *temp;

	size = 0;
	temp = lst;
	while (temp != 0)
	{
		temp = temp->next;
		size++;
	}
	return (size);
}
