/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:44:59 by sucho             #+#    #+#             */
/*   Updated: 2021/02/01 14:04:04 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	command_external_pipe(int pid, t_cmd *cmd)
// {
// }

void	command_external_redir(t_cmd *cmd)
{
	int fd;

	while (cmd->redir)
	{
		if (cmd->redir->type == NODE_REDIR_IN)
		{
			fd = open(cmd->redir->data, O_RDONLY);
			if (fd == -1)
			{
				perror(cmd->redir->data);
				exit(1);
			}
			dup2(fd, STDIN_FILENO);
		}
		else if (cmd->redir->type == NODE_REDIR_OUT)
		{
			fd = open(cmd->redir->data, O_WRONLY | O_TRUNC | O_CREAT,
							S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			if (fd == -1)
			{
				perror(cmd->redir->data);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
		}
		else if (cmd->redir->type == NODE_REDIR_OUT_DBL)
		{
			fd = open(cmd->redir->data, O_WRONLY | O_APPEND | O_CREAT,
							S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
			if (fd == -1)
			{
				perror(cmd->redir->data);
				exit(1);
			}
			dup2(fd, STDOUT_FILENO);
		}
		cmd->redir = cmd->redir->right;
	}
	close(fd);
}

void	command_execute(t_cmd *cmd, t_list **env_list)
{
	int		pid;
	int		stdout_fd;
	int		internal_errno;
	char	**path_arr;

	if (cmd->argc < 0)
		return ;
	// cd, exit, unset의 실행 시점;
	// && export 인자가 1개 이상일 때
	// 자식 프로세스에서 실행되어야 하는게 아니라, 부모 프로세스 내에서 실행 되어야함.
	if (!cmd->pipe->stdin_pipe && !cmd->pipe->stdout_pipe)
	{
		if ((g_exit_code = execute_internal_in_parent(cmd, env_list))>= 0)
		{
			g_pipe_index = 0;
			return ;
		}
	}
	pid = fork();
	if (pid != 0)
	{
		g_pipe_pid[g_pipe_test] = pid;
	}
	if (pid > 0)
	{
		printf("pid: %d\n", pid);
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL); // <-  중요
		signal(SIGQUIT, SIG_DFL);
		command_external_redir(cmd);
		stdout_fd = dup(STDOUT_FILENO);
		// read stdin from pipe if present
		if (cmd->pipe->stdin_pipe)
		{
			dup2(cmd->pipe->pipe_read, STDIN_FILENO);
		}
		// write stdout to pipe if present
		if (cmd->pipe->stdout_pipe)
		{
			dup2(cmd->pipe->pipe_write, STDOUT_FILENO);
		}
		internal_errno = execute_internal_in_child(cmd, env_list);
		if (internal_errno >= 0)
			exit(internal_errno);
		if (!cmd->has_path)
		{
			exec_with_path(cmd, path_arr = create_path_arr(*env_list), *env_list);
			free_path_arr(path_arr);
			printf("command not found: \'%s\'\n", cmd->argv[0]);
			exit(127);
		}
		else
		{
			if (execve(cmd->argv[0], cmd->argv, \
					env_list_to_envp(*env_list)) == -1)
			{
				dup2(stdout_fd, STDOUT_FILENO);
				printf("command not found: \'%s\'\n", cmd->argv[0]);
				exit(1);
			}
			else
			{
				close(stdout_fd);
			}
		}
	}
	return ;
}
