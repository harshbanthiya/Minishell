/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 03:32:35 by sucho             #+#    #+#             */
/*   Updated: 2021/02/01 12:08:58 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_count_argc(t_cmd *cmd, t_node *arg_node)
{
	int output;

	output = 0;
	while (arg_node != NULL)
	{
		arg_node = arg_node->right;
		output++;
	}
	cmd->argc = output;
}

void	command_store_argv(t_cmd *cmd, t_node *arg_node, t_list *env_list)
{
	int		i;
	i = 0;
	if (!env_list)
		return ;
	cmd->argv = (char **)malloc(sizeof(char *) * (cmd->argc + 1));
	cmd->has_path = 0;
	while (arg_node != NULL && arg_node->type == NODE_ARGUMENT)
	{
		if (i == 0 && ft_strchr(arg_node->data, '/'))
			cmd->has_path = 1;
		arg_node->data = replace_env(arg_node->data, env_list);
		arg_node->data = strip_quotes(&arg_node->data);
		arg_node->data = replace_home_path(arg_node->data, env_list);
		cmd->argv[i] = ft_strdup(arg_node->data);
		arg_node = arg_node->right;
		i++;
	}
	cmd->argv[i] = NULL;
}

int		command_init(t_node *simple_cmd, t_cmd *cmd,
											t_pipe *pipe, t_list **env_list)
{
	t_node *arg_node;

	if (simple_cmd == NULL)
	{
		cmd->argc = 0;
		return (-1);
	}
	if (simple_cmd->type == NODE_REDIR_IN || simple_cmd->type == NODE_REDIR_OUT
		|| simple_cmd->type == NODE_REDIR_OUT_DBL)
	{
		arg_node = simple_cmd->left;
		cmd->redir = simple_cmd;
		cmd->redir->left = NULL;
	}
	else
	{
		arg_node = simple_cmd;
		cmd->redir = NULL;
	}
	pre_order(cmd->redir);
	command_count_argc(cmd, arg_node);
	command_store_argv(cmd, arg_node, *env_list);
	cmd->pipe = pipe;
	return (0);
}

void command_destroy(t_cmd* cmd)
{
    int i;

	i = 0;
    while(i++ < cmd->argc)
        free(cmd->argv[i]);
    free(cmd->argv);
    cmd->argc = 0;
}
