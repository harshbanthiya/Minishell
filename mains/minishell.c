#include "../includes/minishell.h"
#include <string.h>
void    parse(t_dlist  *token_list, t_node **node)
{
    global_current_token_node = token_list;
    *node = cmd_line();
    if (global_current_token_node != NULL)
        p//rintf("syntax error near unexpected token: \'%s\'\n", ((t_token *)global_current_token_node->content)->data);
}

t_node   *get_tree(char *line)
{
    t_dlist       *token_list;
    t_node       *output;

    token_list = NULL;
    if (make_token_list(&token_list, line) < 0)
    {
        p//rintf("Error: wrong token\n");
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
        p//rintf("\t");
        i++;
    }
}

void print_tree_r(t_node *root, int level)
{
    if (root == NULL)
    {
        print_tabs(level);
        p//rintf("<empty>\n");
        return ;
    }
    print_tabs(level);
    p//rintf("type - %d | data - %s\n", root->type, root->data);
    p//rintf("left\n");
    print_tree_r(root->left_child, level++);
    print_tabs(level);
    p//rintf("right\n");
    print_tree_r(root->right_child, level++);
    print_tabs(level);
    p//rintf("finished\n");
    
}

void print_tree(t_node *node)
{
    print_tree_r(node, 0);
}

void hook(int signo)
{
    if (signo == SIGINT)
    {
        global_exit_code = 1;
        ft_putstr_fd("\b\b \n", 1);
        p//rintf("%s\n", get_prompt());
    }
    else if (signo == SIGTSTP || signo == SIGQUIT)
        ft_putstr_fd("\b\b  \b\b", 1);
}

int main(int argc, char **argv, char **envp)
{
    char        *user_in;
    t_node      *root_node;


    if(!argc || !(*argv[0]))
        return (-1);
    init_shell(envp);
    if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
    {
        root_node = get_tree(argv[2]);
        //print_tree(root_node); // testing
        if (root_node)
            execute_tree(root_node, get_env());
        return (0);
    }
    global_exit_code = 0;
    init_signals();
    print_welcome();
    global_exit_code = 0;
    user_in = ft_readline();
    while (user_in && *user_in)
    {
		add_history(user_in);
        root_node = get_tree(user_in);
        //print_tree(root_node); // testing
        if (root_node)
            execute_tree(root_node, get_env());
        free(user_in);
        user_in = ft_readline();
    }
    free(user_in);
    free_shell();
    return (0);
}