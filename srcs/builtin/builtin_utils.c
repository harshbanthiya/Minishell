/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:15:44 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/02 17:16:04 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char	**init_builtins(void)
{
	char	**builtins;

	builtins = (char **)ft_calloc(8, sizeof(char *));
	if (builtins == NULL)
		return (NULL);
	builtins[0] = ft_strdup("cd");
	builtins[1] = ft_strdup("echo");
	builtins[2] = ft_strdup("exit");
	builtins[3] = ft_strdup("env");
	builtins[4] = ft_strdup("export");
	builtins[5] = ft_strdup("pwd");
	builtins[6] = ft_strdup("unset");
	return (builtins);
}

int	is_builtin(char *name)
{
	char	**builtins;

	builtins = get_builtins();
	if (!builtins)
		return (0);
	while (*builtins)
	{
		if (!ft_strcmp(*(builtins++), name))
			return (1);
	}
	return (0);
}

int	run_builtin(t_cmd *cmd, t_dlist **lst, int is_pipe)
{
	char	**builtins;
	int		exit_code;

	is_pipe = 0;
	if (!cmd || !cmd->argv[0] || !is_builtin(cmd->argv[0]))
		return (-1);
	if (!ft_strcmp(cmd->argv[0], "export"))
		exit_code = ft_export(cmd, lst);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		exit_code = ft_unset(cmd, lst);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		exit_code = ft_echo(cmd, lst);
	else if (!ft_strcmp(cmd->argv[0], "env"))
		exit_code = ft_env(cmd, lst);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		exit_code = ft_exit(cmd, lst);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		exit_code = ft_cd(cmd, lst);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		exit_code = ft_pwd(cmd, lst);
	return (1);
}

char	**get_builtins(void)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh != NULL)
	{
		return (sh->builtins);
	}
	return (NULL);
}

int			is_valid_env_key(char *env_key)
{
	int idx;

	idx = 0;
	if (*env_key == '_' || ft_isalpha(env_key[idx]))
	{
		idx++;
		while (env_key[idx] != '\0')
		{
			if (!ft_isalnum(env_key[idx]) && env_key[idx] != '_')
				return (FALSE);
			idx++;
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

int            execute_builtin_in_child(t_cmd *cmd, t_dlist **env_list)
{
    int    ret;

    ret = -1;
    if (cmd->pipe->stdin_pipe || cmd->pipe->stdout_pipe)
        if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0] + 1)))
            ret = ft_exit(cmd, env_list);
    if (ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0]) + 1) == 0)
        ret = ft_echo(cmd, env_list);
    else if (ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0]) + 1) == 0)
        ret = ft_pwd(cmd, env_list);
    // else if ((ft_strncmp(cmd->argv[0], "export", \
    //         ft_strlen(cmd->argv[0]) + 1) == 0) && (cmd->argc == 1))
    //     ft_export(cmd, env_list);
    // else if (ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0]) + 1) == 0)
    //     ft_env(cmd, env_list);
    return (ret);
}

int            execute_builtin_in_parent(t_cmd *cmd, t_dlist **env_list)
{
    int    ret;

    ret = -1;
    if (ft_strncmp(cmd->argv[0], "cd", ft_strlen(cmd->argv[0]) + 1) == 0)
        ret = ft_cd(cmd, env_list);
    else if (ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0]) + 1) == 0)
        ret = ft_exit(cmd, env_list);
    else if (ft_strncmp(cmd->argv[0], "unset", \
            ft_strlen(cmd->argv[0]) + 1) == 0)
        ret = ft_unset(cmd, env_list);
    // else if ((ft_strncmp(cmd->argv[0], "export", \
    //         ft_strlen(cmd->argv[0]) + 1) == 0) && (cmd->argc > 1))
    //     	ft_export(cmd, env_list);
    return (ret);
}

// int			execute_builtin_in_child(t_cmd *cmd, t_dlist **env_list)
// {
// 	int	ret;

// 	ret = -1;
// 	if (cmd->pipe->stdin_pipe || cmd->pipe->stdout_pipe)
// 		if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0] + 1)))
// 			ret = ft_exit(cmd);
// 	ret = run_builtin(cmd->argv[0], &cmd->argv[1]);
// 	return (ret);
// }

// int			execute_builtin_in_parent(t_cmd *cmd, t_dlist **env_list)
// {
// 	int	ret;

// 	ret = -1;
// 	ret = run_builtin(cmd->argv[0], &cmd->argv[1]);
// 	return (ret);
// }
