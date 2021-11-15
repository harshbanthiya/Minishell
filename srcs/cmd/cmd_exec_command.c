/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 09:21:56 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/15 09:31:55 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/ms_execution.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"

/*
 * Connect pipe to STDIN_FILENO and STDOUT_FILE_NO.
 *
 * replace STDIN_FILENO and STDOUT_FILE_NO with pipe by dup2().
 */
static void	replace_stdio_with_pipe(t_command *command,
	int pipe_prev_fd[2], int pipe_fd[2])
{
	if (pipe_prev_fd[1] >= 0)
	{
		close(pipe_prev_fd[1]);
		if (dup2(pipe_prev_fd[0], STDIN_FILENO) == -1)
			put_err_msg_and_exit("error child dup2(in)");
		close(pipe_prev_fd[0]);
	}
	if (command->piped_command)
	{
		close(pipe_fd[0]);
		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
			put_err_msg_and_exit("error child dup2(out)");
		close(pipe_fd[1]);
	}
}

/*
 * Execute a command.
 * This function is supposed to be called in child process.
 *
 * command: command
 * pipe_prev_fd[2]: A pipe that connects the previous and current process.
 * pipe_fd[2]: A pipe that connects the current and next process.
 */
void	cmd_exec_command(t_command *command,
	int pipe_prev_fd[2], int pipe_fd[2], t_fd_reds_list *in_fd_reds_list)
{
	//t_builtin_cmd	*builtin_func; /* typedef int	t_builtin_cmd(char**);*/

	//set_sighandlers(SIG_DFL);
	replace_stdio_with_pipe(command, pipe_prev_fd, pipe_fd);
	if (cmd_set_input_file(in_fd_reds_list) == -1
		|| cmd_set_output_file(command) == -1)
		exit(EXIT_FAILURE);
	if (!command->exec_and_args)
		exit(0);
	//builtin_func = get_builtin_func((char *)command->exec_and_args[0]); /* Check builtin utils */
	//if (builtin_func)
	//	exit(builtin_func((char **)command->exec_and_args));
	cmd_execvp((char *)command->exec_and_args[0],
		(char **) command->exec_and_args);
}
