/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:14:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/05 16:26:47 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_list	*ft_init_env(char **envp)
{
	t_list	*env;
	char	**split;
	
	if (envp == NULL)
		return (NULL);
	env = (t_list *)malloc(sizeof(t_list));
	env = NULL;
	while (envp && *envp)
	{
		split = ft_split(*envp, '='); // create a splitn to only split on first '='
		if (split == NULL)
		{
			ft_free_split(split);
			return (ft_free_env(env));
		}
		ft_add_back(&env, ft_new_node(ft_new_var(split[0], split[1])));

		envp++;
	}
	return (env);
}

t_list	**ft_get_env(void)
{
	return (&g_shell.env);
}

t_var	*ft_new_var(char *name, char *value)
{
	t_var	*var;

	var = (t_var *)malloc(sizeof(t_var));
	if (var == NULL)
		return (NULL);
	var->name = name;
	var->value = value;
	return (var);
}

void	*ft_free_var(void *ptr)
{
	t_var	*var;

	var = (t_var *)ptr;
	if (var != NULL)
	{
		if (var->name != NULL)
			ft_free(var->name);
		if (var->value != NULL)
			ft_free(var->value);
		ft_free(ptr);
	}
	return (NULL);
}

void	*ft_free_env(void *ptr)
{
	t_list	*env;

	env = (t_list *)ptr;
	if (env != NULL)
	{
		ft_clear_list(env, ft_free_var); 
		free(ptr);
	}
	return (NULL);
}
