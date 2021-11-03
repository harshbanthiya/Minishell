/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 21:59:14 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/28 17:41:49 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		gen_token_short(t_list **token_list, char *line, int idx_start)
{
	int		idx;
	int		type;
	t_token	*token;

	idx = idx_start;
	type = line[idx_start];
	if (line[idx_start] == GREAT && line[idx_start + 1] == line[idx_start])
	{
		idx++;
		type = GREATGREAT;
	}
	token = create_token(line, idx_start, idx + 1, type);
	ft_lstadd_back(token_list, ft_lstnew(token));
	return (idx);
}

int				set_token_list(t_list **token_list, char *line)
{
	int		idx;
	int		len_line;
	int		idx_start;

	len_line = ft_strlen(line);
	idx = 0;
	while (idx < len_line)
	{
		idx_start = idx;
		if (ft_strchr("<>|;", line[idx]))
			idx = gen_token_short(token_list, line, idx);
		else if (line[idx] == SPACE)
		{
			idx++;
			continue;
		}
		else
			idx = gen_token_string(token_list, line, idx);
		if (idx < 0)
			return (-1);
		idx++;
	}
	return (0);
}
