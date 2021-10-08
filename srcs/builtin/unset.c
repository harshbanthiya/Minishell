/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:51 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/07 17:16:31 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	unset(char *name, t_list **lst)
{
	t_list	*temp;
	t_var	*var;

	if (name == NULL || lst == NULL)
		return (0);
	temp = *lst;
	while (temp != NULL)
	{
		var = (t_var *)temp->content;
		if (!ft_strncmp(name, var->name, ft_strlen(name)))
		{
			if (temp->prev == NULL)
				*lst = temp->next;
			remove_node(temp, free_var);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}
