/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:50:48 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/28 17:41:42 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	gen_str_with_env(char **result, char *str, t_env *env, \
									t_rplc_env_note *note)
{
	char		*temp_str1;
	char		*temp_str2;

	temp_str1 = ft_strndup(&(str[note->crr]), note->idx - note->crr);
	if (env->val != NULL)
		temp_str2 = ft_strjoin(temp_str1, env->val);
	else
		temp_str2 = ft_strdup(temp_str1);
	free(temp_str1);
	if (*result == 0x0)
		*result = ft_strdup(temp_str2);
	else
	{
		temp_str1 = ft_strdup(*result);
		free(*result);
		*result = ft_strjoin(temp_str1, temp_str2);
		free(temp_str1);
	}
	free(temp_str2);
	free(env->key);
	if (env->val != NULL)
		free(env->val);
	return (note->end + 1);
}

static char	*join_str_to_str(char *result, char *str, int start, int end)
{
	char	*temp_str;
	char	*temp_result;

	temp_result = ft_strdup(result);
	free(result);
	temp_str = ft_strndup(&(str[start]), end);
	result = ft_strjoin(temp_result, temp_str);
	free(temp_str);
	free(temp_result);
	return (result);
}

char		*replace_env(char *str, t_list *env_list)
{
	char				*result;
	t_env				*env;
	t_scanner_flags		*flag;
	t_rplc_env_note		*note;

	init_replace_env(&note, &result, &env, &flag);
	while (str[note->idx] != '\0')
	{
		set_quotes_status(str, note->idx, &flag);
		if (is_valid_env_start(str[note->idx], str[note->idx + 1], flag))
		{
			note->end = set_env(&env, str, note->idx, env_list);
			note->crr = gen_str_with_env(&result, str, env, note);
		}
		note->idx++;
	}
	if (result == 0x0)
		result = ft_strndup(str, note->idx);
	else
		result = join_str_to_str(result, str, note->crr, note->idx - \
				(note->crr - 1) - 1);
	//받아오는 인자 free 부분 삭제
	free_env_flag_note(env, flag, note);
	return (result);
}
