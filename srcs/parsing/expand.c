/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 16:11:40 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 15:44:01 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

/* receive a string starting with $ and return the following var key *
*  Example : $HELLO"hey" will return a malloced "HELLO" */
static char	*ex_get_key(char *str, int i)
{
	int	size;

	size = parse_next_delim(&str[i + 1]);
	return (ft_substr(&str[i], 1, size));
}

/* fill the *ex_line until the next $var (unquoted $) *
*  also move the i index */
static void	ex_append_until_var(char **ex_line, char *line, int *i)
{
	int		size;

	size = parse_next_var(line, *i);
	if (size > 0)
	{
		*ex_line = ft_strfuse(*ex_line, ft_substr(line, *i, size));
		*i += size;
	}
}

/* fill the *ex_line with the found $var value *
*  also move the i index */
static void	ex_append_var(char **ex_line, char *line, int *i)
{
	char	*ex_key;
	char	*ex_value;

	ex_key = ex_get_key(line, *i);
	ex_value = get_var_value(ex_key, *get_env());
	if (ex_value != NULL)
		*ex_line = ft_strfuse(*ex_line, ft_strdup(ex_value));
	*i += ft_strlen(ex_key) + 1;
	ft_free(ex_key);
}

char	*parse_expand_line(char *line)
{
	char	*ex_line;
	int		i;

	if (line == NULL)
		return (NULL);
	i = 0;
	ex_line = ft_calloc(1, sizeof(char));
	while (line[i])
	{
		if (parse_is_var(line, i))
			ex_append_var(&ex_line, line, &i);
		ex_append_until_var(&ex_line, line, &i);
	}
	return (ex_line);
}
