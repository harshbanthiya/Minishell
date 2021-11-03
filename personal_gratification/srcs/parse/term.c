/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:10:17 by sucho             #+#    #+#             */
/*   Updated: 2021/02/01 00:15:45 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		term(int token_type, char **arg)
{
	if (g_curtok == NULL)
		return (FALSE);
	if (((t_token *)(g_curtok)->content)->type == token_type)
	{
		if (arg != NULL)
			*arg = ft_strdup(((t_token *)g_curtok->content)->data);
		g_curtok = g_curtok->next;
		return (TRUE);
	}
	return (FALSE);
}

int		term_redir(char **arg, int *node_type)
{
	t_token *current;

	if (g_curtok == NULL)
		return (FALSE);
	current = (t_token *)(g_curtok->content);
	if (current->type == GREAT ||
		current->type == LESS ||
		current->type == GREATGREAT)
	{
		*node_type = current->type;
		if (g_curtok->next == NULL)
			return (FALSE);
		g_curtok = g_curtok->next;
		current = (t_token *)(g_curtok->content);
		if (current->type == STRING)
		{
			if (arg != NULL)
			{
				*arg = ft_strdup(((t_token *)g_curtok->content)->data);
			}
			g_curtok = g_curtok->next;
			return (TRUE);
		}
	}
	return (FALSE);
}
