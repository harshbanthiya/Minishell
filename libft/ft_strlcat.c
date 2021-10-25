/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 10:43:19 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/10/11 18:00:29 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t max)
{
	size_t	i;

	i = 0;
	while (*dest && i < max)
	{
		i++;
		dest++;
	}
	while (*src && i + 1 < max)
	{
		*dest++ = *src++;
		i++;
	}
	if (i < max)
		*dest = 0;
	while (*src++)
		i++;
	return (i);
}
