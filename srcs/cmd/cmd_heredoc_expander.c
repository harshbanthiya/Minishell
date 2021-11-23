/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_heredoc_expander.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 10:52:06 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 12:12:16 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../libft/libft.h"
#include "../../includes/minishell.h"
#include "../../includes/ms_environment.h"
#include "../../includes/ms_execution.h"
#include "../../includes/ms_utils.h"
#include "../../includes/readline/readline.h"
#include "../../includes/readline/history.h"

static void	process_escape(char **result, char **str, int *len)
{
	char	*tmpstr;

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

char	*expand_heredoc_document(char *str)
{
	char	*result;
	int		len;
	bool	is_in_env;
	bool	is_continue;

	result = ft_strdup("");
	check_malloc_success("heredoc expander", result);
	is_continue = true;
	len = 0;
	is_in_env = false;
	while (str && is_continue)
	{
		if (str && str[len] == '\\')
		{
			if (is_in_env)
				is_continue = exp_join_str_or_env(&result, &str, &len,
						&is_in_env);
			process_escape(&result, &str, &len);
		}
		else if ((exp_will_toggle_env(is_in_env, false, str, len)) || !str[len])
			is_continue = exp_join_str_or_env(&result, &str, &len, &is_in_env);
		else
			len++;
	}
	return (result);
}
