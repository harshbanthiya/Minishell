/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 13:38:24 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/05/15 14:48:35 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbr_fd_sub(int fd, int n)
{
	char	c;

	if (n / 10)
		ft_putnbr_fd_sub(fd, n / 10);
	c = '0' + n % 10;
	write (fd, &c, 1);
}

void 	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		ft_putnbr_fd_sub(fd, n);
	}
}
