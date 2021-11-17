/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_msg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:39:16 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/17 12:29:40 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* 
	Output error messages of the following format to stderr
	"minishell: {cmd_name}; {msg}\n"
*/
void	put_minish_err_msg(char *cmd_name, char *msg)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (cmd_name)
		write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name));
	write(STDERR_FILENO, ": ", 2);
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

int	put_minish_err_msg_and_ret(int ret_val,
		char *cmd_name, char *msg)
{
	put_minish_err_msg(cmd_name, msg);
	return (ret_val);
}

/* 
	Output error messages of the following format to stderr and exit (status) 
	"minishell: {cmd_name}: {msg}\n"    
*/

void	put_minish_err_msg_and_exit(int status,
		char *cmd_name, char *msg)
{
	put_minish_err_msg(cmd_name, msg);
	exit(status);
}

void	check_malloc_success(char *cmd_name, void *ptr)
{
	if (!ptr)
	{
		if (cmd_name)
			put_minish_err_msg_and_exit(1, cmd_name, "malloc() failed");
		else
			put_minish_err_msg_and_exit(1, "malloc", "malloc() failed");
	}
}
