/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:14:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/01 20:53:24 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_list	*ft_get_env(void)
{
	return (g_shell.env);
}

t_var	*ft_new_var(char *name, char *value)
{
	t_var *var;
	
	var = (t_var *)malloc(sizeof(t_var));
	if (var == NULL)
		return (NULL);
	var->name = name;
	var->value = value;
	return (var);
}

void	*ft_free_var(void *var)
{
	if (var != NULL)
	{
		if (((t_var *)var)->name != NULL)
			ft_free(((t_var *)var)->name);
		if (((t_var *)var)->value != NULL)
			ft_free(((t_var *)var)->value);
		ft_free(var);
	}
	return (NULL);
}