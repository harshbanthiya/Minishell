/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:39:23 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/22 11:59:54 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t			s_len;
	char			*new_str;

	s_len = ft_strlen(s);
	new_str = (char *)malloc(s_len + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, s_len + 1);
	return (new_str);
}

