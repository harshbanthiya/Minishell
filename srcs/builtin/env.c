/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:41 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/13 15:00:09 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* Duplicate the env list, sort the new list and send it back */
static t_list	*sort_env(t_list *env)
{
	t_list	*sorted;
	t_list	*parser;
	t_list	*save;
	t_var	*var;

	sorted = NULL;
	env = env_lst_dup(env, free_var);
	while (env != NULL)
	{
		parser = env;
		save = parser;
		while (parser != NULL && parser->content != NULL)
		{
			var = (t_var *)parser->content;
			if (ft_strcmp(var->key, ((t_var *)save->content)->key) < 0)
				save = parser;
			parser = parser->next;
		}
		lst_unlink_node(&env, save);
		lst_add_back(&sorted, save);
	}
	return (sorted);
}

/* 0 is for env, 1 is for export */
static void	print_env(int fd, t_list *env, int mode)
{
	t_var	*var;

	while (env != NULL)
	{
		var = (t_var *)env->content;
		if (mode == 0)
			print_var(fd, var);
		else if (mode == 1)
			print_var_extra(fd, var);
		env = env->next;
	}
}

/* same as env, but will sort it. Used with export. */
void	ft_env_sorted(int fd)
{
	t_list	*env;
	t_list	*sorted;

	env = *get_env();
	if (env != NULL)
	{
		sorted = sort_env(env);
		if (sorted != NULL)
		{
			print_env(fd, sorted, 0);
			sorted = lst_clear(sorted, free_var);
		}		
	}
	return ;
}

/* Print the env list */
void	ft_env(int fd)
{
	t_list	*env;

	env = *get_env();
	if (env != NULL)
		print_env(fd, env, 0);
	return ;
}
