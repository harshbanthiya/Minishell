/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parsing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 15:46:05 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSING_H
# define MS_PARSING_H
# include "minishell.h"

/* Perform all required parsing on a given string */
char	*parse_cmdline(char *line);

/* Remove quotes and \character from a given string */
char	*parse_cleanup(char *line);

/* Expands all $variables in a given string *
*  this is done before quotes removal! */
char	*parse_expand_line(char *line);

/* Return the index of the next delimiter *
*  used to obtain the end of a $variable name */
int		parse_next_delim(char *str);

/* Return the amount of characters until the next $variable */
int		parse_next_var(char *line, int i);

int		parse_is_delimiter(char c);
int		parse_is_escaped(char *str, int i);
int		parse_is_quotes(char *line, int i);
int		parse_is_enclosed(char *str, int i, char c);
int		parse_is_var(char *line, int i);

#endif