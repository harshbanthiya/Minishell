/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 10:43:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/12/02 14:23:49 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t max)
{
	size_t	i;

	i = 0;
	while (dest && *dest && i < max)
	{
		i++;
		dest++;
	}
	while (dest && src && *src && i + 1 < max)
	{
		*dest++ = *src++;
		i++;
	}
	if (dest && i < max)
		*dest = 0;
	while (src && *src++)
		i++;
	return (i);
}
