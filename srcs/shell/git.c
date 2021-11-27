/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:32:01 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/27 11:40:56 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static char	*isolate_git(char *git)
{
	char	*head_str;

	if (!git)
		return (NULL);
	head_str = ft_strnstr(git, "refs/heads/", ft_strlen(git));
	if (head_str)
		return (ft_substr(head_str, 11, ft_strlen(head_str) - 11));
	return (NULL);
}

static char	*read_git(char *dir)
{
	char	buff[100];
	char	*path;
	int		bytes;
	int		fd;

	if (!dir || !*dir)
		return (NULL);
	path = ft_strjoin(dir, "/.git/HEAD");
	fd = open(path, O_RDONLY);
	ft_free(path);
	if (fd >= 0)
	{
		bytes = read(fd, buff, 99);
		if (bytes > 0)
			buff[bytes - 1] = '\0';
		close(fd);
		return (isolate_git((char *)buff));
	}
	if (ft_strrchr(dir, '/'))
	{
		close(fd);
		*ft_strrchr(dir, '/') = '\0';
		return (read_git(dir));
	}
	return (NULL);
}

void	append_git(char *prompt)
{
	char	*git;
	char	*dir;

	dir = ft_strdup(get_pwd());
	git = read_git(dir);
	ft_free(dir);
	if (git)
	{
		ft_strlcat(prompt, C_BLUE, PROMPT_SIZE);
		ft_strlcat(prompt, " git:(", PROMPT_SIZE);
		ft_strlcat(prompt, C_RED, PROMPT_SIZE);
		ft_strlcat(prompt, git, PROMPT_SIZE);
		ft_strlcat(prompt, C_BLUE, PROMPT_SIZE);
		ft_strlcat(prompt, ")", PROMPT_SIZE);
		ft_strlcat(prompt, C_NO, PROMPT_SIZE);
		ft_free(git);
	}
}
