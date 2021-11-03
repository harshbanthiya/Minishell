/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:13:49 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:26:05 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_start(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*start;
	char	*backup;

	i = 0;
	start = (char *)s1;
	while (s1[i] != 0)
	{
		backup = start;
		j = 0;
		while (set[j] != 0)
		{
			if (s1[i] == set[j++])
			{
				start += 1;
				break ;
			}
		}
		if (start == backup)
			return (start);
		i++;
	}
	return (start);
}

static int	get_trimlen(char *str, char const *set, size_t len)
{
	size_t	j;
	size_t	backup;

	while (len > 0)
	{
		backup = len;
		j = 0;
		while (set[j] != 0)
		{
			if (str[len - 1] == set[j])
			{
				len--;
				break ;
			}
			j++;
		}
		if (len == backup)
			return (len);
	}
	return (len);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*s_ptr;
	char	*str;
	size_t	idx;
	size_t	trimlen;

	if (!s1 || !set)
		return (0);
	idx = 0;
	trimlen = 0;
	s_ptr = get_start(s1, set);
	trimlen = get_trimlen(s_ptr, set, ft_strlen(s_ptr));
	if (!(str = (char *)malloc(sizeof(char) * (trimlen + 1))))
		return (0);
	while (idx < trimlen)
	{
		str[idx] = s_ptr[idx];
		idx++;
	}
	str[idx] = 0;
	return (str);
}
