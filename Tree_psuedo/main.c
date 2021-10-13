#include "shell.h"

void    parse(list  *token_list, tree_node **node)
{
    global_current_token_node = token_list;
    *node = cmd_line();
    if (global_current_token_node != NULL)
        printf("syntax error near unexpected token: \'%s\'\n", ((token *)global_current_token_node->content)->data);
}

tree_node   *get_tree(char *line)
{
    list            *token_list;
    tree_node       *output;

    token_list = NULL;
    if (make_token_list(&token_list, line) < 0)
    {
        ft_err("Error: wrong token\n", 1);
        return (NULL);
    }
    else 
        parse(token_list, &output);
    return (output);
}

int main(int argc, char **argv, char **env)
{
    char        *cmd_line;
    list        *env_list;
    tree_node   *root_node;
    char        *prompt;
    char        *orig_prompt;

    if(!argc || !(*argv[0]))
        return (-1);
    env_list = make_env_list(env);   /* Psuedo name to populate the env list from env */
    while (1)
    {
        make_prompt(prompt, orig_prompt);
        cmd_line = readline((char *) prompt);
        root_node = get_tree(cmd_line); /* Function that makes the cmd_line tree */
        if (root_node)
            execute_tree(root_node, &env_list); /* Once the tree is made execute it using env list */
        free(cmd_line);
    }
    free(cmd_line);
    ft_lstclear(&env_list,free);
    return (0);
}