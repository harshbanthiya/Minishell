/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:07:35 by sfournie          #+#    #+#             */
/*   Updated: 2021/09/30 14:12:58 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# define	ENV_VAR 

typedef struct	s_var
{
	char	*name;
	char	*value;
}				t_var;

typedef struct	s_tok
{
	char			*value;
	struct s_tok	*next;
}				t_tok;

t_tok	*ft_new_tok(char *str);
void	ft_add_front(t_tok *tok, t_tok *new);
void	ft_add_back(t_tok **tok, t_tok *new);
void	*ft_free_tokens(t_tok *tok);
void	ft_print_tokens(t_tok *tok);

// String utilities (str_utils.c)
int		ft_str_len(char *str);
char	*ft_str_fuse(char *s1, char *s2);
char	*ft_str_append(char *s1, char *s2, int len);
int		ft_str_occur(char *src, char *str);
char	*ft_str_clean(char *src, char *remove);

#endif