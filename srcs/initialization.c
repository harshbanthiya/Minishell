/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 20:57:50 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/01 21:33:08 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	ft_init_shell()
{
	g_shell.active_t = NULL;
	tcgetattr(1, g_shell.saved_t);
	g_shell.env = NULL;
}

void	ft_init_env()
{

}