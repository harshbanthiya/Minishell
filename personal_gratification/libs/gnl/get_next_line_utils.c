/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:24:10 by cbaek             #+#    #+#             */
/*   Updated: 2020/07/30 15:58:24 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_nlc_addr(char *s)
{
	size_t	idx;

	if (s == 0)
		return (NULL);
	idx = 0;
	while (s[idx] != '\0')
	{
		if (s[idx] == '\n')
			return (&s[idx]);
		idx++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (s1 == NULL || s2 == NULL)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (len == 0)
	{
		if ((str = (char *)malloc(sizeof(char))) == NULL)
			return (0);
		str[0] = '\0';
		return (str);
	}
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (0);
	len = 0;
	while (*s1 != '\0')
		str[len++] = *s1++;
	while (*s2 != '\0')
		str[len++] = *s2++;
	str[len] = '\0';
	return (str);
}

char	*ft_strndup(char *s1, size_t len)
{
	char	*str;
	size_t	idx;

	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (0);
	idx = 0;
	while (idx < len)
	{
		str[idx] = s1[idx];
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
