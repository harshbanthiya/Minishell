/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/17 17:41:08 by sfournie         ###   ########.fr       */
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
	set_pwd(new_pwd);
	return (0);
}

int	ft_cd(char **argv)
{
	char	*old_pwd;
	char	*home;
	int		chdir_ret;

	old_pwd = getcwd(NULL, 0);
	if (chdir(argv[1]) == 0)
	{
		home = get_var_value("HOME", *get_env());
		if (home)
		{
			if (*home)
				chdir_ret = chdir(home);
			else
				chdir_ret = chdir(old_pwd);
		}
		else
		{
			ft_free(old_pwd);
			return (error_builtin("cd", NULL, "HOME not set", 1));
		}
	}
	else
		chdir_ret = chdir(argv[0]);
	if (chdir_ret == 0)
		return (cd_update(old_pwd));
	else
	{
		ft_free(old_pwd);
		return (error_builtin("cd", argv[0], "no such file or directory", 1));
	}
}
