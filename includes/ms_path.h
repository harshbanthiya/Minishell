/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:42:31 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/18 16:35:46 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PATH_H
# define MS_PATH_H
# include "../libft/libft.h"

bool	is_directory(char *path);
char	*path_join(char *dirpath, char *filename);
char	*get_parent_dir(char *path);
bool	is_executable(char *path);

#endif