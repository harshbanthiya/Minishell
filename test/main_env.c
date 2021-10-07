/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/04 08:31:44 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_strlen(char *s)
{
	int	count;

	count = 0;
	while (*(s++))
		count++;
	return (count);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n <= 0)
		return (0);
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (n-- > 0 && *s1 == *s2)
	{
		if (*s1 == '\0' || *s2 == '\0' || n == 0)
			break ;
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	*ft_free_split(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
	return (NULL);
}

static size_t	ft_countwords(char const *s, char delimiter)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[++i])
	{
		if (s[i] && s[i] == delimiter && s[i - 1] != delimiter)
			count++;
	}
	if (i != 0 && s[i - 1] != delimiter)
		count++;
	return (count);
}

static size_t	ft_countchar(char const *s, size_t pos, char delimiter)
{
	size_t	count;

	count = 0;
	while (s[pos] && s[pos] != delimiter)
	{
		count++;
		pos++;
	}
	return (count);
}

static	char	*ft_moveword(char const *s, size_t *pos, char delimiter)
{
	char	*str;
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_countchar(s, *pos, delimiter);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	while (i < size)
	{
		str[i++] = s[*pos];
		*pos = *pos + 1;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	index;
	size_t	pos;
	size_t	words;

	if (s == NULL)
		return (NULL);
	pos = -1;
	index = 0;
	words = ft_countwords(s, c);
	split = (char **)malloc(sizeof(char *) * (words + 1));
	if (split == NULL)
		return (NULL);
	while (words != 0 && s[++pos] && pos < ft_strlen(s))
	{
		if (s[pos] != c)
		{
			split[index] = ft_moveword(s, &pos, c);
			if (split[index++] == NULL)
				return (ft_free_split(split));
		}
	}
	split[index] = NULL;
	return (split);
}

int	main(void)
{
	char	*user_in;
	t_list	**env;

	ft_init_shell();
	user_in = readline("export NAME=value : ");
	while (user_in != NULL && *user_in)
	{
		env = ft_get_env();
		ft_export(user_in, env);
		ft_env(1);
		user_in = readline("export NAME=value : ");
	}
	user_in = readline("unset NAME : ");
	while (user_in != NULL && *user_in)
	{
		env = ft_get_env();
		ft_unset(user_in, env);
		ft_env(1);
		user_in = readline("unset NAME : ");
		
	}
	
}