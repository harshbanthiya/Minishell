#include "../shell.h"

void    node_attach_branch(t_node *root, t_node *left, t_node *right)
{
    if (root == NULL)
        return ;
    root->left_child = left;
    root->right_child = right;
}

void    node_append_right(t_node **root, t_node *right)
{
    t_node   *seek;

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

void    node_set_type(t_node *node, int type)
{
    if (node == NULL)
        return ;
    node->type = type;
}

void    node_set_data(t_node *node, char *token)
{
    if (node == NULL)
        return ;
    if (token != NULL)
        node->data = token;
}

void	node_delete(t_node *node)
{
	if (!node)
		return ;
	node_delete(node->left_child);
	node_delete(node->right_child);
	free(node);
}
