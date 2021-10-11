/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:16:27 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/10/11 18:09:51 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t max)
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
