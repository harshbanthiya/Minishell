#include "../shell.h"

ppipe       *pipe_first(int read_pipe, int write_pipe)
{
    ppipe   *output;

    output = (ppipe *)malloc(sizeof(ppipe));
    if (!output)
        return (0);
    output->stdin_pipe = false;
    output->stdout_pipe = true;
    output->read_pipe = read_pipe;
    output->write_pipe = write_pipe;
    return (output);
}

ppipe       *pipe_mid(int read_pipe, int write_pipe)
{
    ppipe   *output;

    output = (ppipe *)malloc(sizeof(ppipe));
    if (!output)
        return (0);
    output->stdin_pipe = true;
    output->stdout_pipe = true;
    output->read_pipe = read_pipe;
    output->write_pipe = write_pipe;
    return (output);
}

ppipe       *pipe_last(int read_pipe, int   write_pipe)
{
    ppipe       *output;

    output = (ppipe *)malloc(sizeof(ppipe));
    if (!output)
        return (0);
    output->stdin_pipe = true;
    output->stdout_pipe = false;
    output->read_pipe = read_pipe;
    output->write_pipe = write_pipe;
    return (output);
}

ppipe       *pipe_for_command(void)
{
    ppipe   *output;

    output = (ppipe *)malloc(sizeof(ppipe));
    if (!output)
        return (0);
    output->stdin_pipe = false;
    output->stdout_pipe = false;
    output->read_pipe = 0;
    output->write_pipe = 0;
    return (output);
}

void    node_count_pipe_node(tree_node *search)
{
    if (search)
    {
        if (search->type == NODE_PIPE)
            global_pipe_index++;
        node_count_pipe_node(search->left_child);
        node_count_pipe_node(search->right_child);
    }
}