#include "minishell.h"

int  gen_str_with_env(char **result, char *str, t_env *env, t_rplc_env_node *node)
{
    char    *temp_str1;
    char    *temp_str2;

    temp_str1 = ft_strndup(&str[node->crr], node->idx - node->crr);
    if (env->val != NULL)
        temp_str2 = ft_strjoin(temp_str1, env->val);
    else 
        temp_str2 = ft_strdup(temp_str1);
    free(temp_str1);
    if (*result == 0)
        *result = ft_strdup(temp_str2);
    else 
    {
        temp_str1 = ft_strdup(*result);
        free(*result);
        *result = ft_strjoin(temp_str1, temp_str2);
        free(temp_str1);
    }
    free(temp_str2);
    free(env->key);
    if (env->val != NULL)
        free(env->val);
    return (node->end + 1);
}

char    *join_str_to_str(char *result, char *str, int start, int end)
{
    char    *temp_str;
    char    *temp_result;

    temp_result = ft_strdup(result);
    free(result);
    temp_str = ft_strndup(&(str[start]), end);
    result = ft_strjoin(temp_result, temp_str);
    free(temp_str);
    free(temp_result);
    return (result);
}

// char    *replace_env(char *str, t_dlist *env_list)
// {
//     char            *result;
//     t_env           *env;
//     t_scan_quotes   *flags;
//     t_rplc_env_node *node;

<<<<<<< HEAD
    init_replace_env(&node, &result, &env, &flags);
    while (str[node->idx] != '\0')
    {
        make_quote_status(str, node->idx, &flags);
        if (is_valid_env_start(str[node->idx], str[node->idx + 1], flags))
        {
            node->end = set_env(&env, str, node->idx, env_list);
            node->crr = gen_str_with_env(&result, str, env, node);
        }
        node->idx++;
    }
    if (result == 0)
        result = ft_strndup(str, node->idx);
    else 
        result = join_str_to_str(result, str, node->crr, node->idx - (node->crr - 1) - 1);
    free_env_flag_node(env, flags, node);
    return(result);
}
=======
//     init_replace_env(&node, &result, &env, &flags);
//     while (str[node->idx] != '\0')
//     {
//         make_quote_status(str, node->idx, &flags);
//         if (is_valid_env_start(str[node->idx], str[node->idx + 1], flags))
//         {
//             node->end = set_env(&env, str, node->idx, env_list);
//             node->crr = gen_str_with_env(&result, str, env, node);
//         }
//         node->idx++;
//     }
//     if (result == 0)
//         result = ft_strndup(str, node->idx);
//     else 
//         result = join_str_to_str(result, str, node->crr, node->idx - (node->crr - 1) - 1);
//     free_env_flags_node(env, flags, node);
//     return(result);
// }
>>>>>>> b486cd166e77d110a201a095d0b086a4b89f1891
