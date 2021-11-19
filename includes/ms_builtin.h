/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/18 16:24:24 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTIN_H	
# define MS_BUILTIN_H
# include "minishell.h"

typedef int		t_builtin_cmd(char **);
/* Return the global array of our builtin fcts */
int				get_builtins(void);
int				is_builtin(char *name);
int				ft_echo(char **argv);
t_builtin_cmd	*get_builtin_func(char *cmd_name);
/* Change working directory (PWD, OLDPWD, pwd and chdir()) */
int				ft_cd(char **argv);
/* Print a list of all shell variables */
int				ft_env(char **argv);
/* Parse and add/modify specified variable. */
int				ft_export(char **argv);
void			ft_export_var(char *key, char *value, t_dlist **lst);
/* Parse and remove specified variable, if it exists */
int				ft_unset(char **argv);
int				ft_unset_var(char *key, t_dlist **env);
/* Print current working directory */
int				ft_pwd(char **argv);	
int				ft_exit(char **argv);
/* printf minishell: builtname: str: msg  in fd 2 */
int				error_builtin(char *builtname, char *str, char *msg, int code);

#endif
