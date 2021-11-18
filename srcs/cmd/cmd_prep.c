/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_prep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 09:35:30 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/18 12:57:12 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/readline/readline.h"
#include "../../includes/readline/history.h"
#include "../../includes/ms_execution.h"
#include "../../includes/minishell.h"
#include "../../includes/ms_utils.h"

t_command	*cmd_init_cmd(char **exec_and_args)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->exec_and_args = exec_and_args;
	cmd->input_redirections = NULL;
	cmd->output_redirections = NULL;
	cmd->piped_command = NULL;
	cmd->pid = 0;
	return (cmd);
}

int	cmd_add_inredirect(t_command *command,
		char *filepath, int fd)
{
	t_cmd_redirection	*red;

	red = ft_calloc(1, sizeof(t_cmd_redirection));
	check_malloc_success("add_inredirect", red);
	red->filepath = ft_strdup(filepath);
	check_malloc_success("add_inredirect", (void *)red->filepath);
	red->fd = fd;
	if (!cmd_redirection_add_back(&command->input_redirections, red))
	{
		free(red);
		return (ERROR);
	}
	return (0);
}

int	cmd_add_outredirect(t_command *command,
	char *filepath, int fd, bool is_append)
{
	t_cmd_redirection	*red;

	red = ft_calloc(1, sizeof(t_cmd_redirection));
	check_malloc_success("add_outredirect", red);
	red->filepath = ft_strdup(filepath);
	check_malloc_success("add_outredirect", (void *)red->filepath);
	red->fd = fd;
	red->is_append = is_append;
	if (!cmd_redirection_add_back(&command->output_redirections, red))
	{
		free(red);
		return (-1);
	}
	return (0);
}

/* Add command to the cmd->pipe_command */

t_command	*cmd_add_pipcmd(t_command **cmds, t_command *pipcmd)
{
	t_command	*current_cmd;

	if (!*cmds)
		*cmds = pipcmd;
	else
	{
		current_cmd = *cmds;
		while (current_cmd->piped_command)
			current_cmd = current_cmd->piped_command;
		current_cmd->piped_command = pipcmd;
	}
	return (pipcmd);
}
