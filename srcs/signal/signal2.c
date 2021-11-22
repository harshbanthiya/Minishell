/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:52:36 by hbanthiy          #+#    #+#             */
/*   Updated: 2021/11/22 14:00:25 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

static void	sighandler_during_execution(int signum)
{
	g_shell.signal_child_received = signum;
}

void	set_sighandlers_during_execution(void)
{
	g_shell.signal_child_received = 0;
	if (signal(SIGQUIT, sighandler_during_execution) == SIG_ERR
		|| signal(SIGINT, sighandler_during_execution) == SIG_ERR)
	{
		printf("signal() failed\n");
		exit(1);
	}
}

void	set_sighandlers(t_sighandler sighandler)
{
	if (signal(SIGQUIT, sighandler) == SIG_ERR
		|| signal(SIGINT, sighandler) == SIG_ERR)
	{
		printf("signal() failed\n");
		exit(1);
	}
}

void	set_shell_sighandlers(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, sigint_sighandler) == SIG_ERR)
	{
		printf("signal() failed\n");
		exit(1);
	}
}
