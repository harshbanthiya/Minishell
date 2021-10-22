#include "../shell.h"

void    execute_simplecmd(tree_node *simple_cmd, ppipe *pipe, list **env_list)
{
    cmd     command;

    command_init(simple_cmd, &command, pipe, env_list); /* probable prototypes for the CRUD operations for the cmd struct */
    command_execute(&command, env_list);
    command_destroy(&command);
}

void    execute_command(tree_node *command, ppipe *pipe, list **env_list)
{
    if (!command)
        return ;
    execute_simplecmd(command, pipe, env_list);
}

void    execute_pipeline(tree_node *pipe_node, list **env_list)
{
    ppipe           *temp_pipe;
    tree_node       *job_node;
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

void    execute_job(tree_node *job, list **env_list)
{
    tree_node   *command;

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

void    execute_tree(tree_node  *head, list *env_list)
{
    int         status;
    int         i;
    tree_node   *pipe_counter;

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
    }
    else 
    {
        global_pipe_index = 1;
        global_pipe_test = 0; /* Maintaining a global flag to test before connecting the pipes */
        i = 0;
        pipe_counter = head;
        node_count_pipe_node(pipe_counter);
        global_pipe_pid = (int *)malloc(sizeof(int) * (global_pipe_index + 1)); 
        if (!global_pipe_index)
            return ;
        execute_job(head, env_list);
        i = 0;
        while (i < global_pipe_index)
        {
            waitpid(*(global_pipe_pid + i), &status, 0);
            printf("status: %d\n", status);
            set_exit_code(status, -1);
            i++;
        }
        free(global_pipe_pid);
    }

}