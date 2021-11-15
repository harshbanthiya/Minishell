/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:54:57 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:26:36 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H

char	*strjoin_and_free_first(char *first, char *second);
char	*strjoin_and_free_both(char *first, char *second);
char	*strjoin_nullable_and_free_both(char *str_nullable, char *second);

#endif
