/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:36 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 15:54:02 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"

int	ft_exit(char **argv)
{
	int argv_len;
	int	exit_status;

	argv_len = ptrarr_len((void **)argv);
	exit_status = -1; /* -1 for failure, remember to define MACROS or have a struct to have consistent values */
	//printf("Command Count: %d\n", cmd->argc);
	if (argv_len == 2)
	 {
	 	exit_status = ft_atoi(argv[1]);
	 	exit(exit_status);
	 }
	else
		exit(g_shell.status);
	return (exit_status);
}
