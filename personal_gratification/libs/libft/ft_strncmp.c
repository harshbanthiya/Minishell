/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 22:40:38 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:24:11 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (n == 0)
		return (0);
	if (s1[0] == 0 || s2[0] == 0)
		return ((unsigned char)s1[0] - (unsigned char)s2[0]);
	while (n > 0)
	{
		if (s1[i] == 0 || s2[i] == 0)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
		n--;
	}
	return ((unsigned char)s1[i - 1] - (unsigned char)s2[i - 1]);
}
