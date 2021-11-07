#ifndef TREE_H
#define TREE_H

typedef enum
{
    NODE_PIPE           = (1 << 0),           
    NODE_BCKGRND        = (1 << 1),        
    NODE_SEQ            = (1 << 2),           
    NODE_REDIRECT_IN    = (1 << 3),   
    NODE_REDIRECT_OUT   = (1 << 4),   
    NODE_REDIRECT_DBOUT = (1 << 5), 
    NODE_REDIRECT_HDOC  = (1 << 6),  
    NODE_CMDPATH        = (1 << 7),       
    NODE_ARGUMENT       = (1 << 8),      
    NODE_DATA           = (1 << 9),   
}t_node_type;

typedef struct s_tree_node
{
    int                 type;
    char                *data;
    struct s_tree_node  *left_child;
    struct s_tree_node  *right_child; 
}t_tree_node;



#endif 