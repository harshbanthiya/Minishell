/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:47 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/18 13:23:55 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

char	*strip_extra_spaces(char *token)
{
	char	*strip;
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (token == NULL)
		return (NULL);
	temp = ft_strdup(token);
	while (temp[i])
	{
		if (!(temp[i] == 32 && temp[i + 1] == 32))
		{
			temp[j++] = temp[i];
		}
		i++;
	}
	temp[j] = '\0';
	strip = ft_strdup(temp);
	ft_free(temp);
	return (strip);
}

void	export_split_var(char **key, char **value, char *argv)
{
	int		i;

	if (argv == NULL || !*argv)
	{
		*key = NULL;
		*value = NULL;
		return ;
	}
	*key = ft_strdup(argv);
	i = 0;
	while ((*key)[i] && (*key)[i] != '=')
		i++;
	if ((*key)[i] == '=')
	{
		*value = ft_strdup(&(*key)[i + 1]);
	}
	else
		*value = NULL;
	(*key)[i] = '\0';
}

void	ft_export_var(char *key, char *value, t_dlist **lst)
{	
	t_var	*var;
	char	*strip;

	strip = strip_extra_spaces(value);
	var = get_var(key, *lst);
	if (var != NULL)
	{
		if (strip != NULL)
		{
			ft_free(var->value);
			var->value = ft_strdup(strip);
		}
	}
	else
	{
		if (strip == NULL)
			var = new_var(ft_strdup(key), NULL);
		else
			var = new_var(ft_strdup(key), ft_strdup(strip));
		lst_add_back(lst, lst_new_node(var));
	}
	ft_free(strip);
}

int	ft_single_export(char *argv, t_dlist **lst)
{
	char	**split;
	int		exit_code;

	exit_code = 0;
	split = ft_splitn(argv, '=', 2);
	if (split != NULL)
	{
		if (var_is_valid_key(split[0]))
		{
			if (split[1] == NULL && ft_strchr(argv, '='))
				ft_export_var(split[0], "", lst);
			else
				ft_export_var(split[0], split[1], lst);
		}
		else
		{
			exit_code = error_builtin("export", split[0], "not a valid identifier", 1);
		}
		free_split(split);
	}
	return (exit_code);
}

int	ft_export(char **argv)
{	
	int		i;
	int		exit_code;
	t_dlist	**env;

	exit_code = 0;
	env = get_env();
	if (argv[1] == NULL)
		return (ft_env_export(1));
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_single_export(argv[i], env) != 0)
			exit_code = 1;
		i++;
	}
	return (exit_code);
}
