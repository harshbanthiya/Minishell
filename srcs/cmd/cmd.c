#include "minishell.h"

void    command_count_argc(t_cmd *command, t_node *arg_node)
{
    int     output;

    output = 0;
    while (arg_node != NULL)
    {
        arg_node = arg_node->right_child;
        output++;
    } 
    command->argc = output;
}

void    command_store_argv(t_cmd *command, t_node *arg_node, t_dlist *env_list)
{
    int     i;

    i = 0;
    if (!env_list)
        return ;
    command->argv = (char **)malloc(sizeof(char *) * (command->argc + 1));
    command->has_path = 0;
    while (arg_node != NULL && arg_node->type == NODE_ARGUMENT)
    {
        if (i == 0 && ft_strchr(arg_node->data, '/'))
            command->has_path = 1;
        // arg_node->data = replace_env(arg_node->data, env_list);
		arg_node->data = parse_expand_line(arg_node->data);
        arg_node->data = strip_quotes(&arg_node->data);
        arg_node->data = replace_home_path(arg_node->data, env_list);
        
        // arg_node->data = replace_env(arg_node->data, env_list);
        // arg_node->data = strip_quotes(&arg_node->data);
        // arg_node->data = replace_home_path(arg_node->data, env_list);
        command->argv[i] = ft_strdup(arg_node->data);
        arg_node = arg_node->right_child;
        i++;
    }
    command->argv[i] = NULL;
}

int     command_init(t_node *simple_cmd, t_cmd *command, t_pipe *pipe, t_dlist **env_list)
{
    t_node   *arg_node;

    if (simple_cmd == NULL)
    {
        command->argc = 0;
        return (-1);
    }
    if (simple_cmd->type == NODE_REDIRECT_IN || simple_cmd->type == NODE_REDIRECT_OUT || simple_cmd->type == NODE_REDIRECT_DOUBLEOUT || simple_cmd->type == NODE_REDIRECT_DOUBLEIN)
    {
        arg_node = simple_cmd->left_child;
        command->redir = simple_cmd;
        command->redir->left_child = NULL;
    }
    else 
    {
        arg_node = simple_cmd;
        command->redir = NULL;
    }
    /* Order the functions and redirections prolly using a function having param of root node of redir  DO NOT FORGET this code needs it*/
    pre_order(command->redir);
    command_count_argc(command, arg_node);
    command_store_argv(command, arg_node, *env_list);
    command->pipe = pipe;
    return (0);
}

void    command_destroy(t_cmd *command)
{   
    int     i;

    i = 0;
    while (i++ < command->argc)
        free(command->argv[i]);
    free(command->argv);
    command->argc = 0;
}
