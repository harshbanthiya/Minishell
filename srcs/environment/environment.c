/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:14:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/11 21:21:56 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_list	*init_env(char **envp)
{
	t_list	*env;
	char	**split;

	if (envp == NULL)
		return (NULL);
	env = NULL;
	while (envp && *envp)
	{
		split = ft_split(*envp, '='); //create a splitn to only split on first '='
		if (split == NULL)
		{
			free_split(split);
			return (free_env(env));
		}
		lst_add_back(&env, lst_new_node(new_var(split[0], split[1])));
		ft_free(split);
		envp++;
	}
	return (env);
}

t_list	**get_env(void)
{
	return (&g_shell.env);
}

void	*free_env(void *ptr)
{
	t_list	*env;

	env = (t_list *)ptr;
	if (env != NULL)
	{
		lst_clear(env, free_var);
	}
	else
		free(ptr);
	return (NULL);
}
