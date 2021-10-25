#include "../shell.h"

void    update_kv_pair(env_kv_pair **env, char *envp)
{
    (*env)->key = ft_substr(envp, 0, ft_strchr(envp, (char)'=') - envp);
    (*env)->val = ft_substr(ft_strchr(envp, (char)'='), 1, ft_strlen(ft_strchr(envp, (char)'=')));
}

list    *make_env_list(char **envp)
{
    int             index;
    env_kv_pair     *env;
    list            *result;

    result = 0;
    index = 0;
    while (envp[index] != NULL)
    {
        env = (env_kv_pair *)malloc(sizeof(env_kv_pair));
        if (!env)
            return (0);
        update_kv_pair(&env, envp[index]);
        ft_lstadd_back(&result, ft_lstnew(env));
        index++;
    }
    return (result);
}