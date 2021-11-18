/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:54:57 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/18 12:57:43 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H

char	*strjoin_and_free_first(char *first, char *second);
char	*strjoin_and_free_both(char *first, char *second);
char	*strjoin_nullable_and_free_both(char *str_nullable, char *second);

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
