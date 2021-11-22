/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 12:55:35 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/19 12:56:29 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_countsplit(char **split)
{
	int	count;

	count = 0;
	while (split && *split)
	{
		split++;
		count++;
	}
	return (count);
}
