/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:41:09 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:41:40 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../libft/libft.h"
#include "../../includes/ms_parse.h"

/* 
    piped_commands ::= command "|" piped_commands | command
*/

t_parse_ast *parse_piped_commands(
    t_parse_buffer *buff, t_token *tok)
{
    t_parse_ast             *pip_node;
    t_parse_node_pipcmds    *content_node;
    t_parse_ast             *cmd_node;
    t_parse_ast             *rest_node;

    cmd_node = parse_command(buff, tok);
    if (!cmd_node)
        return (NULL);
    content_node = malloc(sizeof(t_parse_node_pipcmds));
    pip_node = parse_new_ast_node(ASTNODE_PIPED_COMMANDS, content_node);
    content_node->command_node = cmd_node;
    rest_node = NULL;
    parse_skip_spaces(buff, tok);
    if (tok->type == TOKTYPE_PIPE)
    {
        scan_get_token(buff, tok);
        parse_skip_spaces(buff, tok);
        rest_node = parse_piped_commands(buff, tok);
        pip_node->error = pip_node->error || !rest_node;
    }
    content_node->next = rest_node;
    pip_node->error = pip_node->error || cmd_node->error;
    pip_node->heredocs = parse_concat_heredocs(cmd_node, rest_node);
    return (pip_node);
}

/* 
    command ::= arguments 
*/

t_parse_ast *parse_command(
    t_parse_buffer *buff, t_token *tok)
{
    t_parse_ast             *cmd_node;
    t_parse_node_command    *content_node;
    t_parse_ast             *args_node;
    
    args_node = parse_arguments(buff, tok);
    if (!args_node)
        return (NULL);
    content_node = malloc(sizeof(t_parse_node_command));
    cmd_node = parse_new_ast_node(ASTNODE_COMMAND, content_node);
    content_node->arguments_node = args_node;
    cmd_node->error = cmd_node->error || args_node->error;
    cmd_node->heredocs = args_node->heredocs;
    return (cmd_node);
}

/* 
    arguments ::= redirection | redirection arguments | sting | string arguments
*/

t_parse_ast *parse_arguments(t_parse_buffer *buff, t_token *tok)
{
    t_parse_ast             *string_node;
    t_parse_ast             *redir_node;
    t_parse_ast             *rest_node;
    t_parse_node_arguments  *content_node;
    t_parse_ast             *args_node;

    rest_node = NULL;
    parse_skip_spaces(buff, tok);
    redir_node = parse_redirection(buff, tok);
    string_node = parse_string(buff, tok);
    if (!redir_node && !string_node)
        return (NULL);
    rest_node = parse_arguments(buff, tok);
    content_node = malloc(sizeof(t_parse_node_arguments));
    args_node = parse_new_ast_node(ASTNODE_ARGUMENTS, content_node);
    content_node->string_node = string_node;
    content_node->redirection_node = redir_node;
    content_node->rest_node = rest_node;
    args_node->error = args_node->error || (redir_node && redir_node->error);
    args_node->error = args_node->error || (string_node && string_node->error);
    args_node->error = args_node->error || (rest_node && rest_node->error);
    args_node->heredocs = parse_concat_heredocs(redir_node, rest_node);
    return (args_node);
}

/* 
    string ::= expandable <no_space> string | expandable 
    | not_expandable <no_space> string | not_expandable | expandable_quoted <no_space> string
    | expandable_quoted
*/

t_parse_ast    *parse_string(
     t_parse_buffer *buff, t_token *tok)
{
    t_parse_ast             *new_node;
    t_parse_node_string     *string;
    char                    *text;
    t_token_type            type;

    type = tok->type;
    if (type != TOKTYPE_EXPANDABLE
        && type != TOKTYPE_NON_EXPANDABLE
        && type != TOKTYPE_EXPANDABLE_QUOTED)
        return (NULL);
    string = malloc(sizeof(t_parse_node_string));
    new_node = parse_new_ast_node(ASTNODE_STRING, string);
    text = malloc(tok->length + 1);
    if (!string || !text)
        parse_fatal_error();
    string->type = type;
    ft_memcpy(text, tok->text, tok->length);
    text[tok->length] = '\0';
    string->text = text;
    scan_get_token(buff, tok);
    string->next = parse_string(buff, tok);
    return (new_node);
}

/* 
    redirection ::= "<" string | ">" string | ">>" string | "<<" string
*/

t_parse_ast *parse_redirection(
    t_parse_buffer *buff, t_token *tok)
{
    t_parse_ast                 *new_node;
    t_parse_ast                 *str_node;
    t_parse_node_redirection    *redirection;
    t_token_type                type;
    int                         fd;

    type = tok->type;
    if (type != TOKTYPE_INPUT_REDIRECTION
        && type != TOKTYPE_HEREDOCUMENT
        && type != TOKTYPE_OUTPUT_REDIRECTION
        && type != TOKTYPE_OUTPUT_APPENDING)
        return(NULL);
    fd = tok->length;
    scan_get_token(buff, tok);
    parse_skip_spaces(buff, tok);
    str_node = parse_string(buff, tok);
    redirection = malloc(sizeof(t_parse_node_redirection));
    redirection->type = type;
    redirection->fd = fd;
    redirection->string_node = str_node;
    new_node = parse_new_ast_node(ASTNODE_REDIRECTION, redirection);
    new_node->error = !str_node || str_node->error;
    if (type == TOKTYPE_HEREDOCUMENT)
        new_node->heredocs = parse_new_heredocs(redirection);
    return (new_node);
}
 
