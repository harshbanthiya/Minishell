/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:37:22 by cbaek             #+#    #+#             */
/*   Updated: 2020/08/18 19:13:21 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_baselen(const char *base)
{
	size_t idx;

	idx = 0;
	while (base[idx] != '\0')
		idx++;
	return (idx);
}

char			*ft_uitoa_base(unsigned int n, const char *base)
{
	unsigned int	tmp;
	size_t			baselen;
	size_t			str_size;
	size_t			flag;
	char			*str;

	tmp = n;
	baselen = get_baselen(base);
	str_size = 1;
	while (tmp /= baselen)
		str_size++;
	str = (char *)malloc(sizeof(char) * (str_size + 1));
	str[str_size] = '\0';
	flag = 0;
	while (str_size > flag)
	{
		str[str_size - 1] = base[n % baselen];
		str_size--;
		n /= baselen;
	}
	return (str);
}
