/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:51 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/05 16:39:38 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

// // Sebas, t'es rendu ici
// static int	var_key_is_valid(char *key)
// {
// 	char	quote;
// 	int		i;

// 	if (key == NULL)
// 		return (0);
// 	i = 0;
// 	quote = '\0';
// 	while (key[i])
// 	{
// 		if (parse_is_quotes(key, i) && (quote == '\0' || quote == key[i]))
// 		{
// 			if (quote == key[i])
// 				quote = '\0';
// 			else
// 				quote = key[i];
// 		}
// 		else
// 			return (0);
// 		if (key[i] == '\\' && parse_is_escaped(key, i))
// 			return (0);
// 	}
// }

int	ft_unset_var(char *key, t_dlist **lst)
{
	t_var	*var;
	t_dlist	*temp;

	if (key == NULL || lst == NULL)
		return (0);
	temp = *lst;
	while (temp != NULL)
	{
		var = (t_var *)temp->content;
		if (!ft_strncmp(key, var->key, ft_strlen(key)))
		{
			if (temp->prev == NULL)
				*lst = temp->next;
			lst_remove_node(temp, free_var);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

int	ft_unset(t_cmd *cmd, t_dlist **lst)
{
	int		i;

	if (cmd->argv[1] == NULL)
	{
		error_builtin("unset", NULL, "not enough arguments");
		return (1);
	}
	i = 1;
	while (cmd->argv[i])
	{
		ft_unset_var(cmd->argv[i++], lst);
	}
	return (0);
}
