/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:06:14 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/22 13:55:08 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

void	set_signal(void (*act)(int), int code)
{
	t_sigact	sig_act;

	ft_memset(&sig_act, 0, sizeof(sig_act));
	sig_act.sa_flags = SA_RESTART;
	sig_act.sa_handler = act;
	sigaction(code, &sig_act, NULL);
}

void	sigint_sighandler(int signum)
{
	int	mode;

	mode = sh_get_mode();
	if (mode == 1)
	{
		rl_on_new_line();
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_redisplay();
		set_status(128 + signum);
	}
}

void	init_signals(void)
{
	set_signal(&sigint_sighandler, SIGINT);
	set_signal(&sigquit_handler, SIGQUIT);
}

void	sig_set_all_default(void)
{
	set_signal(SIG_DFL, SIGINT);
	set_signal(SIG_DFL, SIGQUIT);
}

/* ctrl-c */
/* interactive mode : print new prompt on newline */
/* ctrl-\ in non-inter*/
/* interactive mode : nothing*/
void	sigquit_handler(int signum)
{
	int	mode;

	signum = 0;
	mode = sh_get_mode();
	if (mode == 1)
	{
		rl_redisplay();
	}
}
