/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:43:01 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/22 12:29:06 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;

	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	*substr = '\0';
	if (start >= ft_strlen(s))
		return (substr);
	ft_strlcpy(substr, s + start, len + 1);
	return (substr);
}
