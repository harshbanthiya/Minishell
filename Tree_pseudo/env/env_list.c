#include "../shell.h"

void    update_kv_pair(t_env **env, char *envp)
{
    (*env)->key = ft_substr(envp, 0, ft_strchr(envp, (char)'=') - envp);
    (*env)->val = ft_substr(ft_strchr(envp, (char)'='), 1, ft_strlen(ft_strchr(envp, (char)'=')));
}

t_list    *make_env_list(char **envp)
{
    int             index;
    t_env           *env;
    t_list          *result;

    result = 0;
    index = 0;
    while (envp[index] != NULL)
    {
        env = (t_env *)malloc(sizeof(t_env));
        if (!env)
            return (0);
        update_kv_pair(&env, envp[index]);
        ft_lstadd_back(&result, ft_lstnew(env));
        index++;
    }
    return (result);
}