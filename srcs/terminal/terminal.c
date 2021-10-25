/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/18 18:05:06 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	init_terms(t_shell *sh, int term_fd)
{
	t_term	term;

	tcgetattr(term_fd, &sh->def_term);
	tcgetattr(term_fd, &sh->saved_term);
	tcgetattr(term_fd, &term);
	term.c_cc[VEOF] = 4; //to be removed
	term.c_cc[VINTR] = 3;
	term.c_cc[VQUIT] = 28;
	tcsetattr(term_fd, TCSANOW, &term);
}

/* should return the current terminal fd; need a tracked terminal fd */
int	term_get_active_fd(void)
{
	return (1);
}

void	term_save_state(int	term_fd)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh == NULL)
		return ;
	tcgetattr(term_fd, &sh->saved_term);
}

void	term_restore_default(int term_fd)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh == NULL)
		return ;
	tcsetattr(term_fd, TCSANOW, &sh->def_term);
}

void	term_restore_saved(void)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh == NULL)
		return ;
	tcsetattr(1, TCSANOW, &sh->saved_term);
}
