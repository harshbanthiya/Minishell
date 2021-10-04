/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 08:25:43 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/04 09:54:52 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

t_shell	*ft_get_shell(void)
{
	return (&g_shell);
}

void	ft_init_shell(void)
{
	g_shell.active_t = NULL;
	tcgetattr(1, g_shell.saved_t);
	g_shell.env = NULL;
}
