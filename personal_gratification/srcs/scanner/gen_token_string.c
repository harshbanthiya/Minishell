/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_token_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:45:16 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/28 17:41:30 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_end_of_str_token(char chr, t_scanner_flags *flag)
{
	if (flag->s_quote != TRUE && flag->d_quote != TRUE && \
				ft_strchr(" |;<>", chr) != NULL)
		return (TRUE);
	return (FALSE);
}

int			gen_token_string(t_list **token_list, char *line, int idx_start)
{
	int				idx;
	t_token			*token;
	t_scanner_flags	*flag;
	char			*token_data;

	init_flag(&flag);
	idx = idx_start;
	while (line[idx] != '\0')
	{
		set_quotes_status(line, idx, &flag);
		if (is_end_of_str_token(line[idx], flag))
			break ;
		idx++;
	}
	free(flag);
	token_data = strndup(&line[idx_start], idx - idx_start);
	token = create_token(token_data, 0, ft_strlen(token_data), STRING);
	free(token_data);
	ft_lstadd_back(token_list, ft_lstnew(token));
	if (line[idx] != SPACE)
		idx--;
	return (idx);
}
