/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:42:46 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 15:13:10 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_included(char a, char const *set)
{
	while (*set)
		if (a == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	char	*begin;
	char	*until;
	size_t	len;

	begin = (char *)s1;
	until = begin + ft_strlen(s1);
	while (*begin && is_included(*begin, set))
		begin++;
	while (begin < until && is_included(*(until - 1), set))
		until--;
	len = until - begin + 1;
	ptr = malloc(len);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, begin, len);
	return (ptr);
}
