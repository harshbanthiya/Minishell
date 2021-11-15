/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:12:25 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 11:29:04 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/ms_parse.h"

/* 
    command_line ::= "\n" | seq_commands "\n" (Backus Naur Form)
    Command line is defined as either "\n" or seq_commands attached to "\n"
*/

t_parse_ast *parse_command_line(
    t_parse_buffer *buff, t_token *tok)
{
    t_parse_ast             *cmdline_node;
    t_parse_ast             *seqcmd_node;
    t_parse_node_cmdline    *content_node;

    seqcmd_node = parse_sequential_commands(buff, tok);
    if (!seqcmd_node)
        return (NULL);
    parse_skip_spaces(buff, tok);
    if (tok->type != TOKTYPE_NEWLINE)
        return (NULL);
    content_node = malloc(sizeof(t_parse_node_cmdline));
    cmdline_node = parse_new_ast_node(ASTNODE_COMMAND_LINE, content_node);
    content_node->seqcmd_node = seqcmd_node;
    cmdline_node->error = cmdline_node->error || seqcmd_node->error;
    if (cmdline_node->error)
        return (NULL);
    cmdline_node->heredocs = seqcmd_node->heredocs;
    return (cmdline_node);
}

/*
    delimiter ::= ";"
*/

t_parse_ast *parse_delimiter(
    t_parse_buffer *buff, t_token *tok)
{
    t_parse_ast             *delim_node;
    t_parse_node_delimiter  *content_node;    

    parse_skip_spaces(buff, tok);
    if (tok->type != TOKTYPE_SEMICOLON)
        return (NULL);
    content_node = malloc(sizeof(t_parse_node_delimiter));
    delim_node = parse_new_ast_node(ASTNODE_DELIMITER, content_node);
    content_node->type = TOKTYPE_SEMICOLON;
    return (delim_node);
}

/*

    seq_commands ::= piped_commands delimiter sequential commands | piped_commands delimiter 
                    | piped_commands
*/

t_parse_ast *parse_sequential_commands(
    t_parse_buffer *buff, t_token *tok)
{
    t_parse_ast             *seq_node;
    t_parse_ast             *pipcmd_node;
    t_parse_ast             *rest_node;
    t_parse_node_seqcmds    *content;

    parse_skip_spaces(buff, tok);
    pipcmd_node = parse_piped_commands(buff, tok);
    if (!pipcmd_node)
        return (NULL);
    content = malloc(sizeof(t_parse_node_seqcmds));
    seq_node = parse_new_ast_node(ASTNODE_SEQ_COMMANDS, content);
    content->pipcmd_node = pipcmd_node;
    content->delimiter_node = parse_delimiter(buff, tok);
    rest_node = NULL;
    if (content->delimiter_node)
    {
        scan_get_token(buff, tok);
        parse_skip_spaces(buff, tok);
        rest_node = parse_sequential_commands(buff, tok);
    }
    content->rest_node = rest_node;
    seq_node->error = seq_node->error || pipcmd_node->error;
    seq_node->error = seq_node->error || (rest_node && rest_node->error);
    seq_node->heredocs = parse_concat_heredocs(pipcmd_node, rest_node);
    return (seq_node);
}

