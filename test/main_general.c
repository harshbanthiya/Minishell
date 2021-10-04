/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:51:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/04 09:50:14 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	if (fd >= 0 && fd <= 2)
	{
		while (*s)
			write(fd, s++, 1);
	}
}

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

static int	handle_input(char *str, int fd)
{
	if (!str)
		return (0);
	if (!ft_strncmp(str, "export", 6))
		ft_export(str + 7, ft_get_env());
	else if (!ft_strncmp(str, "unset", 5))
		ft_unset(str + 6, ft_get_env());
	else if (!ft_strncmp(str, "echo", 4))
		ft_echo(str + 5, 1);
	else if (!ft_strncmp(str, "env", 3))
		ft_env(1);
	return (1);
}

int	main(void)
{
	char	*user_in;
	t_list	**env;

	ft_init_shell();
	user_in = readline("prompt : ");
	while (user_in != NULL && *user_in)
	{
		add_history(user_in);
		handle_input(user_in, 1);
		user_in = readline("prompt : ");
	}	
}