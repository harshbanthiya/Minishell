/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:21:27 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/12/01 18:38:46 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/ms_utils.h"

static bool	cmd_str_node_add_back(t_cmd_str_node ***str_node_arr,
		char *text, t_token_type tok_type)
{
	t_cmd_str_node		*new_node;
	t_cmd_str_node		**tmp;

	new_node = malloc(sizeof(t_cmd_str_node));
	if (!new_node)
		return (false);
	new_node->text = text;
	new_node->type = tok_type;
	tmp = *str_node_arr;
	*str_node_arr = (t_cmd_str_node **)ptrarr_add_ptr(
			(void **)*str_node_arr, new_node);
	free(tmp);
	if (!*str_node_arr)
		return (false);
	return (true);
}

/* 
	Convert AST str_node to cmd_str_node with variabe expansion
*/
static t_cmd_str_node	**ast_str2cmd_str(t_parse_node_string *str_node)
{
	t_cmd_str_node	**result;
	char			*expanded_str;

	result = NULL;
	while (str_node)
	{
		if (str_node->type == TOKTYPE_NON_EXPANDABLE)
			expanded_str = ft_strdup(str_node->text);
		else
			expanded_str = expand_env_var(str_node->text);
		if (!expanded_str
			|| !cmd_str_node_add_back(&result, expanded_str, str_node->type))
			return (NULL);
		if (str_node->next)
			str_node = str_node->next->content.string;
		else
			str_node = NULL;
	}
	return ((t_cmd_str_node **)result);
}

/* 
	Process TOKTYPE_EXPANDABLE 
	*next_str will be freed in the function when the function update next_str;
	result: pointer of arrray of string 
	next_str: pointer of string which will be added to **result in next call;
	text: str_node->text
	reutrn: updated next_str;
*/

static char	*expandable_node2strarr(void ***result,
		char *next_str, char *text)
{
	int		len;

	len = 0;
	while (text[len])
	{
		if (text[len] == ' ' && len == 0)
			text++;
		else if (text[len] == ' ' && len)
		{
			next_str = strjoin_nullable_and_free_both(
					next_str, ft_substr(text, 0, len));
			*result = ptrarr_add_ptr_and_free(*result, next_str);
			next_str = NULL;
			if (!*result)
				return (NULL);
			text += len + 1;
			len = 0;
		}
		else
			len++;
	}
	if (len)
		next_str = strjoin_nullable_and_free_both(
				next_str, ft_substr(text, 0, len));
	return (next_str);
}

static char	**cmd_str2str_arr(t_cmd_str_node **str_node, bool is_export_cmd)
{
	void	**result;
	char	*next_str;
	int		i;

	i = 0;
	result = NULL;
	next_str = NULL;
	while (str_node[i])
	{
		if (str_node[i]->type != TOKTYPE_EXPANDABLE || is_export_cmd)
		{
			if (next_str)
				next_str = strjoin_and_free_first(next_str, str_node[i]->text);
			else
				next_str = ft_strdup(str_node[i]->text);
		}
		else
			next_str = expandable_node2strarr(&result, next_str,
					str_node[i]->text);
		i++;
	}
	if (next_str)
		result = ptrarr_add_ptr_and_free(result, next_str);
	return ((char **)result);
}

/* 
	Convert AST string to array of string with variable expansion 
	Bash Behaves differently in how it processes string when the command is "export"
	ex: ($b has value "a  b")
	if the command is export ;              (is_export_cmd == true)
		abc = "a"$B"c" -> ["abc=aa  bc"]
	else                                    (is_export_cmd == false )
		abc = "a"$B"c" -> ["abc=aa", "bc"]
*/

char	**expand_string_node(t_parse_node_string *string_node,
	bool is_export_cmd)
{
	t_cmd_str_node	**cmd_str;
	int				i;
	char			**result;

	cmd_str = ast_str2cmd_str(string_node);
	if (!cmd_str)
		return (NULL);
	result = cmd_str2str_arr(cmd_str, is_export_cmd);
	i = 0;
	while (cmd_str[i])
	{
		free(cmd_str[i]->text);
		free(cmd_str[i]);
		i++;
	}
	free(cmd_str);
	return (result);
}
