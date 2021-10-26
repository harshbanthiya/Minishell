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
void		print_env_list(t_list *env_head)
{
	t_list	*temp;

	temp = env_head;
	while (temp)
	{
		ft_putstr_fd(((t_env *)(temp->content))->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(((t_env *)(temp->content))->val, 1);
		ft_putstr_fd("\n", 1);
		temp = temp->next;
	}
}
// will need it later, Seb might have a better implementation check that 
char		**env_list_to_envp(t_list *env_head)
{
	t_list	*temp;
	int		i;
	char	**output;

	temp = env_head;
	i = ft_lstsize(temp);
	temp = env_head;
	if (!(output = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	i = 0;
	while (temp)
	{
		output[i] = ft_strjoin(((t_env *)(temp->content))->key, "=");
		output[i] = ft_strjoin(output[i], ((t_env *)(temp->content))->val);
		temp = temp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}

// Might need to set a single one and unset a single one AND NEED TO WRITE A SORT ENV FUNCTION 

void		set_env_one(t_list **list, t_env *env)
{
	t_list	*temp;
	int		key_len;

	key_len = ft_strlen(env->key);
	temp = *list;
	while (temp)
	{
		if (ft_strncmp((((t_env *)(temp->content))->key), \
				env->key, key_len + 1) == 0)
		{
			free(((t_env *)(temp->content))->val);
			((t_env *)(temp->content))->val = strdup(env->val);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(list, ft_lstnew(env));
}

int	is_existing_key(char *key, t_list *env_list)
{
	int		len;
	int		len_find;
	int		len_exist;

	len_find = ft_strlen(key);
	len_exist = ft_strlen((char *)((t_env *)env_list->content)->key);
	if (len_find > len_exist)
		len = len_find;
	else
		len = len_exist;
	if (ft_strncmp(key, ((t_env *)env_list->content)->key, len) == 0)
		return (1);
	return (0);
}

void		unset_env_one(t_list **env_head, char *key)
{
	t_list *head;
	t_list *delete;

	head = *env_head;
	if (is_existing_key(key, head))
	{
		*env_head = head->next;
		free_env((t_env *)head->content);
		free(head);
		return ;
	}
	while (head->next)
	{
		if (is_existing_key(key, head->next))
		{
			delete = head->next;
			if (delete->next != NULL)
				head->next = delete->next;
			else
				head->next = NULL;
			free_env((t_env *)delete->content);
			free(delete);
			return ;
		}
		head = head->next;
	}
}