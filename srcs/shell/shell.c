/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:02:42 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/14 15:00:38 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	sh_lvl_increment(t_shell *sh)
{
	t_dlist	*env;
	t_var	*var;
	int		lvl;
	char	*lvl_str;

	lvl = 0;
	env = sh->env;
	var = get_var("SHLVL", env);
	if (var)
	{
		lvl = ft_atoi(var->value);
		lvl++;
	}
	lvl_str = ft_itoa(lvl);
	ft_export_var("SHLVL", lvl_str, &env);
	ft_free(lvl_str);
}

t_shell	*get_shell(void)
{
	return (&g_shell);
}

void	sh_init(char **envp)
{
	t_shell	sh;
	char	*pwd;

	if (envp != NULL)
		sh.env = sh_init_env(envp);
	sh_lvl_increment(&sh);
	sh.builtins = init_builtins();
	init_signals();
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		sh.pwd = ft_strdup(pwd);
		ft_free(pwd);
	}
	sh_change_mode(&sh, 1);
	sh.status = 0;
	g_shell = sh;
}

void	exit_shell(void)
{
	free_shell();
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
