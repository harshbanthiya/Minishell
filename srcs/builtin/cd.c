/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/12 19:15:25 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static char	*parse_directory(char *path)
{
	char	**split;
	int		i;

	split = ft_split(path, '/');
	if (split == NULL)
		return (NULL);
	i = 0;
	while (split[i])
	{
		if (strcmp(split[i], "."))
		{
			split[i][0] = '\0';
		}
	}
	
}

int	ft_cd(char *path)
{
	char	*full_path;
	int		i;

	//attempt with current working directory
	if (chdir(path) == 0)
	{
		if (path[0] == '/')
			full_path = ft_strdup(path);
		else
			full_path = join_path_file(get_pwd(), path);
		full_path = parse_directory(full_path);
		set_pwd(full_path);
		return (1);
	}
	return (0);
}
