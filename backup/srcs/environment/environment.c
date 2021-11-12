/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:14:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/07 16:50:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_dlist	*sh_init_env(char **envp)
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

char		**env_list_to_envp(t_dlist *env_head)
{
	t_dlist	*temp;
	int		i;
	char	**output;

	temp = env_head;
	i = lst_size(temp);
	temp = env_head;
	if (!(output = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (temp)
	{
		output[i] = ft_strjoin(((t_var *)(temp->content))->key, "=");
		output[i] = ft_strjoin(output[i], ((t_var *)(temp->content))->value);
		temp = temp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}
