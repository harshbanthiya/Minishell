/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 07:52:18 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 15:10:45 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char 	*ft_strrchr(const char *s, int c)
{
	char	*ptr;

	ptr = 0;
	while (1)
	{
		if (*s == (unsigned char)c)
			ptr = (char *)s;
		if (*s == 0)
			break ;
		s++;
	}
	return (ptr);
}	
