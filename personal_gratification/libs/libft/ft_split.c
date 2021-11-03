/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 14:28:53 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/17 14:25:12 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_strs(char **strs, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static void	setstrs_mem(char **strs, char *s, char c, size_t idx)
{
	int	cnt;
	int	strlen;

	cnt = 0;
	strlen = 0;
	while (s[idx] == c)
		idx++;
	while (s[idx] != 0)
	{
		if ((idx != 0 && (s[idx - 1] != c && s[idx] == c))
				|| (s[idx + 1] == 0 && s[idx] != c))
		{
			if (s[idx + 1] == 0 && s[idx] != c)
				strlen++;
			if (!(strs[cnt++] = (char *)malloc(sizeof(char) * (strlen + 1))))
			{
				free_strs(strs, cnt - 1);
				return ;
			}
			strlen = 0;
		}
		else if (s[idx] != c)
			strlen++;
		idx++;
	}
}

static void	setstrs_str(char **strs, char *s, char c, size_t idx)
{
	int	cnt;
	int	strlen;

	cnt = 0;
	strlen = 0;
	while (s[idx] == c)
		idx++;
	while (s[idx] != 0)
	{
		if ((s[idx] != c) && (s[idx + 1] != 0))
			strs[cnt][strlen++] = s[idx];
		else if ((idx != 0 && s[idx - 1] != c) && s[idx] == c)
		{
			strs[cnt++][strlen] = 0;
			strlen = 0;
		}
		else if (s[idx + 1] == 0 && s[idx] != c)
		{
			strs[cnt][strlen] = s[idx];
			strs[cnt][strlen + 1] = 0;
		}
		idx++;
	}
}

static char	**get_null_strs(void)
{
	char	**null_strs;

	if (!(null_strs = (char **)malloc(sizeof(char *))))
	{
		return (0);
	}
	null_strs[0] = 0;
	return (null_strs);
}

char		**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	idx;
	size_t	cnt;

	if (!s)
		return (0);
	if (!*s)
		return (get_null_strs());
	idx = 0;
	cnt = 0;
	while (s[idx] == c)
		idx++;
	while (s[idx] != 0)
	{
		if (((idx != 0 && s[idx - 1] != c) && s[idx] == c) ||
				(s[idx + 1] == 0 && s[idx] != c))
			cnt++;
		idx++;
	}
	if (!(strs = (char **)malloc(sizeof(char *) * (cnt + 1))))
		return (0);
	strs[cnt] = 0;
	setstrs_mem(strs, (char *)s, c, 0);
	setstrs_str(strs, (char *)s, c, 0);
	return (strs);
}
