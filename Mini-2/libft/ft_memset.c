/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 10:42:45 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/10/11 17:57:07 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int chr, size_t len)
{
	void	*ptr;

	ptr = str;
	while (len--)
		*(char *)str++ = (unsigned char)chr;
	return (ptr);
}
