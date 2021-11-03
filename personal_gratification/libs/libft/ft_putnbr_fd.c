/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 23:06:51 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/09 16:08:15 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long long	get_mt_nb(long long u_nb)
{
	long long	mt_nb;

	mt_nb = 1;
	while (u_nb >= 10)
	{
		mt_nb *= 10;
		u_nb /= 10;
	}
	return (mt_nb);
}

void				ft_putnbr_fd(int n, int fd)
{
	long long	u_nb;
	long long	mt_nb;
	long long	prnt_nb;

	u_nb = (long long)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		u_nb *= -1;
	}
	mt_nb = get_mt_nb(u_nb);
	while (1)
	{
		prnt_nb = '0' + (((u_nb % (mt_nb * 10)) - (u_nb % (mt_nb))) / mt_nb);
		write(fd, &prnt_nb, 1);
		if (mt_nb < 10)
			break ;
		mt_nb /= 10;
	}
}
