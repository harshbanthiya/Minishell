/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:14:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 15:00:01 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_dlist	*init_env(char **envp)
{
	t_dlist	*env;
	char	**split;

	if (envp == NULL)
		return (NULL);
	env = NULL;
	while (envp && *envp)
	{
		split = ft_splitn(*envp, '=', 2);
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

t_dlist	**get_env(void)
{
	return (&g_shell.env);
}

void	*free_env(void *ptr)
{
	t_dlist	*env;

	env = (t_dlist *)ptr;
	if (env != NULL)
	{
		lst_clear(env, free_var);
	}
	else
		free(ptr);
	return (NULL);
}
