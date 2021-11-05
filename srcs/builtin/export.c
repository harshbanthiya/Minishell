/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:47 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/05 15:17:38 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

// static int	is_valid_export(char *token)
// {
// 	if (token == NULL || token[0] == '=' || ft_isdigit(token[0])
// 		return (0); // not a valid identifier
// 	else
// 		return (1);
// }

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
	char	**split;
	int		error;
	
	error = 0;
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
			error_builtin("export", split[0], "not a valid identifier");
			error = 1;
		}
		free_split(split);
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
