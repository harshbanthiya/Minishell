/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:06:14 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/18 18:06:40 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	init_signals(void)
{
	// signal(SIGQUIT, sig_quit);
	// signal(EOF, sig_eof);
	// signal(SIGINT, sig_intr);
}

/* ctrl-c */
/* interactive mode : print new prompt on newline */
/* non-interactive mode : */
void	sig_intr(int sig_num)
{
	t_shell *sh;

	sh = get_shell();
	if (sh->sh_mode == 1)
	{
		printf("trying to print a new prompt\n");
	}
	else if (sh->sh_mode == 0)
	{
		printf("trying to interrupt\n");
	}
	// rl_on_new_line();
	// rl_replace_line("interrupted prompt :", 0);
	// rl_redisplay();
}

/* ctrl-d */
/* interactive : exit the shell (call exit_shell()) */
/* non-interactive : */
void	sig_eof(int sig_num) // to be removed
{
	t_shell *sh;

	sh = get_shell();
	if (sh->sh_mode == 1)
	{
		printf("trying to exit the shell\n");
	}
	else if (sh->sh_mode == 0)
	{
		printf("trying to EOF\n");
	}
}

/* ctrl-\ */
/* interactive mode : print new prompt on newline */
/* non-interactive mode : */
void	sig_quit(int sig_num)
{
	if (get_sh_mode() == 1)
	{
		printf("trying to do nothing at all\n");
	}
	else if (get_sh_mode() == 0)
	{
		printf("trying to quit\n");
	}
}
