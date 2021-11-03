/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:18:17 by sucho             #+#    #+#             */
/*   Updated: 2021/02/01 00:13:34 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*command(void)
{
	t_node	*redir_node;
	t_node	*simplecmd_node;
	t_node	*temp;

	redir_node = NULL;
	simplecmd_node = NULL;
	while (g_curtok)
	{
		if (((t_token *)g_curtok->content)->type == PIPE)
			break ;
		if (((t_token *)g_curtok->content)->type == SEMICOLON)
			break ;
		if ((temp = redir_list()) != NULL)
		{
			node_append_right(&redir_node, temp);
			printf("redir_node:%s\n", redir_node->data);
		}
		else if ((temp = simplecmd()) != NULL)
			node_append_right(&simplecmd_node, temp);
		else
			return (NULL);
	}
	if (redir_node != NULL)
	{
		redir_node->left = simplecmd_node;
		return (redir_node);
	}
	else
		return (simplecmd_node);
}

t_node	*redir_list(void)
{
	t_node	*result;
	char	*pathname;
	int		node_type;

	if (term_redir(&pathname, &node_type) == false)
		return (NULL);
	result = malloc(sizeof(t_node));
	if (node_type == GREAT)
		node_type = NODE_REDIR_OUT;
	else if (node_type == LESS)
		node_type = NODE_REDIR_IN;
	else
		node_type = NODE_REDIR_OUT_DBL;
	node_set_type(result, node_type);
	node_set_data(result, pathname);
	node_attach_branch(result, NULL, NULL);
	return (result);
}

t_node	*simplecmd(void)
{
	t_node	*result;
	char	*pathname;

	if (term(STRING, &pathname) == false)
		return (NULL);
	result = malloc(sizeof(*result));
	node_set_type(result, NODE_ARGUMENT);
	node_set_data(result, pathname);
	node_attach_branch(result, NULL, NULL);
	return (result);
}
