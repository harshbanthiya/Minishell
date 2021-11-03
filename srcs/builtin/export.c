/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:47 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/02 16:58:42 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static int	is_valid_export(char *token)
{
	if (token == NULL || token[0] == '=')
		return (0);
	else
		return (1);
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

int	ft_export(t_cmd *cmd, t_dlist **lst)
{	
	char	**split;
	int		i;

	if (cmd->argv[1] == NULL)
		return (ft_env_export(1));
	i = 1;
	while (cmd->argv[i] != NULL)
	{
		if (is_valid_export(cmd->argv[i]))
		{
			split = ft_splitn(cmd->argv[i], '=', 2);
			if (split != NULL)
			{
				if (split[1] == NULL && ft_strchr(cmd->argv[i], '='))
					ft_export_var(split[0], "", lst);
				else
					ft_export_var(split[0], split[1], lst);
				free_split(split);
			}
		}
		i++;
	}
	return (0);
}
