/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:25:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/25 14:46:01 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_shell	*ft_get_shell(void)
{
	return (&g_shell);
}

void	ft_init_shell(char **envp)
{
	t_shell	sh;
	
	sh.env = ft_init_env(envp); // check for NULL?
	sh.active_term = NULL;
	tcgetattr(1, sh.def_term);
	tcgetattr(1, sh.saved_term);
	g_shell = sh;
}

void	*ft_free_shell(void *ptr)
{	
	t_shell	*sh;

	sh = (t_shell *)ptr;
	if (sh != NULL)
	{
		sh->env = ft_free_env(sh->env);
	}
	return (NULL);
}
