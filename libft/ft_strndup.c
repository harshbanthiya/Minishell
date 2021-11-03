/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:43:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/03 12:43:24 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s1, size_t len)
{
	char	*str;
	size_t	index;

	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (0);
	index = 0;
	while (index < len)
	{
		str[index] = s1[index];
		index++;
	}
	str[index] = '\0';
	return (str);
}
