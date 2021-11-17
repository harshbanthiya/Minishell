/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_scan.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:34:47 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/16 15:44:24 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SCAN_H
# define MS_SCAN_H

typedef struct s_parse_buffer	t_parse_buffer;

typedef enum e_token_type
{
	TOKTYPE_EOF = -1,
	TOKTYPE_PARSE_ERROR = 0,
	TOKTYPE_NON_EXPANDABLE = 0xc101, /* added for the scan test */
	TOKTYPE_EXPANDABLE,
	TOKTYPE_EXPANDABLE_QUOTED,
	TOKTYPE_PIPE,
	TOKTYPE_INPUT_REDIRECTION,
	TOKTYPE_HEREDOCUMENT,
	TOKTYPE_OUTPUT_REDIRECTION,
	TOKTYPE_OUTPUT_APPENDING,
	TOKTYPE_SEMICOLON,
	TOKTYPE_NEWLINE,
	TOKTYPE_SPACE,
}	t_token_type;

typedef enum e_scan_state
{
	SCANSTATE_NORMAL = 0xd101,
	SCANSTATE_SINGLE_QUOTED,
	SCANSTATE_DOUBLE_QUOTED,
}t_scan_state;

typedef struct s_token
{
	char			*text;
	int				length;
	int				max_length;
	t_token_type	type;
}t_token;

int 	scan_init_token(t_token *result);
int 	scan_expand_text_buffer(t_token *result);
int		scan_getc(t_parse_buffer *buf);
void	scan_ungetc(t_parse_buffer *buff);
int		scan_is_special_char(char ch);
int		scan_read_word(t_parse_buffer *buff, t_token *result);
int		scan_read_double_quotes(t_parse_buffer *buff, t_token *result);
int		scan_read_single_quotes(t_parse_buffer *buff, t_token *result);
int		scan_get_spaces(t_parse_buffer *buff, t_token *result, int ch);
int		scan_get_symbols(t_parse_buffer *buff, t_token *result, int ch);
int		scan_get_quotes(t_parse_buffer *buff, t_token *result, int ch);
int		scan_get_token(t_parse_buffer *buff, t_token *result);
int		scan_check_redirection_with_fd(t_parse_buffer *buff, t_token *result);
int		scan_escaped(t_parse_buffer *buff, t_token *result);
int		scan_get_eof(t_token *result, int ch);
void	scan_get_lt_gt(t_parse_buffer *buff, t_token *result, int ch);
#endif