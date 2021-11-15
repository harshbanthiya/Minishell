/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utility.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 09:11:40 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILITY_H	
# define MS_UTILITY_H
# include "minishell.h"

/* Return a new malloced string with no successive spaces */
char	*strip_extra_spaces(char *token);

/* Return a string with the content of each split[n] *
*  separated by (delim). */
char	*ft_merge_split(char **split, char *delim);

/* Split up to (n) times */
char	**ft_splitn(char const *s, char c, int n);

/* Create a new string with the content of str1 and str2. *
*  Free both strings. */
char	*ft_strfuse(char *str1, char *str2);

/* Generic free that will free() and return NULL */
void	*ft_free(void *ptr);	
void	*free_split(char **s);

#endif