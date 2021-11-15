/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:01:18 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/14 15:13:21 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_var	*new_var(char *key, char *value)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (var == NULL)
		return (NULL);
	var->key = key;
	var->value = value;
	return (var);
}

void	*dup_var(void *ptr)
{
	t_var	*var;

	var = (t_var *)ptr;
	if (var != NULL)
	{
		if (var->value == NULL)
			return (new_var(ft_strdup(var->key), NULL));
		else
			return (new_var(ft_strdup(var->key), ft_strdup(var->value)));
	}
	return (NULL);
}

t_var	*get_var(char *key, t_dlist *list)
{
	t_var	*var;

	while (list != NULL)
	{
		var = (t_var *)list->content;
		if (var != NULL && var->key != NULL && !ft_strcmp(key, var->key))
		{
			return (var);
		}
		list = list->next;
	}
	return (NULL);
}

char	*get_var_value(char *key, t_dlist *list)
{
	t_var	*var;

	var = get_var(key, list);
	if (var != NULL)
		return (var->value);
	return (NULL);
}

void	var_set_value(char *key, char *value, t_dlist *list)
{
	t_var	*var;

	if (!list || !key)
		return ;
	var = get_var(key, list);
	if (!var)
		return ;
	ft_free(var->value);
	var->value = ft_strdup(var->value);
}
