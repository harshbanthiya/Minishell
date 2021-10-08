/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:47 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/07 18:34:14 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	export(char *str, t_list **lst)
{	
	t_list	*temp;
	t_var	*var;
	char	**split;

	if (!ft_strchr(str, '='))
		return (0);
	split = ft_split(str, '=');
	if (split == NULL)
		return (0);
	temp = *lst;
	while (temp != NULL)
	{
		var = (t_var *)temp->content;
		if (!ft_strncmp(split[0], var->name, ft_strlen(split[0])))
		{
			var->value = split[1];
			free_split(split);
			return (1);
		}
		temp = temp->next;
	}
	var = new_var(split[0], split[1]);
	add_back(lst, new_node(var));
	ft_free(split);
	return (1);
}
