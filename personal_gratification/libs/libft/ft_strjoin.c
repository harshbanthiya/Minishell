/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 10:00:11 by cbaek             #+#    #+#             */
/*   Updated: 2020/09/18 20:32:11 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (len == 0)
	{
		str = (char *)malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (0);
	len = 0;
	while (*s1 != 0)
		str[len++] = *s1++;
	while (*s2 != 0)
		str[len++] = *s2++;
	str[len] = '\0';
	return (str);
}
