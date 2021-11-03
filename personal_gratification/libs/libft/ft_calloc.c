/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 11:54:44 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/10 14:39:58 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	len;

	len = size * count;
	if (!(ptr = (void *)malloc(len)))
		return (0);
	i = 0;
	while (len > 0)
	{
		((char *)ptr)[i++] = 0;
		len--;
	}
	return (ptr);
}
