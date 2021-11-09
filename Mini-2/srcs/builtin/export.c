/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:47 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/08 16:47:04 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	strip_extra_spaces(char **token)
{
	char	*strip;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (token == NULL || *token == NULL)
		return ;
	strip = ft_strdup(*token);
	while (strip[i])
	{
		if (!(strip[i] == SPACE && strip[i + 1] == SPACE))
		{
			strip[j++] = strip[i];
		}
		i++;
	}
	strip[j] = '\0';
	free(*token);
	*token = strip;
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

	var = get_var(key, *lst);
	if (var != NULL)
	{
		if (value != NULL)
		{
			ft_free(var->value);
			var->value = ft_strdup(value);
		}
		return ;
	}
	if (value == NULL)
		var = new_var(ft_strdup(key), NULL);
	else
		var = new_var(ft_strdup(key), ft_strdup(value));
	lst_add_back(lst, lst_new_node(var));
}

int	ft_single_export(char *argv, t_dlist **lst)
{
	char	*key;
	char	*value;
	int		error;

	error = 0;
	export_split_var(&key, &value, argv);
	strip_extra_spaces(&value);
	if (key != NULL)
	{
		if (var_is_valid_key(key))
		{
			if (value == NULL && ft_strchr(argv, '='))
				ft_export_var(key, "", lst);
			else
				ft_export_var(key, value, lst);
		}
		else
		{
			error = 1;
			error_builtin("export", argv, "not a valid identifier", error);
		}
		ft_free(key);
		ft_free(value);
	}
	return (error);
}

int	ft_export(t_cmd *cmd, t_dlist **lst)
{	
	int		i;
	int		error;

	error = 0;
	if (cmd->argv[1] == NULL)
		return (ft_env_export(1));
	i = 1;
	while (cmd->argv[i] != NULL)
	{
		if (ft_single_export(cmd->argv[i], lst) != 0)
			error = 1;
		i++;
	}
	return (error);
}
