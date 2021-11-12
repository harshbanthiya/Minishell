/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:15:44 by sfournie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/08 16:52:34 by sfournie         ###   ########.fr       */
=======
/*   Updated: 2021/11/12 16:41:29 by sfournie         ###   ########.fr       */
>>>>>>> develop
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

int	run_builtin(char **argv, t_dlist **lst, int is_pipe)
{
	int		exit_code;

	exit_code = 1;
	if (!argv || !argv[0] || !is_builtin(argv[0]))
		return (1);
	if (!ft_strcmp(argv[0], "export"))
		exit_code = ft_export(&argv[1], lst);
	else if (!ft_strcmp(argv[0], "unset"))
		exit_code = ft_unset(&argv[1], lst);
	else if (!ft_strcmp(argv[0], "echo"))
		exit_code = ft_echo(&argv[1], lst);
	else if (!ft_strcmp(argv[0], "env"))
		exit_code = ft_env(&argv[1], lst);
	else if (!ft_strcmp(argv[0], "exit"))
		exit_code = ft_exit(&argv[1], lst);
	else if (!ft_strcmp(argv[0], "cd"))
		exit_code = ft_cd(&argv[1], lst);
	else if (!ft_strcmp(argv[0], "pwd"))
		exit_code = ft_pwd(&argv[1], lst);
	return (exit_code);
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

void	error_builtin(char *builtname, char *str, char *msg, int errcode)
{
	ft_putstr_fd("minishell", 2);
	if (builtname != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(builtname, 2);
	}
	if (str != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd("\'", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\'", 2);
	}
	if (msg != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(msg, 2);
	}
	errno = errcode;
}
