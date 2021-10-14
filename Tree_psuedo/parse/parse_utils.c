#include "../shell.h"

void    node_attach_branch(tree_node *root, tree_node *left, tree_node *right)
{
    if (root == NULL)
        return ;
    root->left_child = left;
    root->right_child = right;
}

void    node_append_right(tree_node **root, tree_node *right)
{
    tree_node   *seek;

    seek = *root;
    if (!seek)
    {
        *root = right;
        return ;
    }
    while (1)
    {
        if (seek->right_child)
            seek = seek->right_child;
        else
        {
            seek->right_child = right;
            return ;
        }
    }
}

void    node_set_type(tree_node *node, int type)
{
    if (node == NULL)
        return ;
    node->type = type;
}

void    node_set_data(tree_node *node, char *token)
{
    if (node == NULL)
        return ;
    if (token != NULL)
        node->data = token;
}




