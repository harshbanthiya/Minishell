/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 11:45:58 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 15:01:59 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t max)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (src[i] && i + 1 < max)
	{
		dest[i] = src[i];
		i++;
	}
	if (max != 0)
		dest[i] = 0;
	while (src[i])
		i++;
	return (i);
}
