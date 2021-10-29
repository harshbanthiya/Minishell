/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:02:42 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/29 18:24:30 by sfournie         ###   ########.fr       */
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
	t_var	*pwd;

	if (envp != NULL)
		sh.env = init_env(envp);
	sh.builtins = init_builtins();
	init_terms(&sh, term_get_active_fd());
	init_signals();
	pwd = get_var("PWD", sh.env);
	if (pwd != NULL)
		sh.pwd = ft_strdup(pwd->value);
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
