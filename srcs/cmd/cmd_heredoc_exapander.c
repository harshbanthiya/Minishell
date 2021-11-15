/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc_exapander.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:52:06 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:32:55 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/ms_environment.h"
#include "../../includes/ms_execution.h"
#include "../../includes/ms_utils.h"

static void     process_escape(char **result, char **str, int *len)
{
    char    *tmpstr;
    
    tmpstr = ft_substr(*str, 0,
            *len + !((*str)[*len + 1] == '$' || (*str)[*len + 1] == '\\'));
    check_malloc_success("heredoc expander", tmpstr);
    *result = strjoin_and_free_both(*result, tmpstr);
    check_malloc_success("heredoc expander", *result);
    *str += *len + 1;
    tmpstr = ft_substr(*str, 0, 1);
    check_malloc_success("heredoc expander", tmpstr);
    *result = strjoin_and_free_both(*result, tmpstr);
    check_malloc_success("heredoc expander", *result);
    *str += 1;
    *len = 0; 
}

/* 
    Expand variable in document of heredoc 
    examples: 
    in  : |\$USER \\$USER $USER '$USER' "$USER" \"\'$
    out : |$USER \hbanthiy hbanthiy 'hbanthiy' "hbanthiy" \"\'$
*/

char    *expand_heredoc_document(char *str)
{
    char    *result;
    int     len;
    bool    is_in_env;
    bool    is_continue;

    result = ft_strdup("");
    check_malloc_success("heredoc expander", result);
    is_continue = true;
    len = 0;
    is_in_env = false;
    while (is_continue)
    {
        if (str[len] == '\\')
        {
            if (is_in_env)
                is_continue = exp_join_str_or_env(&result, &str, &len, 
                        &is_in_env);
            process_escape(&result, &str, &len);
        }
        else if (exp_will_toggle_env(is_in_env, false ,str, len))
            is_continue = exp_join_str_or_env(&result, &str, &len, &is_in_env);
        else 
            len++;
    }
    return (result);
}

bool	cmd_is_heredoc_expandable(t_parse_node_redirection *redirection_node)
{
	bool				is_expandable_heredoc;
	t_parse_node_string	*str_node;

	str_node = redirection_node->string_node->content.string;
	is_expandable_heredoc = 1;
	while (str_node)
	{
		if (str_node->type == TOKTYPE_NON_EXPANDABLE)
			is_expandable_heredoc = 0;
		if (str_node->next)
			str_node = str_node->next->content.string;
		else
			str_node = NULL;
	}
	return (is_expandable_heredoc);
}