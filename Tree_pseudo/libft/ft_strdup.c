/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:39:23 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 13:39:29 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char 	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*ptr;

	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (len--)
		ptr[i++] = *s++;
	ptr[i] = 0;
	return (ptr);
}
