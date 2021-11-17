/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfuse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:36:03 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 15:39:45 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

/* free both strings and create a new one */
char	*ft_strfuse(char *str1, char *str2)
{
	char	*fused;

	if (str1 == NULL)
		return (str2);
	if (str2 == NULL)
		return (str1);
	fused = ft_strjoin(str1, str2);
	ft_free(str1);
	ft_free(str2);
	return (fused);
}
