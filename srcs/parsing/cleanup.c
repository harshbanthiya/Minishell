/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:07:38 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/05 18:12:50 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* clean the line into parsed_line, but over-malloced */
static void	parse_clean_it(char **parsed_line, char *line)
{
	char	quote;
	int		i;
	int		j;

	quote = '\0';
	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == '\\' && parse_is_escaped(line, i) && line[i + 1])
			i++;
		if (!quote && parse_is_quotes(line, i))
			quote = line[i];
		else if (line[i] == '\\' && !parse_is_escaped(line, i) && line[i + 1]
			&& line[i + 1] != ' ' && parse_is_escaped(line, i + 1))
			(*parsed_line)[j++] = line[++i];
		else if (line[i] != quote || (line[i] == quote && parse_is_escaped(line, i)))
			(*parsed_line)[j++] = line[i];
		else
			quote = '\0';
		i++;
	}
	(*parsed_line)[j] = '\0';
}

/* malloc a line and clean it *
*  once cleaned, it dup it into a string of appropriate size */
char	*parse_cleanup(char *line)
{
	char	*parsed_line;
	char	*save;

	if (line == NULL)
		return (NULL);
	parsed_line = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	parse_clean_it(&parsed_line, line);
	save = parsed_line;
	parsed_line = ft_strdup(parsed_line);
	ft_free(save);
	return (parsed_line);
}
