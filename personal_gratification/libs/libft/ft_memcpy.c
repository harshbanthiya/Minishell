/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 12:07:40 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:30:19 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	idx;

	if (!dst && !src)
		return (0);
	idx = 0;
	while (idx < n)
	{
		((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
		idx++;
	}
	return (dst);
}
