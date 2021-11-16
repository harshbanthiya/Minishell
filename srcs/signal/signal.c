/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_general.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:06:14 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/15 16:00:21 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"


void	set_signal(void (*act)(int), int code)
{
	t_sigact	sig_act;

	ft_memset(&sig_act, 0, sizeof(sig_act));
	sig_act.sa_flags = SA_RESTART;
	sig_act.sa_handler = act;
	sigaction(code, &sig_act, NULL);
}

void	init_signals(void)
{
	set_signal(&sigintr_handler, SIGINT);
	set_signal(&sigquit_handler, SIGQUIT);
}

/* ctrl-c */
/* interactive mode : print new prompt on newline */
void	sigintr_handler(int signum)
{
	signum = 0;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	// set_status(128 + signum);
}

/* ctrl-\ in non-inter*/
/* interactive mode : nothing*/
void	sigquit_handler(int signum)
{
	signum = 0;
	// rl_replace_line("", 1);
	// rl_on_new_line();
	// rl_redisplay();
	// ft_putstr_fd("Exiting minishell\n", 1);
	// exit_shell();
	// exit(1);
}

void	sigchld_handler(int signum)
{
	signum = 0;
}
