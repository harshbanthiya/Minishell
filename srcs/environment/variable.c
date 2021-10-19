/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:01:18 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/19 17:27:08 by sfournie         ###   ########.fr       */
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

void	print_var(int fd, t_var *var)
{
	if (var->key != NULL)
	{
		ft_putstr_fd(var->key, fd);
		ft_putchar_fd('=', fd);
		if (var->value != NULL)
			ft_putstr_fd(var->value, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	print_var_extra(int fd, t_var *var)
{
	if (var->key != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(var->key, fd);
		ft_putchar_fd('=', fd);
		ft_putchar_fd('\"', fd);
		if (var->value != NULL)
			ft_putstr_fd(var->value, fd);
		ft_putchar_fd('\"', fd);
		ft_putchar_fd('\n', fd);
	}
}

t_var	*get_var(char *key, t_list *list)
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

char	*get_var_value(char *key, t_list *list)
{
	t_var	*var;

	var = get_var(key, list);
	if (var != NULL)
		return (var->value);
	return (NULL);
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