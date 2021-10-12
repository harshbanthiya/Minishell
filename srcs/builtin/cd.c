/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/11 22:12:56 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_cd(char *path)
{
	char	**paths;
	char	*full_path;
	t_var	*path_var;
	int		i;
	int		found;

	found = 0;
	//attempt with current working directory
	if (chdir(path) == 0)
	{
		full_path = join_path_file(get_pwd(), path);
		set_pwd(full_path);
		return (0);
	}
	path_var = get_var("PATH", *get_env());
	if (path_var == NULL)
		return (0);
	paths = ft_split(path_var->value, ':');
	if (paths == NULL)
		return (0);
	i = 0;
	//attempt with every path in the PATH variable
	while (paths[i])
	{
		full_path = join_path_file(paths[i++], path);
		if (chdir(full_path) == 0)
		{
			set_pwd(full_path);
			found = 1;
			break;
		}
		free(full_path);
	}
	if (found == 0)
		perror(NULL);
	free_split(paths);
	return (0);
}
