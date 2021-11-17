/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:54:18 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/17 14:15:01 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ms_utils.h"
#include "../../libft/libft.h"

/*
 * Join first and second string and free first string.
 */
char	*strjoin_and_free_first(char *first, char *second)
{
	char	*result;

	result = ft_strjoin(first, second);
	free(first);
	return (result);
}

/*
 * Join first and second string and free both strings.
 */
char	*strjoin_and_free_both(char *first, char *second)
{
	char	*result;

	result = ft_strjoin(first, second);
	free(first);
	free(second);
	return (result);
}

/*
 * If str_nullable is truthy return strjoin(str_nullable, second),
 *   otherwise, return strdup(second).
 *
 * str_nullable and second will be freed in this function.
 */
char	*strjoin_nullable_and_free_both(char *str_nullable, char *second)
{
	char	*result;

	if (str_nullable)
		result = ft_strjoin(str_nullable, second);
	else
		result = ft_strdup(second);
	ft_free(str_nullable);
	ft_free(second);
	return (result);
}
