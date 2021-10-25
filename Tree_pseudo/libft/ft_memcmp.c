/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:16:27 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 15:49:28 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int 	ft_memcmp(const void *str1, const void *str2, size_t max)
{
	unsigned char	c1;
	unsigned char	c2;

	while (max--)
	{
		c1 = *(unsigned char *) str1;
		c2 = *(unsigned char *) str2;
		if (c1 != c2)
			return (c1 - c2);
		str1++;
		str2++;
	}
	return (0);
}
