/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 09:16:41 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 16:13:51 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t		sign;
	int			result;

	sign = 1;
	result = 0;
	while ((9 <= *nptr && *nptr <= 13) || (*nptr == 32))
	{
		nptr++;
	}
	while (*nptr == '-' || *nptr == '+')
	{
		if (result >= 1)
			return (0);
		if (*nptr == '-')
			sign = -1;
		result++;
		nptr++;
	}
	result = 0;
	while ('0' <= *nptr && *nptr <= '9')
	{
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * result);
}
