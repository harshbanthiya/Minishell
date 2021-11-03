/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_replace_env1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:48:04 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/28 17:48:57 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_flag(t_scanner_flags **flag)
{
	if (!((*flag) = (t_scanner_flags *)malloc(sizeof(t_scanner_flags))))
		return ;
	(*flag)->s_quote = 0;
	(*flag)->d_quote = 0;
}

void	init_env(t_env **env)
{
	if (!((*env) = (t_env *)(malloc(sizeof(t_env)))))
		return ;
	(*env)->key = 0;
	(*env)->val = 0;
}

void	init_replace_env(t_rplc_env_note **note, char **result, t_env **env, \
								t_scanner_flags **flag)
{
	if (!((*note) = (t_rplc_env_note *)malloc(sizeof(t_rplc_env_note))))
		return ;
	(*note)->idx = 0;
	(*note)->end = 0;
	(*note)->crr = 0;
	init_flag(flag);
	init_env(env);
	*result = 0x0;
}

int		is_valid_env_start(char chr1, char chr2, t_scanner_flags *flag)
{
	if (flag->s_quote == FALSE && chr1 == '$' && \
			(ft_isalpha(chr2) == TRUE || chr2 == '_' || chr2 == '?'))
		return (TRUE);
	return (FALSE);
}

int		is_end_of_env_variable(char chr)
{
	if (ft_isalnum(chr) || chr == '_')
		return (FALSE);
	return (TRUE);
}
