/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbanthiy <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/08 23:08:44 by hbanthiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	set_mode_inter(t_term *term)
{
	term->c_cc[VEOF] = 4;
	term->c_cc[VINTR] = 3;
	term->c_cc[VQUIT] = 4;
}

void	set_mode_non_inter(t_term *term)
{
	term->c_cc[VEOF] = 4;
	term->c_cc[VINTR] = 3;
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
		set_mode_inter(&term);
	}
	else if (mode == 0)
	{
		sh->sh_mode = 0;
		set_mode_non_inter(&term);
	}
	tcsetattr(term_get_active_fd(), TCSANOW, &term);
}

int	get_sh_mode(void)
{
	return (g_shell.sh_mode);
}
