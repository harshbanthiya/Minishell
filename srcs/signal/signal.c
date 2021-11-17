/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:06:14 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/17 12:00:32 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../../includes/minishell.h"
#include 	<signal.h>


void	set_signal(void (*act)(int), int code)
{
	t_sigact	sig_act;

	ft_memset(&sig_act, 0, sizeof(sig_act));
	sig_act.sa_flags = SA_RESTART;
	sig_act.sa_handler = act;
	sigaction(code, &sig_act, NULL);
}

static void	sigint_sighandler(int signum)
{
	signum = 0;
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

void 	set_sighandlers(t_sighandler sighandler)
{
	if (signal(SIGQUIT, sighandler) == SIG_ERR
		|| signal(SIGINT, sighandler) == SIG_ERR)
	{
		printf("signal() failed\n");
		exit(1);
	}
}

void	init_signals(void)
{
	set_signal(&sigint_sighandler, SIGINT);
	set_signal(&sigquit_handler, SIGQUIT);
}

void	sig_set_all_default()
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
	signum = 0;
	int	mode;

	mode = sh_get_mode();
	if (mode == 1)
	{
		rl_redisplay();
	}
	// rl_replace_line("", 1);
	// rl_on_new_line();
	// rl_redisplay();
	// ft_putstr_fd("Exiting minishell\n", 1);
	// exit_shell();
	// exit(1);
}

static void	sighandler_during_execution(int signum)
{
	g_shell.signal_child_received = signum;
}

/*
 * Set signal handlers in shell process.
 *
 * This function set these signal handlers.
 * - SIGQUIT: Ignore signal. Do nothing.
 * - SIGINT: Show "^C" since echo is disabled on the terminal.
 */
void	set_shell_sighandlers(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, sigint_sighandler) == SIG_ERR)
	{
		printf("signal() failed\n");
		exit(1);
	}
}

void set_sighandlers_during_execution(void)
{
	g_shell.signal_child_received = 0;
	if (signal(SIGQUIT, sighandler_during_execution) == SIG_ERR
		|| signal(SIGINT, sighandler_during_execution) == SIG_ERR)
	{
		printf("signal() failed\n");
		exit(1);
	}
}