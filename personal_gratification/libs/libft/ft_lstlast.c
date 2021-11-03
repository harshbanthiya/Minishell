/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:05:17 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/06 22:00:52 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list *result;

	if (!lst)
		return (0);
	result = lst;
	if (result->next == 0)
		return (result);
	while (1)
	{
		if (result->next == 0)
			return (result);
		result = result->next;
	}
	return (0);
}
