/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 15:07:35 by sfournie          #+#    #+#             */
/*   Updated: 2021/09/28 20:17:21 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

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
#endif