/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 15:23:46 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 15:24:53 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_and_assign_null(void **p)
{
	free(*p);
	*p = NULL;
}

void	*free_and_rtn_ptr(void *p, void *val)
{
	free(p);
	return (val);
}
