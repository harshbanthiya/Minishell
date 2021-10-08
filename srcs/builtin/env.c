/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:41 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/07 18:57:31 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_env(int fd)
{
	t_list	*env;
	t_var	*var;

	env = *get_env();
	while (env != NULL)
	{
		var = (t_var *)env->content;
		if (var->name != NULL)
		{
			ft_putstr_fd(var->name, fd);
			ft_putchar_fd('=', fd);
			if (var->value != NULL)
				ft_putstr_fd(var->value, fd);
			ft_putchar_fd('\n', fd);
		}
		env = env->next;
	}
	return ;
}
