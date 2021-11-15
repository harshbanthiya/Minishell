/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_ast_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 10:53:03 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 10:07:22 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* 
    set values of command->execandargs base on string_node
    string ::= expandable <no_space> string | expandable | not_expandable <no_space> string
                | not_expandable | expandable_quoted <no_space> string | expandable_quoted
*/

int     cmd_process_string_node(
    t_parse_node_string *string_node, t_command *command)
{
    char    **splitted_env_val;
    char    **strarr;

    if (command->exec_and_args && command->exec_and_args[0]
        && !ft_strcmp(command->exec_and_args[0], "export"))
        splitted_env_val = expand_string_node(string_node, true);
    else 
        splitted_env_val = expand_string_node(string_node, false);
    strarr = ptrarr_merge((void **)command->exec_and_args, (void **)splitted_env_val);
    free(splitted_env_val);
    if (!strarr)
        return (-1);
    free((void **)command->exec_and_args);
    command->exec_and_args = strarr;
    return (0);
}

/* 
    set values of command->input_file_path or output_file_path
    based on the redirection node
    Mimicking bash behaviour, environment variables expansions will not be done here
    but right before execution.
    redirection := "<" string | ">" string | ">>" string
*/

int cmd_process_redirection_node(t_parse_node_redirection *redirection_node,
    t_command *command)
{
    int     redirection_type;
    char    *text;
    int     fd;
    int     status;

    redirection_type = redirection_node->type;
    text = string_node2string(redirection_node->string_node->content.string,
            redirection_type != TOKTYPE_HEREDOCUMENT);
    fd = redirection_node->fd;
    status = 0;
    if (!text)
        return (-1);
    if (redirection_type == TOKTYPE_INPUT_REDIRECTION)
        status = cmd_add_inredirect(command, text, fd);
    else if (redirection_type = TOKTYPE_OUTPUT_REDIRECTION)
        status = cmd_add_outredirect(command, text, fd, false);
    else if (redirection_type == TOKTYPE_OUTPUT_APPENDING)
        status = cmd_add_outredirect(command, text, fd, true);
    else if (redirection_type == TOKTYPE_HEREDOCUMENT)
        status = cmd_add_heredoc(command, text, fd, 
                    cmd_is_heredoc_expandable(redirection_node));
    free((void *)text);
    return (status);
}

/* 
    Parse Argument Node and set values of command
    arguments ::= redirection | redirection arguments | string
                  | string arguments
*/

int     cmd_process_args_node(
    t_parse_node_arguments *args_node, t_command *command)
{
    if (args_node->string_node)
        return (cmd_process_string_node(
            args_node->string_node->content.string, command));
    else if (args_node->redirection_node)
        return (cmd_process_redirection_node(
            args_node->redirection_node->content.redirection, command));
    else 
        return (1);
    return (0);
}

/*
    Convert AST commands node to command object
    command ::= arguments
*/

t_command   *ast_cmd2cmd(t_parse_node_command *cmd_node)
{
    t_command               *command;
    t_parse_node_arguments  *args_node;

    command = cmd_init_cmd(NULL);
    check_malloc_success("ast2cmd", command);
    args_node = cmd_node->arguments_node->content.arguments;
    while (args_node)
    {
        if (cmd_process_args_node(args_node, command))
        {
            cmd_free_cmd(command);
            return (NULL);
        }
        if (args_node->rest_node)
            args_node = args_node->rest_node->content.arguments;
        else 
            args_node = NULL;
    }
    return (command);
}

/*
    Convert Ast command node to command object

    pipcmds: piped_commands
    piped_commands ::= command "|" piped_commands | command
*/

t_command   *pipcmd2cmd(t_parse_node_pipcmds *pipcmds)
{
    t_command       *commands;
    t_command       *command;

    commands = NULL;
    while (pipcmds)
    {
        command = ast_cmd2cmd(pipcmds->command_node->content.command);
        if (!command)
        {
            cmd_free_cmd(commands);
            return (NULL);
        }
        cmd_add_pipcmd(&commands, command);
        if (pipcmds->next)
            pipcmds = pipcmds->next->content.piped_commands;
        else 
            pipcmds = NULL;
    }
    return (commands);
}