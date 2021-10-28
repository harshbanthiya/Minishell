/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/28 12:52:08 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	init_terms(t_shell *sh, int term_fd)
{
	t_term	term;

	tcgetattr(term_fd, &sh->def_term);
	tcgetattr(term_fd, &sh->saved_term);
	tcgetattr(term_fd, &term);
	// term.c_lflag &= ~(ECHO | ECHONL | ICANON | IEXTEN);
	// term.c_cflag |= ISIG;
	term_set_inter(&term);
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
	tcsetattr(1, TCSANOW, &sh->def_term);
}

void	term_restore_saved(void)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh == NULL)
		return ;
	tcsetattr(1, TCSANOW, &sh->saved_term);
}
