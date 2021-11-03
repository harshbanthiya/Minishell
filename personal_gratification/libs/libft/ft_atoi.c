/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 09:23:24 by cbaek             #+#    #+#             */
/*   Updated: 2020/04/12 23:34:27 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	idx;
	int	result;
	int	sign;

	idx = 0;
	result = 0;
	sign = 0;
	while (str[idx] == ' ' || (str[idx] > 8 && str[idx] < 14))
		idx++;
	if (str[idx] == '+' || str[idx] == '-')
		sign = -(str[idx++] - 44);
	if (str[idx] >= '0' && str[idx] <= '9')
	{
		if (sign == 0)
			sign = 1;
		while (str[idx] >= '0' && str[idx] <= '9')
			result = (result * 10) + (str[idx++] - '0');
	}
	return (sign * result);
}
