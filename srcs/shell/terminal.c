/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/01 14:50:24 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	init_terms(t_shell *sh, int term_fd)
{
	t_term	term;

	tcgetattr(term_fd, &sh->def_term);
	tcgetattr(term_fd, &term);
	set_mode_inter(&term);
	tcsetattr(term_fd, TCSANOW, &term);
}

/* should return the current terminal fd; need a tracked terminal fd */
int	term_get_active_fd(void)
{
	return (1);
}

void	term_restore_default(int term_fd)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh == NULL)
		return ;
	tcsetattr(term_fd, TCSANOW, &sh->def_term);
}
