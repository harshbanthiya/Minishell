/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 06:55:21 by sucho             #+#    #+#             */
/*   Updated: 2021/01/31 23:57:35 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*pipe_first(int pipe_read, int pipe_write)
{
	t_pipe *output;

	if (!(output = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	output->stdin_pipe = false;
	output->stdout_pipe = true;
	output->pipe_read = pipe_read;
	output->pipe_write = pipe_write;
	return (output);
}

t_pipe	*pipe_mid(int pipe_read, int pipe_write)
{
	t_pipe *output;

	if (!(output = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	output->stdin_pipe = true;
	output->stdout_pipe = true;
	output->pipe_read = pipe_read;
	output->pipe_write = pipe_write;
	return (output);
}

t_pipe	*pipe_last(int pipe_read, int pipe_write)
{
	t_pipe *output;

	if (!(output = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	output->stdin_pipe = true;
	output->stdout_pipe = false;
	output->pipe_read = pipe_read;
	output->pipe_write = pipe_write;
	return (output);
}

t_pipe	*pipe_for_commamd(void)
{
	t_pipe *output;

	if (!(output = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	output->stdin_pipe = false;
	output->stdout_pipe = false;
	output->pipe_read = 0;
	output->pipe_write = 0;
	return (output);
}

// t_pipe *pipe_init(void)
// {
// 	t_pipe *output;
// 	int *file_descript;

// 	if (!(output = (t_pipe *)malloc(sizeof(t_pipe))))
// 		return (0);
// 	if (!(file_descript = (int *)malloc(sizeof(int) * 3)))
// 		return (0);
// 	file_descript[2] = '\0';
// 	pipe(file_descript);
// 	output->file_descript =file_descript;
// 	return (output);
// }
