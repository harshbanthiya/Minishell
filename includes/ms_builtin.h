/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 15:45:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTIN_H	
# define MS_BUILTIN_H
# include "minishell.h"

/* Return a double array of all builtins' names */
char	**init_builtins(void);

/* Return the global array of our builtin fcts */
char	**get_builtins(void);

int		is_builtin(char *name);

int		run_builtin(char *cmd, char **args);
int		ft_echo(char **tokens, int fd);

/* Change working directory (PWD, OLDPWD, pwd and chdir()) */
int		ft_cd(char **args);

/* Print a list of all shell variables */
void	ft_env(int fd);

/* Parse and add/modify specified variable. */
void	ft_export(char **tokens, t_dlist **lst);
void	ft_export_var(char *key, char *value, t_dlist **lst);

/* Parse and remove specified variable, if it exists */
int		ft_unset(char **tokens, t_dlist **lst);
int		ft_unset_var(char *key, t_dlist **lst);

/* Print current working directory */
int		ft_pwd(int fd);	

int		ft_exit(void);

#endif