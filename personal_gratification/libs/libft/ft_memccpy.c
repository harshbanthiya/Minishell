/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:46:23 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:31:41 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	idx;

	if (!dst && !src)
		return (0);
	idx = 0;
	while (idx < n)
	{
		((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
		if (((unsigned char *)dst)[idx] == (unsigned char)c)
			return (dst + idx + 1);
		idx++;
	}
	return (0);
}
