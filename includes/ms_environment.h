/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_environment.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 18:43:33 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 12:30:27 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENVIRONMENT_H
# define MS_ENVIRONMENT_H
# include "minishell.h"
# include <stdbool.h>

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
void	var_set_value(char *key, char *value, t_dlist *list);
t_var	*new_var(char *key, char *value);
void	*dup_var(void *ptr);
void	print_var(int fd, t_var *var);
/* Expander */
bool	exp_join_str_or_env(char **result,
			char **str, int *len, bool *is_in_env);
bool	exp_will_toggle_env(bool is_in_env,
			bool is_in_noexpand, char *str, int len);
char	*exp_result_join_normal_str(char *result,
			char *str, int len);
char	*exp_expand_env_and_join(char *result,
			char *str, int env_len);
char	*expand_env_var(char *str);
/* for export with no options */
void	print_var_extra(int fd, t_var *var);

char	*get_pwd(void);
void	set_pwd(char *pwd);

void	*free_var(void *ptr);
void	*free_env(void *ptr);

#endif