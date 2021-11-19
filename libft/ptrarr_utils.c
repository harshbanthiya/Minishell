/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptrarr_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:30:42 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/19 17:02:09 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ptrarr_len(void **ptrarr)
{
	size_t	i;

	i = 0;
	while (ptrarr[i])
		i++;
	return (i);
}

void	free_ptrarr(void **ptrarr)
{
	size_t	i;

	if (!ptrarr)
		return ;
	i = 0;
	while (ptrarr[i])
	{
		free(ptrarr[i]);
		ptrarr[i] = NULL;
		i++;
	}
	free(ptrarr);
}

void	*free_ptrarr_and_rtn_null(void **ptrarr)
{
	free_ptrarr(ptrarr);
	return (NULL);
}

void	free_ptrarr_and_assign_null(void ***ptrarr)
{
	free_ptrarr(*ptrarr);
	*ptrarr = NULL;
}

void	**ptrarr_add_ptr(void **ptrarr, void *ptr)
{
	size_t	arr_size;
	void	**new_ptrarr;

	arr_size = 0;
	if (ptrarr)
		arr_size = ptrarr_len(ptrarr);
	new_ptrarr = ft_calloc(arr_size + 2, sizeof(void *));
	if (!new_ptrarr)
		return (NULL);
	ft_memcpy(new_ptrarr, ptrarr, sizeof(void *) * arr_size);
	new_ptrarr[arr_size] = ptr;
	return (new_ptrarr);
}
