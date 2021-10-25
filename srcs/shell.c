/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:25:43 by sfournie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/10/24 18:03:21 by sfournie         ###   ########.fr       */
=======
/*   Updated: 2021/10/25 14:46:01 by hbanthiy         ###   ########.fr       */
>>>>>>> c9cced1... if any changes
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
	init_fd(sh.fd);
	tcgetattr(1, sh.active_term);
	tcgetattr(1, sh.def_term);
	tcgetattr(1, sh.saved_term);
	pwd = get_var("PWD", sh.env);
	if (pwd != NULL)
		sh.pwd = ft_strdup(pwd->value);
	g_shell = sh;
}

void	free_shell(void)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh != NULL)
<<<<<<< HEAD
		sh->env = free_env(sh->env);
	if (sh->builtins != NULL)
		sh->builtins = free_split(sh->builtins);
}

void	init_fd(int *fd)
{
	fd[0] = 0;
	fd[1] = 1;
	fd[2] = 2;
=======
	{
		sh->env = ft_free_env(sh->env);
	}
	return (NULL);
>>>>>>> c9cced1... if any changes
}
