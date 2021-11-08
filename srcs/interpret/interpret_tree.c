#include "minishell.h"

void    execute_simplecmd(t_node *simple_cmd, t_pipe *pipe, t_dlist **env_list)
{
    t_cmd     command;

    command_init(simple_cmd, &command, pipe, env_list);
    //sh_change_mode(0);
    command_execute(&command, env_list);
    //sh_change_mode(1);
    command_destroy(&command);
}

void    execute_command(t_node *command, t_pipe *pipe, t_dlist **env_list)
{
    if (!command)
        return ;
    execute_simplecmd(command, pipe, env_list);
}

void    execute_pipeline(t_node *pipe_node, t_dlist **env_list)
{
    t_pipe           *temp_pipe;
    t_node          *job_node;
    int             fd[2];
    int             write_pipe;
    int             read_pipe;

    pipe(fd);
    write_pipe = fd[1];
    read_pipe = fd[0];
    temp_pipe = pipe_first(0, write_pipe);
    execute_command(pipe_node->left_child, temp_pipe, env_list);
    job_node = pipe_node->right_child;
    while ((job_node != NULL) && job_node->type == NODE_PIPE)
    {
        close(write_pipe);
        pipe(fd);
        write_pipe = fd[1];
        global_pipe_test++;
        temp_pipe = pipe_mid(read_pipe, write_pipe);
        execute_command(job_node->left_child, temp_pipe, env_list);
        close(read_pipe);
        read_pipe = fd[0];
        job_node = job_node->right_child;
    }
    read_pipe = fd[0];
    close(write_pipe);
    global_pipe_test++;
    temp_pipe = pipe_last(read_pipe, 0);
    execute_command(job_node, temp_pipe, env_list);
    close(read_pipe);
    /* Maybe I need to free temp pipe? I will worry about that later */
}

void    execute_job(t_node *job, t_dlist **env_list)
{
    t_pipe   *command;

    if (job == NULL)
        return;
    else if (job->type == NODE_PIPE)
        execute_pipeline(job, env_list);
    else 
    {
        command = pipe_for_command();
        execute_command(job, command, env_list);
    }
}

/* Excuse me .... while you are reading this, also consider the below thing, ok bie. */
/* Write a function set_exit_code(status, retcode); read up on WIFEXITED, WEXITSTATUS, WTERMSIG */

void    execute_tree(t_node  *head, t_dlist **env_list)
{
    int         status;
    int         i;
    t_node   *pipe_counter;

    if (head == NULL)
        return ;
    if (head->type == NODE_SEQ)
    {
        global_pipe_index = 1;
        global_pipe_test = 0 ; /* Maintaining a global flag to test before connecting the pipes */
        i = 0;
        pipe_counter = head->left_child;
        node_count_pipe_node(pipe_counter);
        execute_job(head->left_child, env_list);    /* recursively calling one child as job */
        execute_tree(head->right_child, env_list);  /* recursively calling right child with the same function */
        return ;
    }
    else 
    {
        global_pipe_index = 1;
        global_pipe_test = 0; /* Maintaining a global flag to test before connecting the pipes */
        i = 0;
        pipe_counter = head;
        node_count_pipe_node(pipe_counter);
        global_pipe_pid = (int *)malloc(sizeof(int) * (global_pipe_index + 1)); 
        if (!global_pipe_pid)
            return ;
        global_pipe_pid[global_pipe_index] = '\0';
        execute_job(head, env_list);
        i = 0;
        while (i < global_pipe_index)
        {
            waitpid(*(global_pipe_pid + i), &status, 0);
           // p//rintf("##status: %d\n", status);
            set_exit_code(status, NO_EXCODE);
            i++;
        }
        free(global_pipe_pid);
    }
}


void	set_exit_code(int status, int excode)
{
	if (excode == -1)
	{
		if (WIFEXITED(status))
			global_exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			global_exit_code = 128 + WTERMSIG(status);
	}
	else
		global_exit_code = excode;
}
