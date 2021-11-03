#include "minishell.h"

t_node   *cmd_line1(void)
{
    t_node   *job_node;
    t_node   *cmdline_node;
    t_node   *result;

    job_node = job();
    if (job_node == NULL)
        return (NULL);
    if (!term(SEMICOLON, NULL))
    {
        node_delete(job_node);
        return (NULL);
    }
    cmdline_node = cmd_line();
    if (cmdline_node == NULL)
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

t_node   *cmd_line2(void)
{
    t_node   *job_node;
    t_node   *result;

    job_node = job();
    if (job_node == NULL)
        return (NULL);
    if (!term(SEMICOLON, NULL))
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
t_node	*cmd_line3(void)
{
	return (job());
}

t_node   *cmd_line(void)
{
    t_node   *node;
    t_dlist  *save;

    save = global_current_token_node;
    global_current_token_node = save;
    node = cmd_line1();
    if (global_current_token_node != NULL && node != NULL)
        return (node);
    global_current_token_node = save;
    node = cmd_line2();
    if (global_current_token_node != NULL && node != NULL)
        return (node);
    global_current_token_node = save;
    node = cmd_line3();
    if (global_current_token_node != NULL &&  node != NULL)
        return (node);
    return (NULL);
}

t_node   *job_1(void)
{
    t_node   *command_node;
    t_node   *job_node;
    t_node   *result;

    command_node = command();
    if (command_node == NULL)
        return (NULL);
    if (!term(PIPE, NULL))
    {
        node_delete(command_node);
        return (NULL);
    }
    job_node = job();
    if (job_node == NULL)
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

t_node   *job_2(void)
{
    return (command());
}

t_node   *job(void)
{
    t_node   *node;
    t_dlist   *save;

    save = global_current_token_node;
    global_current_token_node = save;
    node = job_1();
    if (global_current_token_node != NULL && node != NULL)
        return (node);
    global_current_token_node = save;
    node = job_2();
    if (global_current_token_node != NULL && node != NULL)
        return (node);
    return (NULL);
}

t_node   *command(void)
{
    t_node   *redir_node;
    t_node   *simplecmd_node;
    t_node   *temp;

    redir_node = NULL;
    simplecmd_node = NULL;
    while (global_current_token_node)
    {
        if (((t_token *)global_current_token_node->content)->type == PIPE)
            break ;
        if (((t_token *)global_current_token_node->content)->type == SEMICOLON)
            break ;
        temp = redir_list();
        if (temp != NULL)
        {
            node_append_right(&redir_node, temp);
            printf("redirection_node: %s\n", redir_node->data); /* comment printf later */    
        }
        else if ((temp =simplecmd()) != NULL)
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

t_node   *redir_list(void)
{
    t_node   *result;
    char        *pathname;
    int         node_type;

    if (term_redir(&pathname, &node_type) == false)
        return (NULL);
    result = malloc(sizeof(t_node));
    if (node_type == GREAT) /* ascii for > is 62 */
        node_type = NODE_REDIRECT_OUT;
    else if (node_type == LESS) /* ascii for < is 60 */
        node_type = NODE_REDIRECT_IN;
    else if (node_type == LESSLESS) // make the double in logic
        node_type = NODE_REDIRECT_DOUBLEIN;
    else 
        node_type = NODE_REDIRECT_DOUBLEOUT;
    node_set_type(result, node_type);
    node_set_data(result, pathname);
    node_attach_branch(result, NULL, NULL);
    return (result);
}

t_node  *simplecmd(void)
{
    t_node   *result;
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
    if (((t_token *)(global_current_token_node)->content)->type == token_type)
    {
        if (arg != NULL)
            *arg = ft_strdup(((t_token *)global_current_token_node->content)->data);
        global_current_token_node = global_current_token_node->next;
        return (true);
    }
    return (false);
}

int     term_redir(char **arg, int *node_type)
{
    t_token   *current;

    if (global_current_token_node == NULL)
        return (false);
    current = (t_token *)(global_current_token_node->content);
    if (current->type == GREAT || current->type == LESS || current->type == GREATGREAT || current->type == LESSLESS)
    {
        *node_type = current->type;
        if (global_current_token_node->next == NULL)
            return (false);
        global_current_token_node = global_current_token_node->next;
        current = (t_token *)(global_current_token_node->content);
        if (current->type == STRING)
        {
            if (arg != NULL)
                *arg = ft_strdup(((t_token *)global_current_token_node->content)->data);
            global_current_token_node = global_current_token_node->next;
            return (true);
        }
    }
    return (false);
}