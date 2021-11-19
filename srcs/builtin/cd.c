/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/19 12:33:48 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

static int	cd_update(char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (get_var("OLDPWD", *get_env()))
		ft_export_var("OLDPWD", old_pwd, get_env());
	if (get_var("PWD", *get_env()))
		ft_export_var("PWD", new_pwd, get_env());
	ft_free(old_pwd);
	set_pwd(new_pwd);
	return (0);
}

static int	cd_error(char *old_pwd, char *arg, char *msg, int exit)
{
	ft_free(old_pwd);
		return (error_builtin("cd", arg, msg, exit));
}

static int	cd_home(char *old_pwd)
{
	char	*home;
	int		chdir_ret;

	home = get_var_value("HOME", *get_env());
	if (home)
	{
		if (*home)
			chdir_ret = chdir(home);
		else
			chdir_ret = chdir(old_pwd);
		ft_free(home);
	}
	else
		return (cd_error(old_pwd, NULL, "HOME not set", 1));
	if (chdir_ret == 0)
		return (cd_update(old_pwd));
	else
		return (cd_error(old_pwd, NULL, "HOME is not a valid directory", 1));
}

int	ft_cd(char **argv)
{
	char	*old_pwd;
	int		chdir_ret;

	old_pwd = getcwd(NULL, 0);
	if (argv[1] == 0)
		return (cd_home(old_pwd));
	else
		chdir_ret = chdir(argv[1]);
	if (chdir_ret == 0)
		return (cd_update(old_pwd));
	else
	{
		return (cd_error(old_pwd, NULL, "no such file or directory", 1));
		ft_free(old_pwd);
		return (error_builtin(old_pwd, argv[1], "no such file or directory", 1));
	}
}
