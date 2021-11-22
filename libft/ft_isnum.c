/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:06:29 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/22 14:27:27 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int  ft_isnum(char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\n' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while(ft_isdigit(*str) && *str)
        str++ ;
	while (*str == ' ' || *str == '\t' || *str == '\f'
		|| *str == '\r' || *str == '\n' || *str == '\v')
		str++;
	if (*str)
		return (0);
    return (1);
}
