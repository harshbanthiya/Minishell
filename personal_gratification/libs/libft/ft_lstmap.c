/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 00:38:45 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/09 20:17:26 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_sub_lstclear(t_list **lst, void (*del)(void *))
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

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp_res;

	if (!lst || ((result = (t_list *)malloc(sizeof(t_list))) == 0))
		return (0);
	result->content = (*f)(lst->content);
	result->next = 0;
	temp_res = result;
	lst = lst->next;
	while (lst != 0)
	{
		if ((temp_res->next = (t_list *)malloc(sizeof(t_list))) == 0)
		{
			ft_sub_lstclear(&result, del);
			return (0);
		}
		temp_res = temp_res->next;
		temp_res->content = (*f)(lst->content);
		temp_res->next = 0;
		lst = lst->next;
	}
	return (result);
}
