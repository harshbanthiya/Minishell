/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/28 17:48:04 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	term_set_inter(t_term *term)
{
	term->c_cc[VEOF] = 4;
	term->c_cc[VINTR] = 3;
	term->c_cc[VQUIT] = 4;
	// term->c_lflag |= (ICANON);
}

void	term_set_non_inter(t_term *term)
{
	term->c_cc[VEOF] = 4;
	term->c_cc[VINTR] = 4;
	term->c_cc[VQUIT] = 28;
}

/* mode 0 : non-interactive, mode 1 : interactive */
void	sh_change_mode(int mode)
{
	t_shell	*sh;
	t_term	term;

	tcgetattr(term_get_active_fd(), &term);
	sh = get_shell();
	if (sh == NULL)
		return ;
	if (mode == 1)
	{
		sh->sh_mode = 1;
		term_set_inter(&term);
	}
	else if (mode == 0)
	{
		sh->sh_mode = 0;
		term_set_non_inter(&term);
	}
	tcsetattr(term_get_active_fd(), TCSANOW, &term);
}

int	get_sh_mode(void)
{
	return (g_shell.sh_mode);
}
