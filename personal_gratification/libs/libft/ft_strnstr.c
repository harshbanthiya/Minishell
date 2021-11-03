/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:39:59 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:24:52 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ismatch(const char *str, const char *needle, int i, size_t len)
{
	int j;

	j = i;
	while (needle[j - i] != 0)
	{
		if (str[j] == needle[j - i])
			j++;
		else
			return (0);
		if (len-- == 0)
			return (0);
	}
	return (1);
}

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx;

	if (!haystack && !*haystack)
		return (0);
	idx = 0;
	if (needle[0] == 0)
		return (char *)&haystack[0];
	if (len == 0)
		return (0);
	while (needle[idx] != 0)
		if (len <= idx++)
			return (0);
	idx = 0;
	if (((len == 1 && needle[1] == 0) && haystack[0] == needle[0]))
		return (char *)&haystack[idx];
	while (haystack[idx] != 0 && len > 0)
	{
		if (haystack[idx] == needle[0])
			if (ft_ismatch(haystack, needle, idx, len))
				return (char *)&haystack[idx];
		idx++;
		len--;
	}
	return (0);
}
