#include "shell.h"

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
            execute_tree(root_node, env_list); /* Once the tree is made execute it using env list */
        free(cmd_line);
    }
    free(cmd_line);
    ft_lstclear(&env_list,free);
    return (0);
}

/* Prototypes required */
/*
    MAKE ENV LIST FIRST: 
    ------------------------

    1. list *make_env_list(char **env)
        
        env_kv_pair     *start;
        t_list          *final_env_list;

        Malloc for each env_kv_node;
        Split the env using a function; 
        Add the splited item to final_env_list; (split_env_line(char **final_env_list, char *env[index])) 
        return (final_env_list)

    2. void  split_env_line(char **final_list, char *env_line)

    (*final_list)->key = substring(env_line, 0, strchr(first equal sign))
    (*final_list)->value = substring((strchr(first equal sign), 1, strlen(strchr (newline))))

    ------------------------------------------------------------

    MAKE TREE :  
    -----------------------------

    1.  tree_node  *get_tree(char *cmd_line)

        t_list      *token_list;
        tree_node   *final_tree;

        make_token_list(token_list, cmd_line);  // Helper function to check if correct tokens are entered and populates the token_list;
        if (make_list == NULL)
            error(bad token entered)
        else 
            parse_token_to_tree(token_list, final_tree);
        return final_tree 
    
    2. int  make_token_list(t_list **token_list, char *cmd_line)
        
        int len , index, len = strlen(cmd_line) 
        while(index < len)
            if (strchr("<>|;", cmd_line[index]))
                make_special_token(token_list, cmd_line, index);
            if (cmd_line[index] == whitespace)
                index++
            else 
                make_string_token(token_list, cmd_line, index);
            
    3. int  make_special_token(t_list **token_list, char *cmd_line, int index)

        token   *token;
        int     type;

        type = cmd_line[index];
        token = create_token(cmd_line, index, length, type);  ( A function that can populate the token linked list)
        lst_add(token_list, lst_new(token));

    4. int  make_string_token(t_list **token_list, char *cmd_line, int index)
    
        token       *token;
        scan_quote  *quotes;
        char        *pre_token_string;
        int         index2;

        while (cmd_line[index2])
        {
            look_for_quotes(line, index2, &quotes); ( A function to look for single and double quotes and populates the quotes struct we can match it later using odd even)
            look_for_end_of_string(cmd_line[index2], quotes) (A function that looks for end of string token which isnt a special character)
            index2++;
        }
        pre_token_string = strndup(cmd_line[index], index2 - index);
        token = create_token(pre_token_string, 0, strlen(pre_token_string), string); (same function as above);
        lst_add(token_list, lst_new(token));
        free(whatever is not in use)
    
    5. token * create_token(char *line, int start, int end, int type)

        token *to_ret;

        malloc(token)
        token->data = strndup(line[start], end - start);
        token->type = type
        return (to_ret)



*/