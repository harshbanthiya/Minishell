/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:22:38 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/13 15:00:41 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char	*merge_split(char **split, char *delim)
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
