/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:14:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/08 14:44:14 by sfournie         ###   ########.fr       */
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
		add_back(&env, new_node(new_var(split[0], split[1])));
		ft_free(split);
		envp++;
	}
	return (env);
}

t_list	**get_env(void)
{
	return (&g_shell.env);
}

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

t_var	*get_var(char *key)
{
}

void	*free_var(void *ptr)
{
	t_var	*var;

	var = (t_var *)ptr;
	if (var != NULL)
	{
		if (var->key != NULL)
			ft_free(var->key);
		if (var->value != NULL)
			ft_free(var->value);
		ft_free(ptr);
	}
	return (NULL);
}

void	*free_env(void *ptr)
{
	t_list	*env;

	env = (t_list *)ptr;
	if (env != NULL)
	{
		clear_list(env, free_var);
	}
	else
		free(ptr);
	return (NULL);
}
