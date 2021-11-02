#include "minishell.h"

void    init_env(t_env **env)
{
    (*env) = (t_env *)malloc(sizeof(t_env));
    if (!(*env))
        return ;
    (*env)->key = 0;
    (*env)->val = 0;
} 

void    init_replace_env(t_rplc_env_node **node, char **result, t_env **env, t_scan_quotes **flags)
{
    (*node) = (t_rplc_env_node *)malloc(sizeof(t_rplc_env_node));
    if (!(*node))
        return ;
    (*node)->idx = 0;
    (*node)->end = 0;
    (*node)->crr = 0;
    init_flag(flags);
    init_env(env);
    *result = 0;
}

int     is_valid_env_start(char chr1, char chr2, t_scan_quotes *flags)
{
    if (flags->s_quote == false && chr1 == '$' && (ft_isalpha(chr2) == true || chr2 == '_' || chr2 == '?'))
        return (true);
    return (false);
}

int     is_end_of_env_variable(char chr)
{
    if (ft_isalnum(chr) || chr == '_')
        return (false);
    return (true);
}

void    make_env_key_value(t_env **env, char *str, int len, t_dlist *env_list)
{
    (*env)->key = ft_strndup(str, len);
    if (ft_strncmp((*env)->key, "?", 2) == 0)
        (*env)->val = ft_itoa(global_exit_code);
    else 
        (*env)->val = get_env_val((*env)->key, env_list);
}


int     set_env_pos(char *str, int idx)
{
    idx++;
    while (!is_end_of_env_variable(str[idx]))
        idx++;
    if (str[idx] == '?')
        idx++;
    return (idx - 1);
}

int     set_env(t_env **env, char *str, int idx, t_dlist *env_list)
{
    int     env_str_end;

    env_str_end = set_env_pos(str, idx);
    make_env_key_value(env, &(str[idx + 1]), env_str_end - idx, env_list);
    return (env_str_end);
}

void    free_env_flag_node(t_env *env, t_scan_quotes *flags, t_rplc_env_node *node)
{
    free(env);
    free(flags);
    free(node);
}

