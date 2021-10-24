/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/24 18:29:44 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	dir_parser(char **split)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (split[i])
	{
		if (!ft_strcmp(split[i], ".") || !ft_strcmp(split[i], ".."))
		{
			if (j > 0 && !ft_strcmp(split[i], ".."))
			{
				ft_free(split[--j]);
				split[j] = NULL;
			}
			ft_free(split[i]);
			split[i] = NULL;
		}	
		else
			split[j++] = split[i];
		i++;
	}
}

/*	Expands . and .. and return the resulting string. 
	the received path is NOT freed.	*/
char	*parse_directory(char *path)
{
	char	**split;
	char	*new_path;

	split = ft_split(path, '/');
	if (split == NULL)
		return (NULL);
	dir_parser(split);
	new_path = merge_split(split, "/");
	free_split(split);
	return (new_path);
}

int	ft_cd(char **tokens)
{
	char	*old_pwd;
	char	*new_pwd;
	int		exit_code;

	old_pwd = getcwd(NULL, 0);
	if (chdir(tokens[0]) == 0)
	{
		new_pwd = getcwd(NULL, 0);
		if (get_var("OLDPWD", *get_env()))
			ft_export_var("OLDPWD", old_pwd, get_env());
		if (get_var("PWD", *get_env()))
			ft_export_var("PWD", new_pwd, get_env());
		set_pwd(new_pwd);
		exit_code = 1;
	}
	else
	{
		perror("cd: ");
		exit_code = 0;
	}
	ft_free(old_pwd);
	return (exit_code);
}
