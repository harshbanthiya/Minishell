#include "../shell.h"
/* Need to link with seb working builtins */

int			execute_internal_in_child(t_cmd *cmd, t_list **env_list)
{
	int	ret;

	ret = -1;
	if (cmd->pipe->stdin_pipe || cmd->pipe->stdout_pipe)
		if (!ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0] + 1)))
			ret = ft_exit(cmd);
	if (ft_strncmp(cmd->argv[0], "echo", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = ft_echo(cmd);
	else if (ft_strncmp(cmd->argv[0], "pwd", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = ft_pwd(cmd);
	else if ((ft_strncmp(cmd->argv[0], "export", \
			ft_strlen(cmd->argv[0]) + 1) == 0) && (cmd->argc == 1))
		ret = ft_export(cmd, env_list);
	else if (ft_strncmp(cmd->argv[0], "env", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = ft_env(cmd, env_list);
	return (ret);
}

int			execute_internal_in_parent(t_cmd *cmd, t_list **env_list)
{
	int	ret;

	ret = -1;
	if (ft_strncmp(cmd->argv[0], "cd", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = ft_cd(cmd, *env_list);
	else if (ft_strncmp(cmd->argv[0], "exit", ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = ft_exit(cmd);
	else if (ft_strncmp(cmd->argv[0], "unset", \
			ft_strlen(cmd->argv[0]) + 1) == 0)
		ret = ft_unset(cmd, env_list);
	else if ((ft_strncmp(cmd->argv[0], "export", \
			ft_strlen(cmd->argv[0]) + 1) == 0) && (cmd->argc > 1))
		ret = ft_export(cmd, env_list);
	return (ret);
}