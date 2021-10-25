#include "shell.h"

void    parse(t_list  *token_list, t_node **node)
{
    global_current_token_node = token_list;
    *node = cmd_line();
    if (global_current_token_node != NULL)
        printf("syntax error near unexpected token: \'%s\'\n", ((t_token *)global_current_token_node->content)->data);
}

t_node   *get_tree(char *line)
{
    t_list       *token_list;
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
    //char        *cmd_line;
    t_list      *env_list;
    //t_node      *root_node;


    if(!argc || !(*argv[0]))
        return (-1);
    env_list = make_env_list(envp);   /* Psuedo name to populate the env list from env */
    print_env_list(env_list);
    //signal stuff 
    //global_exit_code = 0;
    //cmd_line = readline(put_prompt());
    //root_node = get_tree(cmd_line);
   // print_tree(root_node);
    /*
    while (1)
    {
        cmd_line = readline(put_prompt());
        root_node = get_tree(cmd_line); // Function that makes the cmd_line tree
        //print_tree(root_node); // testing
        if (root_node)
            execute_tree(root_node, &env_list); //Once the tree is made execute it using env list 
        
        free(cmd_line);
    }
    */
    //free(cmd_line);
    ft_lstclear(&env_list,free);
    return (0);
}