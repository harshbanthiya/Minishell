/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:02:42 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/05 16:49:43 by sfournie         ###   ########.fr       */
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
	char	*pwd;

	if (envp != NULL)
		sh.env = init_env(envp);
	sh.builtins = init_builtins();
	init_terms(&sh, term_get_active_fd());
	init_signals();
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		sh.pwd = ft_strdup(pwd);
		ft_free(pwd);
	}
	sh.sh_mode = 1;
	g_shell = sh;
}

void	exit_shell(void)
{
	term_restore_default(term_get_active_fd());
	free_shell();
}

void	free_shell(void)
{
	t_shell	*sh;

	sh = get_shell();
	term_restore_default(term_get_active_fd());
	if (sh != NULL)
		sh->env = free_env(sh->env);
	if (sh->builtins != NULL)
		sh->builtins = free_split(sh->builtins);
}
