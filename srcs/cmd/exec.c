/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:21:41 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/12/03 15:05:43 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "../../includes/ms_environment.h"
#include "../../includes/ms_path.h"
#include "../../includes/ms_execution.h"
#include "../../includes/minishell.h"

/*
 * find executable file in dirpath.
 *
 *   filename: filename
 *   dirpath: the directory to search
 *
 *   return:  fullpath of found executable file,
 *            otherwise return NULL.
 */
char	*find_executable_file_in_dir(char *filename, char *dirpath)
{
	struct stat		buf;
	char			*fullpath;

	if (!dirpath)
		return (NULL);
	fullpath = path_join(dirpath, filename);
	if (!fullpath)
		return (NULL);
	if (stat(fullpath, &buf) == 0 && S_ISREG(buf.st_mode))
		return (fullpath);
	free(fullpath);
	return (NULL);
}

/*
 * This function search file in directories in dirs and try to execute.
 */
static char	*search_and_exec_file_from_dirs(char *filename,
	char **argv, char **dirs)
{
	char		**envs;
	int			i;
	char		*executable_path;
	char		*last_executable_path;

	i = 0;
	last_executable_path = NULL;
	envs = env_list_to_envp(*get_env());
	while (dirs[i])
	{
		if (dirs[i])
			executable_path = find_executable_file_in_dir(filename, dirs[i]);
		if (executable_path)
		{
			free(last_executable_path);
			last_executable_path = ft_strdup(executable_path);
			execve(executable_path, argv, envs);
		}
		free(executable_path);
		i++;
	}
	free_ptrarr((void **)envs);
	return (last_executable_path);
}

/*
 * This function search file in directories in $PATH and try to execute.
 */
char	*search_and_exec_file_from_path_env(char *filename, char **argv)
{
	t_var		*path_env_var;
	char		**dirs;
	char		*last_executable_path;

	path_env_var = get_var("PATH", *get_env());
	if (!path_env_var || !path_env_var->value)
		return (NULL);
	dirs = get_colon_units(path_env_var->value, "./");
	last_executable_path = search_and_exec_file_from_dirs(filename, argv, dirs);
	free_ptrarr((void **)dirs);
	return (last_executable_path);
}

void	exec_with_path(char *filename, char **argv)
{
	char	**envp;

	envp = env_list_to_envp(*get_env());
	if (envp)
		execve(filename, argv, envp);
	free_ptrarr((void **)envp);
}

/*
 * This function works just like execvp.
 *
 * filename: filename or filepath.s
 * argv: arguments that is passed to execution program
 *
 * return: If exec command successful, no value will be returned.
 *         This function returning value means exec or other function is failed.
 */
int	cmd_execvp(char *filename, char **argv)
{
	char		*executable_path;

	errno = 0;
	executable_path = filename;
	if (ft_strchr(filename, '/'))
		exec_with_path(filename, argv);
	else
		executable_path = search_and_exec_file_from_path_env(filename, argv);
	if (executable_path && is_directory(executable_path))
	{	
		put_minish_err_msg(executable_path, "Is a directory");
		return (exec_exit_err_ret(126));
	}
	if (errno == ENOEXEC && is_executable(executable_path))
		return (exec_exit_err_ret(0));
	else if (errno == ENOEXEC && !is_executable(executable_path))
		errno = EACCES;
	if (errno && executable_path)
		put_minish_err_msg(executable_path, strerror(errno));
	else
		put_minish_err_msg(filename, "command not found");
	if (errno && errno != ENOENT)
		return (exec_exit_err_ret(126));
	return (exec_exit_err_ret(127));
}
