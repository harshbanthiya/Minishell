/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:52:46 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/29 18:45:44 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*replace_home_path(char *str, t_list *env_list)
{
	char	*home;

	if ((ft_strncmp(str, "~", 2) == 0))
	{
		home = get_env_val("HOME", env_list);
		return (home);
	}
	return (str);
}

void			print_err(char *pathname, char *argv_1)
{
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(pathname, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(argv_1, 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
}

char			*get_env_val(char *key, t_list *env_list)
{
	char	*env_val;
	int		key_len;

	key_len = ft_strlen(key);
	while (env_list)
	{
		if (!ft_strncmp(key, ((t_env *)(env_list->content))->key, key_len + 1))
		{
			env_val = ft_strdup(((t_env *)(env_list->content))->val);
			return (env_val);
		}
		env_list = env_list->next;
	}
	env_val = ft_strdup("");
	return (env_val);
}

void			free_env(void *env)
{
	if (((t_env *)env) == NULL)
		return ;
	free(((t_env *)env)->key);
	free(((t_env *)env)->val);
	free(((t_env *)env));
}

t_token			*create_token(char *line, int start, int end, int type)
{
	t_token	*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return (0);
	token->data = ft_strndup(&line[start], (end - start));
	token->type = type;
	return (token);
}
