/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_types.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:58:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/24 17:29:30 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* return 1 if (c) is a delimiter related to parsing */
int	parse_is_delimiter(char c)
{
	if (c == '\0' || c == '\'' || c == '\"' || c == ' '
		|| c == '$' || c == '\\')
		return (1);
	return (0);
}

int	parse_is_escaped(char *str, int i)
{
	if (i > 0 && str[i - 1] == '\\' && str[i] != ' ')
	{
		if (!parse_is_escaped(str, i - 1))
			return (1);
	}
	return (0);
}

int	parse_is_quotes(char *line, int i)
{
	char	quote;

	if ((line[i] == '\'' || line[i] == '\"') && !parse_is_escaped(line, i))
	{
		quote = line[i];
		if (parse_is_enclosed(line, i + 1, quote))
			return (1);
	}
	return (0);
}

int	parse_is_var(char *line, int i)
{
	if (line[i] == '$' && !parse_is_escaped(line, i))
		return (1);
	return (0);
}

/* return 1 if enclosed by (c) */
int	parse_is_enclosed(char *str, int i, char c)
{
	while (str && str[i])
	{
		if (str[i] == c && !parse_is_escaped(str, i))
			return (1);
		i++;
	}
	return (0);
}
