/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 12:08:04 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 14:39:19 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void 	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n--)
	{
		*(char *)dest++ = *(char *)src;
		if (*(unsigned char *)src++ == (unsigned char) c)
			return (dest);
	}
	return (0);
}
