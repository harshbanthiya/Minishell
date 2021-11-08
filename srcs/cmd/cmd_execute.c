#include "minishell.h"
#define TMPFILE ".here_doc"
void    command_external_redir(t_cmd *command)
{
    int     fd;

    while (command->redir)
    {
        if (command->redir->type == NODE_REDIRECT_IN)
        {
            fd = open(command->redir->data, O_RDONLY);
            if (fd == -1)
            {
                perror(command->redir->data);
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
        }
        else if (command->redir->type == NODE_REDIRECT_OUT)
        {
            fd = open(command->redir->data, O_WRONLY | O_TRUNC | O_CREAT | S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); /* read up S_IRUSR S_IRGRP S_IWGRP S_IWUSRon signals and add here in open statements */
            if (fd == -1)
            {
                perror(command->redir->data);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
        }
        else if (command->redir->type == NODE_REDIRECT_DOUBLEOUT)
        {
            fd = open(command->redir->data, O_WRONLY | O_APPEND | O_CREAT | S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
            if (fd == -1)
            {
                perror(command->redir->data);
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
        }
        else if (command->redir->type == NODE_REDIRECT_DOUBLEIN)
        {
            fd = open(TMPFILE, O_CREAT | O_TRUNC | O_RDWR | S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR, 0777);
            if (fd == -1)
            {
                perror(command->redir->data);
                exit(1);
            }
            dup2(STDIN_FILENO, fd);
        }
        /* Add Heredoc logic here */
        command->redir = command->redir->right_child;
    }
    close(fd);
}

// Execution time of cd, exit, unset;
// && When there is more than one export argument
// It should be executed in the parent process, not in the child process.

void    command_execute(t_cmd *command, t_dlist ** env_list)
{
    int     pid;
    int     stdout_fd;
    int     internal_errno;
    char    **path_arr;

    if (command->argc < 0)
        return ;
    if (!command->pipe->stdin_pipe && !command->pipe->stdout_pipe)
    {
        // if ((global_exit_code = execute_builtin_in_parent(command, env_list)) >= 0)
		if ((global_exit_code = run_builtin(command, env_list, 0)) > 0)
        {
            global_pipe_index = 0;
            return ;
        }
    }
    pid = fork();
    if (pid != 0)
        global_pipe_pid[global_pipe_test] = pid;
    //if (pid > 0)
        //p//rintf("pid: %d\n", pid);
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        command_external_redir(command);
        stdout_fd = dup(STDOUT_FILENO);
        // read stdin from pipe if present
        if (command->pipe->stdin_pipe)
            dup2(command->pipe->read_pipe, STDIN_FILENO);
        // write stdio to pipe if present
        if (command->pipe->stdout_pipe)
            dup2(command->pipe->write_pipe, STDOUT_FILENO);
        internal_errno = run_builtin(command, env_list, 1);
        if (internal_errno > 0)
            exit(internal_errno);
        if (!command->has_path)
        {
            path_arr = create_path_arr(*env_list);
            exec_with_path(command, path_arr, *env_list);
            free_path_arr(path_arr);
            p//rintf("command not found: \'%s\'\n", command->argv[0]);
            exit(127); /* Use the proper exit code here */
        }
        else 
        {
            if (execve(command->argv[0], command->argv, env_list_to_envp(*env_list)) == -1)
            {
                dup2(stdout_fd, STDOUT_FILENO);
                p//rintf("commnand not found: \'%s'\n", command->argv[0]);
                exit(1); /* Use proper exit code */
            }
            else
                close(stdout_fd);
        }
    }
    return ;
}