/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 12:06:12 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/10/11 17:56:59 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	void	*ptr;

	if (!dest && !src)
		return (0);
	ptr = dest;
	if (src < dest)
	{
		src += len;
		dest += len;
		while (len--)
			*(char *)--dest = *(char *)--src;
	}
	else
		while (len--)
			*(char *)dest++ = *(char *)src++;
	return (ptr);
}
