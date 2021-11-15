/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:22:26 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 15:39:25 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

char	*ft_merge_split(char **split, char *delim)
{
	char	*merged;
	char	*temp;
	int		size;

	if (split == NULL)
		return (NULL);
	merged = ft_calloc(1, sizeof(char));
	while (*split || !*merged)
	{
		if (**split)
		{
			size = ft_strlen(*split) + ft_strlen(merged);
			temp = ft_calloc(size + 2, sizeof(char));
			ft_strcat(temp, merged);
			if (delim && *delim)
				ft_strcat(temp, delim);
			ft_strcat(temp, *split);
			ft_free(merged);
			merged = temp;
			split++;
		}
	}
	return (merged);
}
