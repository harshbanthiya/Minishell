/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_environment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/07 16:36:29 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENVIRONMENT_H
# define MS_ENVIRONMENT_H
# include "minishell.h"

/* Contain the name and value of environemnt variables */
typedef struct s_var
{
	char	*key;
	char	*value;
}				t_var;

/* Fill the environment list with (envp) */
t_dlist	*sh_init_env(char **envp);	

t_dlist	**get_env(void);
int		ft_env_export(int fd);
t_var	*get_var(char *key, t_dlist *list);
char	*get_var_value(char *key, t_dlist *list);
t_var	*new_var(char *key, char *value);
void	*dup_var(void *ptr);
void	print_var(int fd, t_var *var);

/* for export with no options */
void	print_var_extra(int fd, t_var *var);

char	*get_pwd(void);
void	set_pwd(char *pwd);

void	*free_var(void *ptr);
void	*free_env(void *ptr);

#endif