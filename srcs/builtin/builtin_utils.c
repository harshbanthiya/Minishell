/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:15:44 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 14:28:50 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char	**init_builtins(void)
{
	char	**builtins;

	builtins = (char **)ft_calloc(8, sizeof(char *));
	if (builtins == NULL)
		return (NULL);
	builtins[0] = ft_strdup("cd");
	builtins[1] = ft_strdup("echo");
	builtins[2] = ft_strdup("exit");
	builtins[3] = ft_strdup("env");
	builtins[4] = ft_strdup("export");
	builtins[5] = ft_strdup("pwd");
	builtins[6] = ft_strdup("unset");
	return (builtins);
}

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

int	run_builtin(char *cmd, char **args)
{
	char	**builtins;

	if (!cmd || !is_builtin(cmd))
		return (0);
	builtins = get_builtins();
	if (!ft_strcmp(cmd, "export"))
		ft_export(args, get_env());
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(args, get_env());
	else if (!ft_strcmp(cmd, "echo"))
		ft_echo(args, 1);
	else if (!ft_strcmp(cmd, "env"))
		ft_env(1);
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit();
	else if (!ft_strcmp(cmd, "cd"))
		ft_cd(args);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd(1);
	return (1);
}

char	**get_builtins(void)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh != NULL)
	{
		return (sh->builtins);
	}
	return (NULL);
}
