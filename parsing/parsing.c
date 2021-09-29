/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 18:45:14 by sfournie          #+#    #+#             */
/*   Updated: 2021/09/28 20:53:20 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"parsing.h"

// return 0 if not enclosed
int		is_enclosed(char *str, char c)
{
	while (str && *str)
	{
		if (*(str++) == c)
			return (1);
	}
	return (0);
}

int		count_c(char *str, char delim)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (0);
	while (*str && *str != delim)
	{
		if (*str == '\"' && is_enclosed(str + 1, '\"'))
		{
			while (*(++str) != '\"')
				count++;
			count++;
		}
		str++;
		count++;
	}
	return (count);
}

char	*tokenize(char *str, char delim, int *i)
{
	char	*tok;
	int		size;
	int		j;

	size = count_c(&str[*i], delim);
	if (size == 0)
		return (NULL);
	tok = (char *)malloc(sizeof(char) * (size + 1));
	j = 0;
	while (j < size)
	{
		tok[j] = str[*i + j];
		j++;
	}
	tok[j] = '\0';
	*i = *i + j;
	return (tok);
	
	
}

t_tok *parse_input(char *str, char delim)
{
	t_tok	*tokens;
	char	*tok;
	int		i;

	tokens = NULL;
	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != delim)
		{
			tok = tokenize(str, delim, &i);
			if (tok == NULL)
				return (ft_free_tokens(tokens));
			ft_add_back(&tokens, ft_new_tok(tok));
		}
		else
			i++;
	}
	return (tokens);	
}

int	main(int argn, char **argv, char **envp)
{
	int		flag_exit = 0;
	char	*user_input;
	t_tok	*tokens;
	
	tokens = NULL;
	while (!flag_exit)
	{
		user_input = readline("prompt (\"quit\" to exit) : ");
		tokens = parse_input(user_input, ' ');
		if (tokens == NULL)
			break;
		ft_print_tokens(tokens);
	}
	return (0);
}