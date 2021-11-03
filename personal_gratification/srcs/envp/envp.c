/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:25:12 by cbaek             #+#    #+#             */
/*   Updated: 2021/02/01 12:13:33 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_env_one(t_list **list, t_env *env)
{
	t_list	*temp;
	int		key_len;

	key_len = ft_strlen(env->key);
	temp = *list;
	while (temp)
	{
		if (ft_strncmp((((t_env *)(temp->content))->key), \
				env->key, key_len + 1) == 0)
		{
			free(((t_env *)(temp->content))->val);
			((t_env *)(temp->content))->val = strdup(env->val);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(list, ft_lstnew(env));
}

void	put_splitted_env(t_env **env, char *envp)
{
	(*env)->key = ft_substr(envp, 0, ft_strchr(envp, (char)'=') - envp);
	(*env)->val = ft_substr(ft_strchr(envp, (char)'='), 1,
		ft_strlen(ft_strchr(envp, (char)'=')));
}

t_list		*set_env_list(char **envp)
{
	int		idx;
	t_env	*env;
	t_list	*result;

	result = 0x0;
	idx = 0;
	while (envp[idx] != NULL)
	{
		// temp = ft_split(envp[idx], '=');
		if (!(env = (t_env *)malloc(sizeof(t_env))))
			return (0);
		put_splitted_env(&env, envp[idx]);
		ft_lstadd_back(&result, ft_lstnew(env));
		idx++;
	}
	return (result);
}

void		print_env_list(t_list *env_head)
{
	t_list	*temp;

	temp = env_head;
	while (temp)
	{
		ft_putstr_fd(((t_env *)(temp->content))->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(((t_env *)(temp->content))->val, 1);
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}
}

char		**env_list_to_envp(t_list *env_head)
{
	t_list	*temp;
	int		i;
	char	**output;

	temp = env_head;
	i = ft_lstsize(temp);
	temp = env_head;
	if (!(output = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (temp)
	{
		output[i] = ft_strjoin(((t_env *)(temp->content))->key, "=");
		output[i] = ft_strjoin(output[i], ((t_env *)(temp->content))->val);
		temp = temp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}
