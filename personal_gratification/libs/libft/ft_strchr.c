/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:04:35 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:28:55 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	idx;

	if (!s && !*s)
		return (NULL);
	idx = 0;
	while (s[idx] != 0)
	{
		if (s[idx] == c)
			return ((char *)&s[idx]);
		idx++;
	}
	if (c == 0)
		return ((char *)&s[idx]);
	return (0);
}
