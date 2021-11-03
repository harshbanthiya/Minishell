/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 23:39:56 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/06 15:17:44 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *lst;

	if ((lst = (t_list *)malloc(sizeof(t_list))) == 0)
		return (0);
	lst->content = content;
	lst->next = 0;
	return (lst);
}
