/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 23:14:23 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:26:34 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	len;
	size_t	idx;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != 0)
		len++;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	idx = 0;
	while (idx < len)
	{
		str[idx] = (*f)(idx, s[idx]);
		idx++;
	}
	str[idx] = 0;
	return (str);
}
