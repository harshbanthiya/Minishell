/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/13 14:59:53 by sfournie         ###   ########.fr       */
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

int	ft_cd(char *path)
{
	char	*full_path;
	char	*new_path;

	if (chdir(path) == 0)
	{
		if (path[0] == '/')
			full_path = ft_strdup(path);
		else
			full_path = join_path_file(get_pwd(), path);
		new_path = parse_directory(full_path);
		set_pwd(new_path);
		ft_free(full_path);
		return (1);
	}
	else
		perror("error in ft_cd");
	return (0);
}
