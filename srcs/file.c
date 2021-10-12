/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 21:43:04 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/12 17:02:02 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char	*join_path_file(char *path, char *file)
{
	int		i;
	size_t	size;
	char	*str;

	if (path == NULL || file == NULL)
		return (NULL);
	i = 0;
	size = ft_strlen(path) + ft_strlen(file) + 2;
	str = (char *)malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	while (*path)
		str[i++] = *(path++);
	str[i++] = '/';
	while (*file)
		str[i++] = *(file++);
	str[i] = '\0';
	return (str);
}

/* 0 for stdin, 1 for stdout, 2 for stderr. return -1 on error */
int	get_fd(int std)
{
	if (g_shell.fd != NULL && std >= 0 && std <= 2)
		return (g_shell.fd[std]);
	return (-1);
}