/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:41 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/04 09:56:46 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_env(int fd)
{
	t_list	*env;
	t_var	*var;

	env = *ft_get_env();
	while (env != NULL)
	{
		var = (t_var *)env->content;
		if (var->name != NULL)
		{
			printf("%s", var->name);
			printf("%s", "=");
			if (var->value != NULL)
				printf("%s", var->value);
			printf("%s", "\n");
		}
		env = env->next;
	}
	return ;
}
