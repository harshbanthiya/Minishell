/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 15:58:55 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<sys/types.h>
# include	<termios.h>
# include	<signal.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<libft.h>

# include	"dlist.h"
# include	"ms_builtin.h"
# include	"ms_environment.h"
# include	"ms_parsing.h"
# include	"ms_shell.h"
# include	"ms_signal.h"
# include	"ms_utility.h"

/* Global shell structure declaration */
struct s_shell	g_shell;

/* Return a formated prompt */
char	*get_prompt(void);	
char	*ft_readline(void);
void	*ft_history(char *line);

/* Append (file) to (path), with a '/' in between */
char	*join_path_file(char *path, char *file);
/* Search for and return full path of specified "name" */
char	*get_path(char *name);

#endif