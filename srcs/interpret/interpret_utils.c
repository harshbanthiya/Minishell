#include "minishell.h"

t_pipe       *pipe_first(int read_pipe, int write_pipe)
{
    t_pipe   *output;

    output = (t_pipe *)malloc(sizeof(t_pipe));
    if (!output)
        return (0);
    output->stdin_pipe = false;
    output->stdout_pipe = true;
    output->read_pipe = read_pipe;
    output->write_pipe = write_pipe;
    return (output);
}

t_pipe       *pipe_mid(int read_pipe, int write_pipe)
{
    t_pipe   *output;

    output = (t_pipe *)malloc(sizeof(t_pipe));
    if (!output)
        return (0);
    output->stdin_pipe = true;
    output->stdout_pipe = true;
    output->read_pipe = read_pipe;
    output->write_pipe = write_pipe;
    return (output);
}

t_pipe       *pipe_last(int read_pipe, int   write_pipe)
{
    t_pipe       *output;

    output = (t_pipe *)malloc(sizeof(t_pipe));
    if (!output)
        return (0);
    output->stdin_pipe = true;
    output->stdout_pipe = false;
    output->read_pipe = read_pipe;
    output->write_pipe = write_pipe;
    return (output);
}

t_pipe       *pipe_for_command(void)
{
    t_pipe   *output;

    output = (t_pipe *)malloc(sizeof(t_pipe));
    if (!output)
        return (0);
    output->stdin_pipe = false;
    output->stdout_pipe = false;
    output->read_pipe = 0;
    output->write_pipe = 0;
    return (output);
}

void    node_count_pipe_node(t_node *search)
{
    if (search)
    {
        if (search->type == NODE_PIPE)
            global_pipe_index++;
        node_count_pipe_node(search->left_child);
        node_count_pipe_node(search->right_child);
    }
}