/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_general.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:06:14 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/28 13:08:33 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

static void	init_signal(t_sigact *act, int code)
{
	ft_memset(act, 0, sizeof(*act));
	act->sa_flags = SA_RESTART;
	act->sa_handler = act;
	sigaction(code, act, NULL);
}

void	init_signals(void)
{
	t_sigact	sigintr_act;
	t_sigact	sigquit_act;

	init_signal(&sigintr_act, SIGINT);
	init_signal(&sigquit_act, SIGQUIT);
}

/* ctrl-c */
/* interactive mode : print new prompt on newline */
/* non-interactive mode : */
void	sigintr_handler (int signum)
{
	t_shell *sh;

	sh = get_shell();
	if (sh->sh_mode == 1)
	{
		printf("trying to print a new prompt\n");
		rl_on_new_line();
	}
	else if (sh->sh_mode == 0)
	{
		printf("trying to interrupt\n");
	}
}

/* ctrl-\ in non-inter, ctrl-D in inter */
/* interactive mode : print new prompt on newline */
/* non-interactive mode : */
void	sigquit_handler(int signum)
{
	// if (get_sh_mode() == 1)
	// {
	// 	printf("trying to do nothing at all\n");
	// }
	// else if (get_sh_mode() == 0)
	// {
		printf("Exiting minishell\n");
		exit(1);
	// }
}

/* ctrl-\ in non-inter, ctrl-D in inter */
/* interactive mode : print new prompt on newline */
/* non-interactive mode : */
void	sigchld_handler(int signum)
{

}
