#include "shell.h"

int print_tokens(list *token_list)
{
    list    *tokens;

    tokens = token_list;
    while(tokens)
    {
        printf("TYPE: %.3d CONTENT: [%s]\n", ((token *)(tokens->content))->type,((token *)(tokens->content))->data);
        tokens = tokens->next; 
    }
}

 