/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:51 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/01 22:11:42 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_unset(char *name, t_list *lst)
{
	t_list	*temp;
	
	if (name == NULL || lst == NULL)
		return (0);
	temp = lst;
	while (temp != NULL)
	{
		if (!ft_strncmp(name, ((t_var *)temp->content)->name, ft_strlen(name)))
		{
			ft_remove_node(temp, ft_free_var);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
