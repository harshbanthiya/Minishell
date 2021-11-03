/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 18:23:01 by sucho             #+#    #+#             */
/*   Updated: 2021/02/01 13:44:41 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_simplecmd(t_node *simple_cmd, t_pipe *pipe, t_list **env_list)
{
	t_cmd	cmd;

	command_init(simple_cmd, &cmd, pipe, env_list);
	command_execute(&cmd, env_list);
	command_destroy(&cmd);
}

void	execute_cmd(t_node *cmd_node, t_pipe *pipe, t_list **env_list)
{
	if (!cmd_node)
		return ;
	execute_simplecmd(cmd_node, pipe, env_list);
}

void	execute_pipeline(t_node *pipe_node, t_list **env_list)
{
	t_pipe	*pipe_temp;
	t_node	*job_node;
	int		file_descript[2];
	int		pipewrite;
	int		piperead;

	pipe(file_descript);
	pipewrite = file_descript[1];
	piperead = file_descript[0];
	execute_cmd(pipe_node->left, pipe_temp = pipe_first(0, pipewrite), \
			env_list);
	job_node = pipe_node->right;
	while ((job_node != NULL) && job_node->type == NODE_PIPE)
	{
		close(pipewrite);
		pipe(file_descript);
		pipewrite = file_descript[1];
		g_pipe_test++;
		execute_cmd(job_node->left, pipe_temp = pipe_mid(piperead, pipewrite), \
				env_list);
		close(piperead);
		piperead = file_descript[0];
		job_node = job_node->right;
	}
	piperead = file_descript[0];
	close(pipewrite);
	g_pipe_test++;
	execute_cmd(job_node, pipe_temp = pipe_last(piperead, 0), env_list);
	close(piperead);
	// free(pipe_temp->file_descript);
	// free(pipe_temp);
}

void	execute_job(t_node *job, t_list **env_list)
{
	t_pipe	*command;

	if (job == NULL)
		return ;
	else if (job->type == NODE_PIPE)
		execute_pipeline(job, env_list);
	else
		execute_cmd(job, command = pipe_for_commamd(), env_list);
}

void	set_exit_code(int status, int excode)
{
	if (excode == -1)
	{
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_code = 128 + WTERMSIG(status);
	}
	else
		g_exit_code = excode;
}

void	execute_cmdline(t_node *cmdline, t_list **env_list)
{
	int		status;
	int		i;
	t_node	*pipe_counter;

	if (cmdline == NULL)
		return ;
	if (cmdline->type == NODE_SEQ)
	{
		g_pipe_index = 1;
		g_pipe_test = 0;
		i = 0;
		pipe_counter = cmdline->left;
		node_count_pipe_node(pipe_counter);
		execute_job(cmdline->left, env_list);
		execute_cmdline(cmdline->right, env_list);
		return ;
	}
	else
	{
		g_pipe_index = 1;
		g_pipe_test = 0;
		i = 0;
		pipe_counter = cmdline;
		node_count_pipe_node(pipe_counter);
		if (!(g_pipe_pid = (int *)malloc(sizeof(int) * (g_pipe_index + 1))))
			return ;
		g_pipe_pid[g_pipe_index] = '\0';
		execute_job(cmdline, env_list);
		i = 0;
		while (i < g_pipe_index)
		{
			waitpid(*(g_pipe_pid + i), &status, 0);
			printf("#####status:%d####\n", status);
			set_exit_code(status, NO_EXCODE);
			i++;
		}
		free(g_pipe_pid);
	}
}

void	execute_tree(t_node *head, t_list **env_list)
{
	execute_cmdline(head, env_list);
}
