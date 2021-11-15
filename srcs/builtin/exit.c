/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 19:27:36 by sfournie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/15 13:49:03 by hbanthiy         ###   ########.fr       */
=======
/*   Updated: 2021/11/15 13:58:02 by sfournie         ###   ########.fr       */
>>>>>>> b989a1e3d66853e445a35926e61acde717994af0
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

int	ft_exit(char **argv)
{
	int	exit_status;

	lst = NULL;
	exit_status = -1; /* -1 for failure, remember to define MACROS or have a struct to have consistent values */
	// //printf("Command Count: %d\n", cmd->argc);
	// if (cmd->argc == 2)
	// {
	// 	exit_status = ft_atoi(cmd->argv[1]);
	// 	exit(exit_status);
	// }
	// else
	// {
	// 	ft_putstr_fd("exit: too many args\n", 1);
	// 	exit_status = 1;
	// }
	return (exit_status);
}
