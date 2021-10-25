/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 10:42:45 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 14:46:19 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void 	*ft_memset(void *str, int chr, size_t len)
{
	void	*ptr;

	ptr = str;
	while (len--)
		*(char *)str++ = (unsigned char)chr;
	return (ptr);
}
