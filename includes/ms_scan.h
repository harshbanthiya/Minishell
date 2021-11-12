/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_scan.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 21:34:47 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/09 00:53:23 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_SCAN_H
# define MS_SCAN_H

typedef struct s_parse_buffer	t_parse_buffer;

typedef enum e_token_type
{
	TOKTYPE_EOF = -1,
	TOKTYPE_PARSE_ERROR = 0,
	TOKTYPE_NON_EXPANDABLE = 500,
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
	SCANSTATE_NORMAL,
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

#endif