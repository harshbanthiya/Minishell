/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_replace_env2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 19:02:14 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/28 17:42:27 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_quotes_status(char *line, int idx, t_scanner_flags **flag)
{
	if (line[idx] == D_QUOTE)
	{
		if ((*flag)->s_quote == FALSE && (*flag)->d_quote == FALSE)
			(*flag)->d_quote = !((*flag)->d_quote);
		else if ((*flag)->d_quote == TRUE)
			(*flag)->d_quote = !((*flag)->d_quote);
	}
	if ((*flag)->d_quote == FALSE && line[idx] == S_QUOTE)
		(*flag)->s_quote = !((*flag)->s_quote);
}

static void	set_env_key_val(t_env **env, char *str, int len, t_list *env_list)
{
	(*env)->key = ft_strndup(str, len);
	if (ft_strncmp((*env)->key, "?", 2) == 0)
		(*env)->val = ft_itoa(g_exit_code);
	else
		(*env)->val = get_env_val((*env)->key, env_list);
}

static int	set_env_pos(char *str, int idx)
{
	idx++;
	while (!is_end_of_env_variable(str[idx]))
		idx++;
	if (str[idx] == '?')
		idx++;
	return (idx - 1);
}

int			set_env(t_env **env, char *str, int idx, t_list *env_list)
{
	int	env_str_end;

	env_str_end = set_env_pos(str, idx);
	set_env_key_val(env, &(str[idx + 1]), env_str_end - idx, env_list);
	return (env_str_end);
}

void		free_env_flag_note(t_env *env, t_scanner_flags *flag, \
				t_rplc_env_note *note)
{
	free(env);
	free(flag);
	free(note);
}
