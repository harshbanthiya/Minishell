/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:14:21 by sfournie          #+#    #+#             */
/*   Updated: 2021/12/02 17:57:14 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

t_dlist	*sh_init_env(char **envp)
{
	t_dlist	*env;
	char	**split;

	if (envp == NULL)
		return (NULL);
	env = NULL;
	while (envp && *envp)
	{
		split = ft_splitn(*envp, '=', 2);
		if (split == NULL)
		{
			free_split(split);
			return (free_env(env));
		}
		lst_add_back(&env, lst_new_node(new_var(split[0], split[1])));
		ft_free(split);
		envp++;
	}
	return (env);
}

t_dlist	**get_env(void)
{
	return (&g_shell.env);
}

void	*free_env(void *ptr)
{
	t_dlist	*env;

	env = (t_dlist *)ptr;
	if (env != NULL)
	{
		lst_clear(env, free_var);
	}
	else
		free(ptr);
	return (NULL);
}

char	**env_list_to_envp(t_dlist *env_head)
{
	t_dlist	*temp;
	int		i;
	char	**output;
	char 	*save;

	temp = env_head;
	i = lst_size(temp);
	temp = env_head;
	save = NULL;
	output = malloc(sizeof(char *) * (i + 1));
	if (output == NULL)
		return (NULL);
	i = 0;
	while (temp)
	{
		output[i] = ft_strjoin(((t_var *)(temp->content))->key, "=");
		save = output[i];
		output[i] = ft_strjoin(output[i], ((t_var *)(temp->content))->value);
		ft_free(save);
		temp = temp->next;
		i++;
	}
	ft_free(temp);
	output[i] = NULL;
	return (output);
}

/* Split string by colon(':').
 *
 * str: Colon delimited string.
 * def_str: Default string.
 *
 * Return: An array of strings created as a result of string delimitation.
 *
 * ex:
 *   - args:
 *     - str: "::/"
 *     - default_str: "default"
 *   - return: ["default", "default", "/"]
 */

char	**get_colon_units(const char *str, const char *default_str)
{
	void	**result;
	char	*next;
	void	**tmparr;

	result = NULL;
	next = ft_strchr(str, ':');
	while (next)
	{
		tmparr = result;
		if (next - str == 0)
			result = ptrarr_add_ptr(result, ft_strdup(default_str));
		else
			result = ptrarr_add_ptr(result, ft_substr(str, 0, next - str));
		free(tmparr);
		str = next + 1;
		next = ft_strchr(str, ':');
	}
	tmparr = result;
	if (*str == '\0')
		result = ptrarr_add_ptr(result, ft_strdup(default_str));
	else
		result = ptrarr_add_ptr(result, ft_strdup(str));
	free(tmparr);
	return ((char **)result);
}
