/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/05 16:43:53 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTIN_H	
# define MS_BUILTIN_H
# include "minishell.h"

typedef struct  s_cmd	t_cmd;

/* Return a double array of all builtins' names */
char	**init_builtins(void);

/* Return the global array of our builtin fcts */
char	**get_builtins(void);

int		is_builtin(char *name);

int		run_builtin(t_cmd *cmd, t_dlist **lst, int is_pipe);
int		ft_echo(t_cmd *cmd, t_dlist **lst);

/* Change working directory (PWD, OLDPWD, pwd and chdir()) */
int		ft_cd(t_cmd *cmd, t_dlist **lst);

/* Print a list of all shell variables */
int		ft_env(t_cmd *cmd, t_dlist **lst);

/* Parse and add/modify specified variable. */
int		ft_export(t_cmd *cmd, t_dlist **lst);
void	ft_export_var(char *key, char *value, t_dlist **lst);

/* Parse and remove specified variable, if it exists */
int		ft_unset(t_cmd *cmd, t_dlist **lst);
int		ft_unset_var(char *key, t_dlist **lst);

/* Print current working directory */
int		ft_pwd(t_cmd *cmd, t_dlist **lst);	

int		ft_exit(t_cmd *cmd, t_dlist **lst);

/* Printf minishell: builtname: str: msg  in fd 2 */
void	error_builtin(char *builtname, char *str, char *msg);

#endif