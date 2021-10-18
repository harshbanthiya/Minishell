/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:32:05 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/18 14:59:27 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

/* mode 0 : non-interactive, mode 1 : interactive */
void	sh_change_mode(int mode)
{
	t_shell	*sh;

	sh = get_shell();
	if (sh == NULL)
		return ;
	if (mode == 1)
		sh->sh_mode = 1;
	else if (mode == 0)
		sh->sh_mode = 0;	
}

int	get_sh_mode(void)
{
	return (g_shell.sh_mode);
}
