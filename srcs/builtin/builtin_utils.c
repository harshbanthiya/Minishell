/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:15:44 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/28 10:27:57 by sfournie         ###   ########.fr       */
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
	if (!ft_strncmp(cmd, "export", 6))
		ft_export(args, get_env());
	else if (!ft_strncmp(cmd, "unset", 5))
		ft_unset(args, get_env());
	else if (!ft_strncmp(cmd, "echo", 4))
		ft_echo(args, get_fd(1));
	else if (!ft_strncmp(cmd, "env", 3))
		ft_env(1);
	else if (!ft_strncmp(cmd, "exit", 4))
		ft_exit();
	else if (!ft_strncmp(cmd, "cd", 2))
		ft_cd(args);
	else if (!ft_strncmp(cmd, "pwd", 3))
		ft_pwd(get_fd(1));
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
