/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:16:30 by sfournie          #+#    #+#             */
/*   Updated: 2021/09/30 15:03:14 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"parsing.h"

int		ft_str_len(char *str)
{
	int	count;

	count = 0;
	while (str != NULL && *(str++))
		count++;
	return (count);
}

// Malloc and return a string with the content of (s1) and (s2), but also free (s1) and (s2).
char	*ft_str_fuse(char *s1, char *s2)
{
	char	*fused;
	int		i;
	int		j;
	
	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	fused = (char *)malloc(sizeof(char) * (ft_str_len(s1) + ft_str_len(s2) + 1));
	if (fused == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i])
		fused[j++] = s1[i++];
	i = 0;
	while (s2[i])
		fused[j++] = s2[i++];
	fused[j] = '\0';
	free(s1);
	return (fused);
}

// Will malloc a new string containing (s1) and (len) characters from (s2). Free (s1)
char	*ft_str_append(char *s1, char *s2, int len)
{
	char	*new;
	int		i;
	int		j;
	
	new = (char *)malloc(sizeof(char) * (ft_str_len(s1) + len + 1));
	if (new == NULL)
		return (s1);
	j = 0;
	i = 0;
	while (s1 != NULL && s1[i])
		new[j++] = s1[i++];
	i = 0;
	while (i < len)
		new[j++] = s2[i++];
	new[j] = '\0';
	if (s1 != NULL)
		free(s1);
	return (new);
}

// Count of amount of times (str) is found in (src)
int		ft_str_occur(char *src, char *str)
{
	int	count;
	int	i;
	int	j;
	int	len;

	count = 0;
	len = ft_str_len(str);
	if (src == NULL || str == NULL)
		return (0);
	i = 0;
	while (src[i])
	{
		j = 0;
		while (src[i + j] == str[j])
		{
			if (j++ == len - 1)
			{
				count++;
				break;
			}
		}
		i++; 
	}
	return (count);
}

/* Malloc and return a string containing the content of (src) 
* with every occurences of (remove) removed. Free (src) */
char	*ft_str_clean(char *src, char *remove)
{
	char	*clean;
	int		i;
	int		j;
	int		k;
	int		len;
	int		size;
	
	if (src == NULL || remove == NULL)
		return (src);
	len = ft_str_len(remove);
	size = ft_str_len(src) - (len * ft_str_occur(src, remove));
	clean = (char *)malloc(sizeof(char) * (size + 1));
	if (clean == NULL)
		return (src);
	i = 0;
	k = 0;
	while (src[i])
	{
		j = 0;
		if (src[i + j] == remove[j])
		{
			while (src[i + j] == remove[j])
			{
				if (j++ == (len - 1))
					i += len;
			}
		}
		else
			clean[k++] = src[i++];
	}
	clean[k] = '\0';
	free(src);
	return (clean);
}
