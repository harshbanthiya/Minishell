/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:02:42 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/02 14:10:17 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

static void	put_shlvl_warnmsg(int lvl)
{
	char	*lvl_str;

	lvl_str = ft_itoa(lvl);
	if (!lvl_str)
		put_minish_err_msg_and_exit(1, "initialization", "malloc failed");
	ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
	ft_putstr_fd(lvl_str, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
	free(lvl_str);
}

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
		if (lvl < 0)
			lvl = 0;
		else
			lvl++;
		if (lvl >= 1000)
		{
			put_shlvl_warnmsg(lvl);
			lvl = 1;
		}
	}
	lvl_str = ft_itoa(lvl);
	if (lvl_str)
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
	ft_export_var("_", "./minishell", &sh.env);
	sh_lvl_increment(&sh);
	init_signals();
	ft_memset(sh.prompt, '\0', PROMPT_SIZE);
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		sh.pwd = ft_strdup(pwd);
		ft_free(pwd);
	}
	sh_change_mode(&sh, 1);
	sh.status = 0;
	sh.exit_flag = -1;
	g_shell = sh;
}

void	free_shell(void)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh != NULL)
	{
		sh->pwd = ft_free(sh->pwd);
		sh->env = free_env(sh->env);
	}
}

void 	exit_shell(void)
{
	parse_free_all_ast();
	free_shell();
	exit(g_shell.exit_flag);
}