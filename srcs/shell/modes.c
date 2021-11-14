/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/11/14 15:01:06 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* mode 0 : non-interactive, mode 1 : interactive */
void	sh_change_mode(t_shell *sh, int mode)
{
	if (sh == NULL)
		return ;
	if (mode == 1)
	{
		sh->sh_mode = 1;
		set_signal(&sigintr_handler, SIGINT);
		set_signal(&sigquit_handler, SIGQUIT);
	}
	else if (mode == 0)
	{
		sh->sh_mode = 0;
		set_signal(SIG_DFL, SIGINT);
		set_signal(SIG_DFL, SIGQUIT);
	}
}

int	sh_get_mode(void)
{
	return (g_shell.sh_mode);
}
