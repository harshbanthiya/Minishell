/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:38:16 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:27:18 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t idx;

	if (!src || !dst)
		return (0);
	idx = 0;
	if (dstsize != 0)
	{
		while (src[idx] != 0 && idx < (dstsize - 1))
		{
			dst[idx] = src[idx];
			idx++;
		}
		dst[idx] = 0;
	}
	idx = 0;
	while (src[idx] != 0)
		idx++;
	return (idx);
}
