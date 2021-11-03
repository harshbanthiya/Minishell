/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:19:53 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/10 14:41:00 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	getsize(size_t templen, unsigned int start, size_t len)
{
	if (templen - start > (size_t)len)
		return (size_t)len;
	else
		return (templen - start);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	templen;
	size_t	size;

	if (!s)
		return (0);
	templen = ft_strlen(s);
	if (templen <= start || len == 0)
	{
		if (!(str = (char *)malloc(sizeof(char))))
			return (0);
		str[0] = 0;
		return (str);
	}
	size = getsize(templen, start, len);
	if (!(str = (char *)malloc(sizeof(char) * (size + 1))))
		return (0);
	templen = 0;
	while (size > 0)
	{
		str[templen++] = s[start++];
		size--;
	}
	str[templen] = 0;
	return (str);
}
