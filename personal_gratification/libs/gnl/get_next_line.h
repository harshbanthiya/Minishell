/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 11:12:08 by cbaek             #+#    #+#             */
/*   Updated: 2020/12/16 11:44:31 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define GNL_NL 1
# define GNL_ERROR -1
# define GNL_EOF 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 64
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
char	*ft_get_nlc_addr(char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strndup(char *s1, size_t len);
#endif
