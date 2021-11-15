/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:39:22 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:36:41 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "../../includes/ms_path.h"
#include "../../includes/minishell.h"

bool	is_directory(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) != 0)
		return (false);
	if (S_ISDIR(buf.st_mode))
		return (true);
	return (false);
}

/*
 * concatenate dirpath, "/" and filename.
 */
char	*path_join(char *dirpath, char *filename)
{
	char	*tmp;
	char	*result;

	if (ft_strlen(dirpath) == 0 || dirpath[ft_strlen(dirpath) - 1] != '/')
		tmp = ft_strjoin(dirpath, "/");
	else
		tmp = ft_strdup(dirpath);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, filename);
	free(tmp);
	return (result);
}

/*
 * Returns path of parent directory.
 *
 * path: Path of the target directory.
 * Return: Path of parent directory.
 */
char	*get_parent_dir(char *path)
{
	char	*result;

	result = ft_substr(path, 0, ft_strrchr(path, '/') - path);
	if (result && ft_strlen(result) == 0)
	{
		free(result);
		result = ft_strdup("/");
	}
	return (result);
}

/*
 * If user has access permission to the path,
 *   return True. Otherwise, return false.
 */
bool	is_executable(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		return (false);
	if (!(buf.st_mode & S_IXUSR))
		return (false);
	if (!(buf.st_mode & S_IRUSR))
		return (false);
	return (true);
}
