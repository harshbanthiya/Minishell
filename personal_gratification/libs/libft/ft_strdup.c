/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:12:12 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/06 18:36:29 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*duplicate;
	int		idx;
	int		d_idx;

	idx = 0;
	while (s1[idx] != 0)
		idx++;
	if ((duplicate = (char *)malloc(sizeof(char) * (idx + 1))) == 0)
		return (0);
	d_idx = 0;
	while (d_idx <= idx)
	{
		duplicate[d_idx++] = 0;
	}
	idx = 0;
	while (s1[idx] != 0)
	{
		duplicate[idx] = s1[idx];
		idx++;
	}
	return (duplicate);
}
