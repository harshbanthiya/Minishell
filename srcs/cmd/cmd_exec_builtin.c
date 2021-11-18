/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:56:38 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/17 16:29:58 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include "../../includes/ms_environment.h"
#include "../../includes/ms_execution.h"
#include "../../includes/ms_builtin.h"
#include "../../includes/minishell.h"

static int	save_stdin_stdout(t_cmd_redirection *red,
	int *stdinfd, int *stdoutfd)
{
	if (red->fd == *stdinfd)
		*stdinfd = dup(*stdinfd);
	if (red->fd == *stdoutfd)
		*stdoutfd = dup(*stdoutfd);
	if (*stdinfd == -1 || *stdoutfd == -1)
		return (ERROR);
	return (0);
}

/* Configure input redirection for builtin command.
 *
 * command: Command.
 * fd_list: File descriptor list for closing file descriptors
 *   after finishing command.
 * stdinfd: int variable's pointer for remember original fd socket of STDIN
 *   and recovering original STDIN after finishing command.
 * stdoutfd: int variable's pointer for remember original fd socket of STDOUT
 *   and recovering original STDOUT after finishing command.
 */
static int	builtin_set_in_red(t_command *command,
	t_fd_list **fd_list, int *stdinfd, int *stdoutfd)
{
	int					fd;
	t_cmd_redirection	*red;

	red = command->input_redirections;
	while (red)
	{
		if (save_stdin_stdout(red, stdinfd, stdoutfd))
			return (ERROR);
		if (!red->is_heredoc)
		{
			fd = open_file_for_redirect(red, O_RDONLY, 0);
			if (fd == ERROR)
				return (ERROR);
			if (dup2(fd, red->fd) == ERROR || close(fd) == ERROR
				|| !fd_list_add_fd(fd_list, red->fd))
				return (put_redir_errmsg_and_ret(ERROR,
						red->fd, strerror(errno)));
		}
		else
			close(red->fd);
		red = red->next;
	}
	return (0);
}

/* Configure output redirection for builtin command.
 *
 * command: Command.
 * fd_list: File descriptor list for closing file descriptors
 *   after finishing command.
 * stdinfd: int variable's pointer for remember original fd socket of STDIN
 *   and recovering original STDIN after finishing command.
 * stdoutfd: int variable's pointer for remember original fd socket of STDOUT
 *   and recovering original STDOUT after finishing command.
 */
static int	builtin_set_out_red(t_command *command,
	t_fd_list **fd_list, int *stdinfd, int *stdoutfd)
{
	int					fd;
	t_cmd_redirection	*red;
	int					flag_open;

	red = command->output_redirections;
	while (red)
	{
		flag_open = O_TRUNC * !red->is_append + O_APPEND * red->is_append;
		fd = open_file_for_redirect(red, O_WRONLY | O_CREAT | flag_open, 0644);
		if (fd == ERROR || save_stdin_stdout(red, stdinfd, stdoutfd))
			return (ERROR);
		if (dup2(fd, red->fd) == ERROR || close(fd) == ERROR
			|| !fd_list_add_fd(fd_list, red->fd))
			return (put_redir_errmsg_and_ret(ERROR,
					red->fd, strerror(errno)));
		red = red->next;
	}
	return (0);
}

/*
 * Execute built in command in the same process as the minishell main process.
 */
int	cmd_exec_builtin(t_command *command)
{
	int				stdoutfd;
	int				stdinfd;
	int				status;
	t_builtin_cmd	*builtin_func;
	t_fd_list		*fd_lst;

	fd_lst = NULL;
	stdinfd = dup(STDIN_FILENO);
	stdoutfd = dup(STDOUT_FILENO);
	if (stdinfd == -1 || stdoutfd == -1
		|| builtin_set_in_red(command, &fd_lst, &stdinfd, &stdoutfd) == ERROR
		|| builtin_set_out_red(command, &fd_lst, &stdinfd, &stdoutfd) == ERROR)
		return (set_status_and_ret(1, 1));
	builtin_func = get_builtin_func((char *)command->exec_and_args[0]);
	//command->exec_and_args = exec_wild_args(command->exec_and_args);
	status = builtin_func(&((char **)command->exec_and_args)[1]);
	set_status(status);
	fd_list_close(&fd_lst);
	if (dup2(stdoutfd, STDOUT_FILENO) == -1
		|| dup2(stdinfd, STDIN_FILENO) == -1)
		put_err_msg_and_exit("failed recovering original fd");
	close(stdoutfd);
	close(stdinfd);
	return (status);
}
