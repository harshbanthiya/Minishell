/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:06:29 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/12/02 16:37:21 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../../includes/ms_environment.h"
#include "../../includes/ms_execution.h"
#include "../../includes/ms_builtin.h"

static int	cmd_connect_pipe(
	int pipe_prev_fd[2], int pipe_fd[2])
{
	if (pipe_prev_fd[1] != -1)
		cmd_close_pipe(pipe_prev_fd);
	cmd_copy_pipe(pipe_prev_fd, pipe_fd);
	return (0);
}

/*
 * Wait until all commands has finished and return exit code of last command.
 */
int	cmd_wait_commands(t_command *command)
{
	int			status;
	
	while (command)
	{
		if (command->pid > 0)
		{
			waitpid(command->pid, &status, 0);
			status = WEXITSTATUS(status);
		}
		command = command->piped_command;
	}
	set_status(status);
	return (status);
}

/*
 * Write to pipe_heredoc_fd[1]
 *   if last element of input_redirections is heredoc.
 */
static int	write_heredoc(t_fd_reds_list *in_fd_red_list)
{
	t_cmd_redirection	*red;

	while (in_fd_red_list)
	{
		red = in_fd_red_list->reds;
		while (red->next)
			red = red->next;
		close(in_fd_red_list->heredoc_pipe[0]);
		if (red->is_heredoc && red->filepath)
			write(in_fd_red_list->heredoc_pipe[1], red->filepath,
				ft_strlen(red->filepath));
		in_fd_red_list = in_fd_red_list->next;
	}
	return (0);
}

static int	cmd_exec_one_command(t_command *master, t_command *current_cmd,
			int pipe_fd[2], int pipe_prev_fd[2])
{
	pid_t			pid;
	t_fd_reds_list	*in_fd_red_list;

	in_fd_red_list = cmd_reds2fd_reds_list(current_cmd->input_redirections);
	if (pipe(pipe_fd) || cmd_set_heredoc_pipe_fd(in_fd_red_list))
		return (put_err_msg_and_ret("error pipe()"));
	if (current_cmd->exec_and_args)
		ft_export_var("_", (char *)current_cmd->exec_and_args[0], get_env());
	pid = fork();
	if (pid < 0)
		return (put_err_msg_and_ret("error fork()"));
	else if (pid == 0)
	{
		cmd_exec_command(current_cmd, pipe_prev_fd, pipe_fd,
			in_fd_red_list);
		cmd_free_cmd(master);
		if (g_shell.exit_flag >= 0)
			exit_shell();
	}
	write_heredoc(in_fd_red_list);
	cmd_free_fd_reds_list(in_fd_red_list);
	current_cmd->pid = pid;
	if (cmd_connect_pipe(pipe_prev_fd, pipe_fd) != 0)
		return (put_err_msg_and_ret("error cmd_connect_pipe()"));
	return (0);
}

/*
 * fork and execute commands.
 *
 * prev_cmd <1--pipe_prev_fd--0> current_cmd <1--pipe_fd--0> next_cmd
 *
 * return: status of last command
 */

int	cmd_exec_commands(t_command *command)
{
	int			pipe_fd[2];
	int			pipe_prev_fd[2];
	t_command	*current_cmd;
	int 		status;

	current_cmd = command;
	if (!command->piped_command && command->exec_and_args
		&& is_builtin((char *)command->exec_and_args[0]))
	{
		status = cmd_exec_builtin(current_cmd);
		return (status);
	}
	cmd_init_pipe_fd(pipe_prev_fd, STDIN_FILENO, -1);
	while (current_cmd)
	{
		if (cmd_exec_one_command(command, current_cmd, pipe_fd, pipe_prev_fd))
			break ;
		current_cmd = current_cmd->piped_command;

	}
	return (cmd_wait_commands(command));
}
