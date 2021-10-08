/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:25:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/08 17:00:12 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_shell	*get_shell(void)
{
	return (&g_shell);
}

void	init_shell(char **envp)
{
	t_shell	sh;
	
	if (envp != NULL)
		sh.env = init_env(envp);
	sh.builtins = init_builtins();
	sh.active_term = NULL;
	tcgetattr(1, sh.def_term);
	tcgetattr(1, sh.saved_term);
	g_shell = sh;
}

void	free_shell(void)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh != NULL)
		sh->env = free_env(sh->env);
	if (sh->builtins != NULL)
		sh->builtins = free_split(sh->builtins);
}
