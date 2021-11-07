#include "minishell.h"

char **create_path_arr(t_dlist *env_path)
{
	char	*path_env;
	char	**path_arr;

	path_env = NULL;
	while (env_path)
	{
		if (ft_strnstr( ((t_env *)(env_path->content))->key, "PATH",
			ft_strlen("PATH") + 1))
			path_env = ((t_env *)(env_path->content))->val;
		env_path = env_path->next;
	}
	if (!path_env)
		return (0);
	path_arr = ft_split(path_env, ':');
	return (path_arr);
}

void free_path_arr(char **path_arr)
{
	int i;

	i = 0;
	while (path_arr[i])
	{
		free(path_arr[i]);
		i++;
	}
	free(path_arr);
}

void free_tmp_env(char **env)
{
	int i;

	i = 0;
	if (env)
	{
		while (env[i])
			free(env[i++]);
		free(env);
	}
}

void exec_with_path(t_cmd *cmd, char **path_arr, t_dlist *env_list)
{
	char	*path_cmd1;
	char	*path_cmd2;
	char	**tmp_env;
	int		i;
	int	j=0;

	i = 0;
	while (path_arr[i])
	{
		path_cmd1 = ft_strjoin(path_arr[i], "/");
		path_cmd2 = ft_strjoin(path_cmd1, cmd->argv[0]);
		tmp_env = env_list_to_envp(env_list);
		execve(path_cmd2, cmd->argv, tmp_env);
		free_tmp_env(tmp_env);
		free(path_cmd1);
		free(path_cmd2);
		i++;
	}
}

char			*get_env_val(char *key, t_dlist *env_list)
{
	char	*env_val;
	int		key_len;

	key_len = ft_strlen(key);
	while (env_list)
	{
		if (!ft_strncmp(key, ((t_env *)(env_list->content))->key, key_len + 1))
		{
			env_val = ft_strdup(((t_env *)(env_list->content))->val);
			return (env_val);
		}
		env_list = env_list->next;
	}
	env_val = ft_strdup("");
	return (env_val);
}

char			*replace_home_path(char *str, t_dlist *env_list)
{
	char	*home;

	if ((ft_strncmp(str, "~", 2) == 0))
	{
		home = get_var_value("HOME", env_list);
		return (home);
	}
	return (str);
}