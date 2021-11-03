/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 21:03:56 by chPaik            #+#    #+#             */
/*   Updated: 2020/04/12 23:32:16 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	getdigit(long long nbr)
{
	long long	i;

	if (nbr == 0)
		return (1);
	i = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static char			getsign(long long nbr)
{
	char		sign;

	if (nbr >= 0)
		sign = '+';
	else
	{
		nbr *= -1;
		sign = '-';
	}
	return (sign);
}

char				*ft_itoa(int n)
{
	char		*str;
	char		sign;
	long long	len;
	long long	memsize;

	len = (long long)n;
	sign = getsign(len);
	if (len < 0)
		len *= -1;
	memsize = getdigit(len) + ((sign - 43) / 2);
	if ((str = (char *)malloc(sizeof(char) * (memsize + 1))) == 0)
		return (0);
	str[memsize--] = 0;
	if (len == 0)
		str[0] = len + '0';
	while (len > 0)
	{
		str[memsize--] = (len % 10) + '0';
		len /= 10;
	}
	if (sign == '-')
		str[memsize] = sign;
	return (str);
}
