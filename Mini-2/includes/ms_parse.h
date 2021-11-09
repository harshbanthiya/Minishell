/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 00:08:09 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/09 00:37:17 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_PARSE_H
# define MS_PARSE_H
# include "ms_scan.h"

#define PARSE_BUFF_SIZE 1024
struct          s_parse_buffer;
typedef int     t_scan_getc(struct s_parse_buffer *buff);
typedef void    t_scan_ungetc(struct s_parse_buffer *buff);

typedef struct  s_parse_buffer
{
    char            buffer[PARSE_BUFF_SIZE * 100];
    int             size;
    int             cur_pos;
    t_scan_state    scan_state;
    t_scan_getc     *getc;
    t_scan_ungetc   *ungetc;
    void            *data;
}t_parse_buffer;

typedef enum e_parse_ast_type
{
	ASTNODE_NONE,
	ASTNODE_STRING,
	ASTNODE_REDIRECTION,
	ASTNODE_ARGUMENTS,
	ASTNODE_COMMAND,
	ASTNODE_PIPED_COMMANDS,
	ASTNODE_DELIMITER,
	ASTNODE_SEQ_COMMANDS,
	ASTNODE_COMMAND_LINE,
	ASTNODE_INVALID,
}	t_parse_ast_type;

typedef struct s_parse_node_string
{
	char			*text;
	t_token_type	type;
	t_parse_ast		*next;
}	t_parse_node_string;

typedef struct s_parse_node_pipcmds
{
	t_parse_ast	*command_node;
	t_parse_ast	*next;
}	t_parse_node_pipcmds;

typedef struct s_parse_node_command
{
	t_parse_ast	*arguments_node;
}	t_parse_node_command;

typedef struct s_parse_node_arguments
{
	t_parse_ast	*string_node;
	t_parse_ast	*redirection_node;
	t_parse_ast	*rest_node;
}	t_parse_node_arguments;

typedef struct s_parse_node_delimiter
{
	t_token_type	type;
}	t_parse_node_delimiter;

typedef struct s_parse_node_seqcmds
{
	t_parse_ast	*pipcmd_node;
	t_parse_ast	*delimiter_node;
	t_parse_ast	*rest_node;
}	t_parse_node_seqcmds;

typedef struct s_parse_node_cmdline
{
	t_parse_ast	*seqcmd_node;
}	t_parse_node_cmdline;

typedef struct s_parse_node_redirection
{
	t_parse_ast		*string_node;
	t_token_type	type;
	int				fd;
}	t_parse_node_redirection;

typedef struct s_parse_hdoc_list
{
	t_parse_node_redirection	*redirection;
	struct s_parse_hdoc_list	*next;
}	t_parse_hdoc_list;

typedef struct s_parse_ast
{
	t_parse_ast_type	type;
	int					error;
	t_parse_hdoc_list	*heredocs;
	union u_parse_ast_node_content
	{
		void						*void_ptr;
		t_parse_node_redirection	*redirection;
		t_parse_node_string			*string;
		t_parse_node_arguments		*arguments;
		t_parse_node_command		*command;
		t_parse_node_pipcmds		*piped_commands;
		t_parse_node_delimiter		*delimiter;
		t_parse_node_seqcmds		*sequential_commands;
		t_parse_node_cmdline		*command_line;
	}					content;
}	t_parse_ast;

#endif 