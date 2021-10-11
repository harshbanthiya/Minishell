/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 11:47:35 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/10/11 18:01:24 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*src_str;
	char	*dest_str;
	void	*ptr;

	dest_str = (char *)dest;
	src_str = (char *)src;
	if (!dest_str && !src_str)
		return (0);
	ptr = dest;
	while (n--)
	{
		*dest_str++ = *src_str++;
	}
	return (ptr);
}
