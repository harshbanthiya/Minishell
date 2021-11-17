/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_node2string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:19:28 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/17 08:19:45 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_utils.h"

/* Convert AST string node to string */
char	*string_node2string(t_parse_node_string *string_node,
							bool add_quotes)
{	
	char	*result;

	result = ft_strdup("");
	check_malloc_success("string_node2string", result);
	while (string_node)
	{
		if (add_quotes && string_node->type == TOKTYPE_NON_EXPANDABLE)
			result = strjoin_and_free_first(result, "\'");
		else if (add_quotes && string_node->type == TOKTYPE_EXPANDABLE_QUOTED)
			result = strjoin_and_free_first(result, "\"");
		check_malloc_success("string_node2string", result);
		result = strjoin_and_free_first(result, string_node->text);
		check_malloc_success("string_node2string", result);
		if (add_quotes && string_node->type == TOKTYPE_NON_EXPANDABLE)
			result = strjoin_and_free_first(result, "\'");
		else if (add_quotes && string_node->type == TOKTYPE_EXPANDABLE_QUOTED)
			result = strjoin_and_free_first(result, "\"");
		check_malloc_success("string_node2string", result);
		if (string_node->next)
			string_node = string_node->next->content.string;
		else
			break ;
	}
	return (result);
}
