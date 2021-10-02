/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:41 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/01 21:58:08 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_env(int fd)
{
	t_list	*env;

	env = g_shell.env;
	while (env != NULL)
	{
		if (((t_var *)(env->content))->name != NULL)
		{
			printf("%s", ((t_var *)(env->content))->name);
			printf("%s", "=");
			if (((t_var *)(env->content))->value != NULL)
				printf("%s", ((t_var *)(env->content))->value);
			printf("%s", "\n");		
		}
		env = env->next;
		
			
	}
	return ;
}
