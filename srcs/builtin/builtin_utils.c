/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:15:44 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/18 16:09:57 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

static char	*ft_str_tolower(char *str)
{
	char	*str_lower;
	int		i;

	if (!str)
		return (NULL);
	str_lower = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	while (*str)
		str_lower[i++] = (char)ft_tolower(*(str++));
	str_lower[i] = '\0';
	return (str_lower);
}

int	is_builtin(char *name)
{
	char	*str_lower;
	int		found;

	if (!name)
		return (0);
	found = 0;
	str_lower = ft_str_tolower(name);
	if (!ft_strcmp(str_lower, "export"))
		found = 1;
	else if (!ft_strcmp(str_lower, "unset"))
		found = 1;
	else if (!ft_strcmp(str_lower, "echo"))
		found = 1;
	else if (!ft_strcmp(str_lower, "env"))
		found = 1;
	else if (!ft_strcmp(str_lower, "exit"))
		found = 1;
	else if (!ft_strcmp(str_lower, "cd"))
		found = 1;
	else if (!ft_strcmp(str_lower, "pwd"))
		found = 1;
	ft_free(str_lower);
	return (found);
}

t_builtin_cmd	*get_builtin_func(char *cmd_name)
{
	char			*str_lower;
	t_builtin_cmd	*f;

	if (!cmd_name)
		return (0);
	f = NULL;
	str_lower = ft_str_tolower(cmd_name);
	if (ft_strcmp(str_lower, "echo") == 0)
		f = ft_echo;
	else if (ft_strcmp(str_lower, "cd") == 0)
		f = ft_cd;
	else if (ft_strcmp(str_lower, "pwd") == 0)
		f = ft_pwd;
	else if (ft_strcmp(str_lower, "env") == 0)
		f = ft_env;
	else if (ft_strcmp(str_lower, "export") == 0)
		f = ft_export;
	else if (ft_strcmp(str_lower, "unset") == 0)
		f = ft_unset;
	else if (ft_strcmp(str_lower, "exit") == 0)
		f = ft_exit;
	ft_free(str_lower);
	return (f);
}

int	error_builtin(char *builtname, char *str, char *msg, int code)
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
	return (code);
}
