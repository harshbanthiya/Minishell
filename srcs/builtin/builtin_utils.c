/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:15:44 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/08 18:04:50 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	is_builtin(char *name)
{
	char	**builtins;

	builtins = get_builtins();
	if (!builtins)
		return (0);
	while (*builtins)
	{
		if (!ft_strcmp(*(builtins++), name))
			return (1);
	}
	return (0);
}

int		run_builtin(char *name) // need to be redone
{
	char	**builtins;

	// if (!name || !is_builtin(name))
	// 	return (0);
	builtins = get_builtins();
	if (!ft_strncmp(name, "export", 6))
		ft_export(name + 7, get_env());
	else if (!ft_strncmp(name, "unset", 5))
		ft_unset(name + 6, get_env());
	else if (!ft_strncmp(name, "echo", 4))
		ft_echo(name + 5, 1);
	else if (!ft_strncmp(name, "env", 3))
		ft_env(1);
	else if (!ft_strncmp(name, "exit", 4))
		ft_exit();
	else if (!ft_strncmp(name, "cd", 2))
		ft_cd(name + 3);
	else if (!ft_strncmp(name, "pwd", 3))
		ft_pwd();
	return (1);	
}

char	**get_builtins()
{
	t_shell	*sh;

	sh = get_shell();
	if (sh != NULL)
	{
		return (sh->builtins);
	}
	return (NULL);
}

char	**init_builtins()
{
	char	**builtins;

	builtins = (char **)ft_calloc(8, sizeof(char *));
	builtins[0] = ft_strdup("cd");
	builtins[1] = ft_strdup("echo");
	builtins[2] = ft_strdup("exit");
	builtins[3] = ft_strdup("env");
	builtins[4] = ft_strdup("export");
	builtins[5] = ft_strdup("pwd");
	builtins[6] = ft_strdup("unset");
	return (builtins);
}