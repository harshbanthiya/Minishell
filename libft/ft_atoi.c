/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 09:16:41 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/12/02 12:39:09 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	num_len(const char *str)
{
	int	i;

	i = 0;
	while (ft_isdigit(*str++))
		i++;
	return (i);
}

bool	is_long_overflow(const char *nptr, int sign)
{
	if (num_len(nptr) > 19)
		return (true);
	if (num_len(nptr) == 19)
	{
		if (sign == -1 && ft_strncmp(nptr, "9223372036854775808", 19) > 0)
			return (true);
		if (sign == 1 && ft_strncmp(nptr, "9223372036854775807", 19) > 0)
			return (true);
	}
	return (false);
}

bool	is_int_overflow(const char *nptr, int sign)
{
	if (num_len(nptr) > 10)
		return (true);
	if (num_len(nptr) == 10)
	{
		if (sign == -1 && ft_strncmp(nptr, "2147483648", 10) > 0)
			return (true);
		if (sign == 1 && ft_strncmp(nptr, "2147483647", 10) > 0)
			return (true);
	}
	return (false);
}

int	ft_atoi(const char *nptr)
{
	unsigned int	num;
	int				np;

	np = 1;
	num = 0;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\f'
		|| *nptr == '\r' || *nptr == '\n' || *nptr == '\v')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			np = -1;
	if (is_long_overflow(nptr, np))
	{
		if (np == 1)
			return (-1);
		else
			return (0);
	}
	while (ft_isdigit(*nptr))
		num = num * 10 + (*nptr++ - '0');
	return ((int)(np * num));
}
