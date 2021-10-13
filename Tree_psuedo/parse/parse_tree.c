#include "../shell.h"

tree_node   *cmd_line1(void)
{
    tree_node   *job_node;
    tree_node   *cmdline_node;
    tree_node   *result;

    job_node = job();
    if (job_node == NULL)
        return (NULL);
    if (!term(59, NULL)) /* Semi colon is ascii 59 replace with enum or global */
    {
        node_delete(job_node);
        return (NULL);
    }
    if ((cmdline_node = cmd_line()) == NULL)
    {
        node_delete(job_node);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    if (!result)
        return (NULL);
    node_set_data(result, ";");
    node_set_type(result, NODE_SEQ);
    node_attach_branch(result, job_node, cmdline_node);
    return (result);
}

tree_node   *cmd_line2(void)
{
    tree_node   *job_node;
    tree_node   *result;

    job_node = job();
    if (job_node == NULL)
        return (NULL);
    if (!term(59, NULL)) /* Semi colon is ascii 59 replace with enum or global */
    {
        node_delete(job_node);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    if (!result)
        return (NULL);
    node_set_data(result, ";");
    node_set_type(result, NODE_SEQ);
    node_attach_branch(result, job_node, NULL);
    return (result);
}
tree_node	*cmd_line3(void)
{
	return (job());
}

tree_node   *cmd_line(void)
{
    tree_node   *node;
    list        *save;

    save = global_current_token_node;
    if ((global_current_token_node = save, node = cmd_line1()) != NULL)
        return (node);
    if ((global_current_token_node = save, node = cmd_line2()) != NULL)
        return (node);
    if ((global_current_token_node = save, node = cmd_line3()) != NULL)
        return (node);
    return (NULL);
}

tree_node   *job_1(void)
{
    tree_node   *command_node;
    tree_node   *job_node;
    tree_node   *result;

    if ((command_node = command()) == NULL)
        return (NULL);
    if (!term(124, NULL)) /* 124 is the ascii for Pipe change later */
    {
        node_delete(command_node);
        return (NULL);
    }
    if ((job_node == job()) == NULL)
    {
        node_delete(command_node);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    if (!result)
        return (NULL);
    node_set_data(result, "|");
    node_set_type(result, NODE_PIPE);
    node_attach_branch(result, command_node, job_node);
    return (result);
}

tree_node   *job_2(void)
{
    return (command());
}

tree_node   *job(void)
{
    tree_node   *node;
    list        *save;

    save = global_current_token_node;
    if ((global_current_token_node = save, node = job1()) != NULL)
        return (node);
    if ((global_current_token_node = save, node = job_2()) != NULL)
        return (node);
    return (NULL);
}

tree_node   *command(void)
{
    tree_node   *redir_node;
    tree_node   *simplecmd_node;
    tree_node   *temp;

    redir_node = NULL;
    simplecmd_node = NULL;
    while (global_current_token_node)
    {
        if (((token *)global_current_token_node->content)->type == '|')
            break ;
        if (((token *)global_current_token_node->content)->type == ';')
            break ;
        if ((temp = redir_list()) != NULL)
        {
            node_append_right(&redir_node, temp);
            printf("redirection_node: %s\n", redir_node->data);           
        }
        else if ((temp = simplecmd()) != NULL)
            node_append_right(&simplecmd_node, temp);
        else 
            return (NULL);
    }
    if (redir_node != NULL)
    {
        redir_node->left_child = simplecmd_node;
        return (redir_node);
    }
    else 
        return (simplecmd_node);
}

tree_node   *redir_list(void)
{
    tree_node   *result;
    char        *pathname;
    int         node_type;

    if (term_redir(&pathname, &node_type) == false)
        return (NULL);
    result = malloc(sizeof(tree_node));
    if (node_type == 62) /* ascii for > is 62 */
        node_type = NODE_REDIRECT_OUT;
    if (node_type == 60) /* ascii for < is 60 */
        node_type = NODE_REDIRECT_IN;
    else 
        node_type = NODE_REDIRECT_DOUBLEOUT;
    node_set_type(result, node_type);
    node_set_data(result, pathname);
    node_attach_branch(result, NULL, NULL);
    return (result);
}

tree_node *simplecmd(void)
{
    tree_node   *result;
    char        *pathname;

    if(term(STRING, &pathname) == false)
        return (NULL);
    result = malloc(sizeof(*result));
    node_set_type(result, NODE_ARGUMENT);
    node_set_data(result, pathname);
    node_attach_branch(result, NULL, NULL);
    return (result);
}

int     term(int token_type, char **arg)
{
    if (global_current_token_node == NULL)
        return (false);
    if (((token *)(global_current_token_node)->content)->type == token_type)
    {
        if (arg != NULL)
            *arg = ft_strdup(((token *)global_current_token_node->content)->data);
        global_current_token_node = global_current_token_node->next;
        return (true);
    }
    return (false);
}

int     term_redir(char **arg, int *node_type)
{
    token   *current;

    if (global_current_token_node == NULL)
        return (false);
    current = (token *)(global_current_token_node->content);
    if (current->type == '>' || current->type == '<' || current->type == ">>")
    {
        *node_type = current->type;
        if (global_current_token_node->next == NULL)
            return (false);
        global_current_token_node = global_current_token_node->next;
        current = (token *)(global_current_token_node->content);
        if (current->type == STRING)
        {
            if (arg != NULL)
                *arg = ft_strdup(((token *)global_current_token_node->content)->data);
            global_current_token_node = global_current_token_node->next;
            return (true);
        }
    }
    return (false);
}