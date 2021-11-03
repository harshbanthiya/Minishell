/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:59:22 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/28 17:42:00 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	calc_buff_len(int *buff)
{
	int	idx;
	int	len;

	len = 0;
	idx = 0;
	while (idx < BUFF_SIZE)
	{
		if (buff[idx] == 1)
			len++;
		idx++;
	}
	return (len);
}

static char	*create_result_str(int *buff, char *token_data, \
		t_scanner_flags *flag)
{
	int		idx;
	int		cnt;
	char	*result;

	if (flag->d_quote == TRUE || flag->s_quote == TRUE)
	{
		write(1, "Wrong Token!\n", 13);
		result = ft_strdup("");
		return (result);
	}
	cnt = calc_buff_len(buff);
	result = ft_calloc(cnt + 1, sizeof(char));
	result[cnt] = '\0';
	idx = 0;
	cnt = 0;
	while (idx < BUFF_SIZE && token_data[idx] != '\0')
	{
		if (buff[idx] == 1)
		{
			result[cnt] = token_data[idx];
			cnt++;
		}
		idx++;
	}
	return (result);
}

static int	strip_quotes_others(char *token_data, int (*buff)[BUFF_SIZE], \
		int idx, t_scanner_flags **flag)
{
	if (token_data[idx] == S_QUOTE)
		(*flag)->s_quote = FALSE;
	if ((*flag)->s_quote == FALSE && token_data[idx] == D_QUOTE)
		(*flag)->d_quote = !((*flag)->d_quote);
	if (token_data[idx] != S_QUOTE && token_data[idx] != D_QUOTE)
		(*buff)[idx] = 1;
	return (idx + 1);
}

static int	strip_quotes_single(char *token_data, int (*buff)[BUFF_SIZE], \
		int idx, t_scanner_flags **flag)
{
	if ((*flag)->d_quote == TRUE)
		(*buff)[idx] = 1;
	else
		(*flag)->s_quote = TRUE;
	idx++;
	while ((*flag)->d_quote == FALSE && \
			token_data[idx] != '\0' && token_data[idx] != S_QUOTE)
	{
		(*buff)[idx] = 1;
		idx++;
	}
	return (idx);
}

char		*strip_quotes(char **token_data)
{
	char			*result;
	t_scanner_flags *flag;
	int				idx;
	int				buff[BUFF_SIZE];

	init_flag(&flag);
	ft_bzero(buff, BUFF_SIZE);
	idx = 0;
	while ((*token_data)[idx] != '\0')
	{
		if ((*token_data)[idx] == S_QUOTE && flag->s_quote == FALSE)
			idx = strip_quotes_single(*token_data, &buff, idx, &flag);
		else
			idx = strip_quotes_others(*token_data, &buff, idx, &flag);
	}
	result = create_result_str(buff, *token_data, flag);
	free((*token_data));
	free(flag);
	return (result);
}
