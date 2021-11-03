/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbaek <cbaek@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:16:30 by cbaek             #+#    #+#             */
/*   Updated: 2021/01/31 23:50:00 by cbaek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pwd(t_cmd *cmd)
{
	char cwd[1024];

	if (FALSE)		// TODO: 가짜 코드!
		cmd = 0;	// TODO: 가짜 코드!
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd(strerror(errno), 1);
	g_exit_code = 0;
	return (EXIT_SUCCESS);
}
