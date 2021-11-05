/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:41 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/05 15:10:50 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* Duplicate the env list, sort the new list and send it back */
static t_dlist	*sort_env(t_dlist *env)
{
	t_dlist	*sorted;
	t_dlist	*parser;
	t_dlist	*save;
	t_var	*var;

	sorted = NULL;
	env = lst_dup(env, dup_var, free_var);
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
static void	print_env(int fd, t_dlist *env, int mode)
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
int	ft_env_export(int fd)
{
	t_dlist	*env;
	t_dlist	*sorted;

	env = *get_env();
	if (env != NULL)
	{
		sorted = sort_env(env);
		if (sorted != NULL)
		{
			print_env(fd, sorted, 1);
			sorted = lst_clear(sorted, free_var);
		}		
	}
	else
		return (1);
	return (0);
}

/* Print the env list */
int	ft_env(t_cmd *cmd, t_dlist **lst)
{
	if (lst != NULL && !cmd->argv[1])
	{
		print_env(1, *lst, 0);
		return (0);
	}
	return (126);
}
