/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:07:38 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/05 17:58:54 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* return the amount of characters before next delimiter */
int	parse_next_delim(char *str)
{
	int	i;

	i = 0;
	if (str && ft_isdigit(*str))
		return (1);
	while (str && !parse_is_delimiter(str[i]))
		i++;
	return (i);
}

int	parse_next_var(char *line, int i)
{
	int		count;
	int		flag_ignore;

	flag_ignore = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !parse_is_escaped(line, i))
		{
			if (parse_is_enclosed(line, i + 1, '\'') && flag_ignore == 0)
				flag_ignore = 1;
			else
				flag_ignore = 0;
		}
		if (parse_is_var(line, i) && !flag_ignore)
			return (count);
		i++;
		count++;
	}
	return (count);
}

char	*parse_cmdline(char *line)
{
	char	*expand_line;
	char	*parsed_line;

	if (line == NULL)
		return (NULL);
	expand_line = parse_expand_line(line);
	parsed_line = parse_cleanup(expand_line);
	ft_free(expand_line);
	return (parsed_line);
}
