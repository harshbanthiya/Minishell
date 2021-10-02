/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:47 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/01 21:53:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_export(char *str, t_list **lst)
{	
	t_list	*temp;
	char	**split;
	
	split = ft_split(str, '=');
	if (split == NULL)
		return (0);
	temp = *lst;
	while (temp != NULL)
	{
		if (!ft_strncmp(split[0], ((t_var *)temp->content)->name, ft_strlen(split[0])))
		{
			((t_var *)temp->content)->value = split[1]; // NOT FINISHED!!! 
			return (1);
		}
		temp = temp->next;
	}
	ft_add_back(lst, ft_new_node(ft_new_var(split[0], split[1])));
	// ft_free_split(split);
	return (0);
}
