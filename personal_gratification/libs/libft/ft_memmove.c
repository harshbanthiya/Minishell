/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:19:56 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/06 15:18:07 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char			direction;
	size_t			i;
	unsigned char	*d_start;
	unsigned char	*s_start;

	if (dst == 0 && src == 0)
		return (0);
	direction = 1;
	s_start = (unsigned char *)src;
	d_start = (unsigned char *)dst;
	if (src < dst)
	{
		direction = -1;
		s_start = (unsigned char *)(src + len - 1);
		d_start = (unsigned char *)(dst + len - 1);
	}
	i = 0;
	while (i < len)
	{
		*d_start = *s_start;
		d_start += direction;
		s_start += direction;
		i++;
	}
	return (dst);
}
