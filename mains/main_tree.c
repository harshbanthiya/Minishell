#include "../includes/minishell.h"

void    parse(t_dlist  *token_list, t_node **node)
{
    global_current_token_node = token_list;
    *node = cmd_line();
    if (global_current_token_node != NULL)
        printf("syntax error near unexpected token: \'%s\'\n", ((t_token *)global_current_token_node->content)->data);
}

t_node   *get_tree(char *line)
{
    t_dlist       *token_list;
    t_node       *output;

    token_list = NULL;
    if (make_token_list(&token_list, line) < 0)
    {
        printf("Error: wrong token\n");
        return (NULL);
    }
    else 
        parse(token_list, &output);
    return (output);
}
/* remove later */
void print_tabs(int tabs)
{
    int     i;
    i = 0;
    while (i < tabs)
    {
        printf("\t");
        i++;
    }
}

void print_tree_r(t_node *root, int level)
{
    if (root == NULL)
    {
        print_tabs(level);
        printf("<empty>\n");
        return ;
    }
    print_tabs(level);
    printf("type - %d | data - %s\n", root->type, root->data);
    printf("left\n");
    print_tree_r(root->left_child, level++);
    print_tabs(level);
    printf("right\n");
    print_tree_r(root->right_child, level++);
    print_tabs(level);
    printf("finished\n");
    
}

void print_tree(t_node *node)
{
    print_tree_r(node, 0);
}
/* Needs some working super basic */
char *put_prompt(void)
{
    char    *cwd;
    cwd = (char *)malloc(sizeof(char) * 99);
    getcwd(cwd, 99);
    return (cwd);
}

int main(int argc, char **argv, char **envp)
{
    char        *cmd_line;
    t_dlist      *env_list;
    t_node      *root_node;
    char        prompt[100];


    if(!argc || !(*argv[0]))
        return (-1);
    init_shell(envp);
    init_signals();
    global_exit_code = 0;
    get_prompt(prompt);
    cmd_line = readline(prompt);
    
    while (cmd_line && *cmd_line)
    {
        root_node = get_tree(cmd_line);
        //print_tree(root_node); // testing
        if (root_node)
            execute_tree(root_node, get_env()); //Once the tree is made execute it using env list
        free(cmd_line);
        get_prompt(prompt);
        cmd_line = readline(put_prompt());
    }
    free(cmd_line);
    free_shell();
    return (0);
}