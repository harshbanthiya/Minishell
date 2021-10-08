/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:47 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/08 16:07:35 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_export(char *str, t_list **lst)
{	
	t_var	*var;
	char	**split;

	if (!ft_strchr(str, '='))
		return (0);
	split = ft_split(str, '=');
	if (split == NULL)
		return (0);
	var = get_var(split[0], *lst);
	if (var != NULL)
	{
		var->value = ft_strdup(split[1]);
		free_split(split);
		return (1);
	}
	var = new_var(split[0], split[1]);
	lst_add_back(lst, lst_new_node(var));
	ft_free(split);
	return (1);
}
