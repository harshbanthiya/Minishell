/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 14:07:38 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/19 19:10:41 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* return 1 if (c) is a delimiter related to parsing */
int		parse_is_delimiter(char c)
{
	if (c == '\0' || c == '\'' || c == '\"' || c == ' ' || c == '$' || c == '\\')
		return (1);
	return (0);
}

int		parse_is_special(char *str, int i)
{
	if (i > 0 && str[i - 1] == '\\' && str[i] != ' ')
	{
		if (!parse_is_special(str, i - 1))
			return (1);
	}
	return (0);
}

int		parse_is_quotes(char *line, int i)
{
	char	quote;
	if ((line[i] == '\'' || line[i] == '\"') && !parse_is_special(line, i))
	{
		quote = line[i];
		if (parse_is_enclosed(line, i + 1, quote))
			return (1);
	}
	return (0);
}

int		parse_is_var(char *line, int i)
{
	if (line[i] == '$' && !parse_is_special(line, i))
		return (1);
	return (0);
}

/* return 1 if enclosed by (c) */
int		parse_is_enclosed(char *str, int i, char c)
{
	while (str && str[i])
	{
		if (str[i] == c && !parse_is_special(str, i))
			return (1);
		i++;
	}
	return (0);
}

/* return the amount of characters before next delimiter */
int		parse_next_delim(char *str)
{
	int	i;

	i = 0;
	while (str && !parse_is_delimiter(str[i]))
		i++;
	return (i);
}



int		parse_next_var(char *line, int i)
{
	int		count;
	int		flag_ignore;

	flag_ignore = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !parse_is_special(line, i))
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

char	*parse_cleanup(char *line)
{
	char	*parsed_line;
	char	quote;
	int		i;
	int		j;

	if (line == NULL)
		return (NULL);
	quote = '\0';
	parsed_line = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == '\\' && parse_is_special(line, i) && line[i + 1])
			i++;
		if (!quote && parse_is_quotes(line, i))
			quote = line[i];
		else if	(line[i] == '\\' && !parse_is_special(line, i) && line[i + 1] && line[i + 1] != ' ')
			parsed_line[j++] = line[++i];
		else if (line[i] != quote || (line[i] == quote && parse_is_special(line, i)))
			parsed_line[j++] = line[i];
		else
			quote = '\0';
		i++;
	}
	line[j] = '\0';
	parsed_line = ft_strdup(parsed_line);
	return (parsed_line);
}

/* return a malloced string or NULL if (line) is NULL *
 * the string has the content of (line) with expanded variables */
char	*parse_expand_line(char *line)
{
	char	*save;
	char	*substr;
	char	*expand_line;
	char	*expand_var;
	char	*var_name;
	int		size;
	int		i;

	if (line == NULL)
		return (NULL);
	i = 0;
	expand_line = ft_calloc(1, sizeof(char));
	while (line[i])
	{
		if (parse_is_var(line, i))
		{
			size = parse_next_delim(&line[i + 1]);
			var_name = ft_substr(&line[i], 1, size);
			expand_var = get_var_value(var_name, *get_env());
			if (expand_var != NULL)
				expand_line = ft_strjoin(expand_line, expand_var);
			i += size + 1;
		}
		size = parse_next_var(line, i);
		if (size > 0)
		{
			save = expand_line;
			substr = ft_substr(line, i, size);
			expand_line = ft_strjoin(expand_line, substr);
			ft_free(save);
			ft_free(substr);
			i += size;
		}
	}
	return (expand_line);
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
