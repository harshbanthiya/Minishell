/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/18 20:39:33 by cbaek             #+#    #+#             */
/*   Updated: 2020/09/18 20:41:28 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *s1, size_t len)
{
	char	*str;
	size_t	idx;

	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (0);
	idx = 0;
	while (idx < len)
	{
		str[idx] = s1[idx];
		idx++;
	}
	str[idx] = '\0';
	return (str);
}
