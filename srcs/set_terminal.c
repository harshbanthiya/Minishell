/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfournie <marvin@42quebec.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 12:43:20 by sfournie          #+#    #+#             */
/*   Updated: 2021/10/08 12:48:00 by sfournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	set_saved_term(t_term *term)
{
	t_shell	*sh;
	
	sh = get_shell();
	sh->saved_term = term;
}

void	set_def_term(t_term *term)
{
	t_shell	*sh;
	
	sh = get_shell();
	sh->def_term = term;
}
void	set_active_term(t_term *term)
{
	t_shell	*sh;
	
	sh = get_shell();
	sh->active_term = term;
}
